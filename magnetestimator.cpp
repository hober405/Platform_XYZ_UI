#include "magnetestimator.h"
#include "iostream"
#include <QDebug>

MagnetEstimator::MagnetEstimator(int n):
    pos(3,n),
    magneticData(3,n)
{
    numberOfSensor = n;
}

void MagnetEstimator::inititialize()
{
    Vector3d rotDir; rotDir << 0, 0, 1;
    Matrix3d rotBase; rotBase << 0, -1, 0,
                                 1, 0, 0,
                                 0, 0, 1;
    Vector3d posBase; posBase << 1.5, 0, 0;
    rotDir.normalize();
    double rotRad = 2*EIGEN_PI/numberOfSensor;
    rotMat.push_back(rotBase);
    pos.col(0) = (posBase);

    Matrix3d rot;
    rot = AngleAxisd(rotRad, rotDir);

    for(int i = 1; i < numberOfSensor; i++)
    {
        rotMat.push_back(rot*rotMat[i-1]);
        pos.col(i) = (rot*pos.col(i-1));

//        std::cout << "rotMat[" << i << "]\n" << rotMat[i] << "\n";
    }
//    std::cout << "pos\n" << pos << "\n";
}

void MagnetEstimator::setData(double *data)
{
    Map<MatrixXd> mag((double *)data,3,numberOfSensor);
    magneticData = mag;
//    std::cout << "magneticData\n" << magneticData << "\n";
}
bool MagnetEstimator::estimate()
{
    if(magneticData.cwiseAbs().mean() < 1e-2)
    {
//        qDebug()<<"data too small";
        return false;
    }
    MatrixXd tmp = magneticData;
//    std::cout << "tmp\n" << tmp << "\n";
    for(int i = 0; i < numberOfSensor; i++) tmp.col(i) = rotMat[i]*tmp.col(i);
//    std::cout << "tmp\n" << tmp << "\n";
    MatrixXd magCrossPos = MatrixXd::Zero(3,numberOfSensor);
    for(int i = 0; i < numberOfSensor; i++)
        magCrossPos.col(i) = Vector3d(tmp.col(i)).cross(Vector3d(pos.col(i)));
//    std::cout << "magCrossPos\n" << magCrossPos << "\n";
    MatrixXd F(numberOfSensor,6);
    F = (MatrixXd(6,numberOfSensor)<<tmp,magCrossPos).finished().transpose();
    MatrixXd FTF = F.transpose()*F;
//    std::cout << "FTF\n" << FTF << "\n";
    SelfAdjointEigenSolver<MatrixXd> eigenSolution(FTF);
    if(eigenSolution.info() != Success) abort();
    MatrixXd::Index matRow, matCol;
    eigenSolution.eigenvalues().cwiseAbs().minCoeff(&matRow,&matCol);
//    std::cout << "eigenSolution.eigenvalues()\n" << eigenSolution.eigenvalues() << "\n";
    VectorXd V = eigenSolution.eigenvectors().col(matRow);
//    std::cout << "V\n" << V << "\n";
    V = V*1/V.tail<3>().norm();
    Vector3d r = V.head(3);
//    std::cout << "r\n" << r << "\n";
    Vector3d H = V.tail<3>();
//    std::cout << "H\n" << H << "\n";
    float lrl2 = r.norm()*r.norm();
    MatrixXd lposl2 = pos.colwise().norm().cwiseAbs2();
    MatrixXd rxH = r.cross(H);
    MatrixXd rxH_n = rxH.replicate(1,numberOfSensor);
    MatrixXd HTpos = H.transpose()*pos;
    MatrixXd G2 = 2*H.replicate(1,numberOfSensor);
//    std::cout << "G2\n" << G2 << "\n";
    MatrixXd G1 = (-3*pos+3*rxH_n-H*(HTpos));
//    std::cout << "G1\n" << G1 << "\n";
    MatrixXd G0 = 3*(pos-rxH_n)*(HTpos).asDiagonal()
                  -H*(lposl2+lrl2*MatrixXd::Ones(1,numberOfSensor)-2*rxH.transpose()*pos);
//    std::cout << "G0\n" << G0 << "\n";
    MatrixXd coef2(3,numberOfSensor);
    MatrixXd coef1(3,numberOfSensor);
    MatrixXd coef0(3,numberOfSensor);
    for(int i = 0; i < numberOfSensor; i++)
    {
        coef2.col(i) = Vector3d(G2.col(i)).cross(Vector3d(tmp.col(i)));
        coef1.col(i) = Vector3d(G1.col(i)).cross(Vector3d(tmp.col(i)));
        coef0.col(i) = Vector3d(G0.col(i)).cross(Vector3d(tmp.col(i)));
    }
    coef2.resize(coef2.size(),1);
    coef1.resize(coef1.size(),1);
    coef0.resize(coef0.size(),1);

//    std::cout << "coef2\n" << coef2 << "\n";
//    std::cout << "coef1\n" << coef1 << "\n";
//    std::cout << "coef0\n" << coef0 << "\n";

    //////////////////////////////////////////////////////////////////////
    MatrixXd c2(3*numberOfSensor, 2);
    c2 << coef2 , coef1;
    VectorXd t2_t = c2.bdcSvd(ComputeThinU|ComputeThinV).solve(-coef0);
    magnetPosition = rxH+H*t2_t(1);
    magnetDirection = H;
    //////////////////////////////////////////////////////////////////////

//    std::cout << "c2\n" << c2 << "\n";
    MatrixXd coef(3*numberOfSensor, 3);
    coef << coef2 , coef1, coef0;
    MatrixXd rt = MatrixXd::Zero(3*numberOfSensor, 2);
    for(int i = 0, j = 0; i < 3*numberOfSensor; i++)
    {
        if( coef2(i,0)/coef1(i,0) > 1e-3)
        {
            double b2_4ac = coef1(i,0)*coef1(i,0)-4*coef2(i,0)*coef0(i,0);
            if(b2_4ac >= 0)
            {
                rt(j,0) = (-coef1(i,0)+sqrt(b2_4ac))/(2*coef2(i,0));
                rt(j,1) = (-coef1(i,0)-sqrt(b2_4ac))/(2*coef2(i,0));
                j++;
            }
        }
        else
        {
            rt(j,0) = -coef0(i,0)/coef1(i,0);
            rt(j,1) = rt(i,0);
            j++;
        }
    }
    rt.resize(rt.size(),1);
    rt = rt.block(0,0,(rt.array() != 0).count(),1);
//    std::cout << "rt\n" << rt << "\n";
    MatrixXd O_B(3,rt.size()+1);
    O_B << rxH.replicate(1,rt.rows())+H*rt.transpose(), magnetPosition;
//    std::cout << "O_B\n" << O_B << "\n";
    MatrixXd predictMag(3,numberOfSensor);
    VectorXd error(rt.size()+1);
    VectorXd Bt(rt.size()+1);
    for(int i = 0; i < rt.size()+1; i++)
    {
        MatrixXd X = pos-O_B.col(i).replicate(1,numberOfSensor);
//        std::cout << "X\n" << X << "\n";
        MatrixXd XnormV2 = X.colwise().norm().cwiseAbs2();
//        std::cout << "XnormDiag\n" << XnormV << "\n";
        predictMag = (3*X*(H.transpose()*X).asDiagonal()-(H*XnormV2))
                *XnormV2.array().pow(-2.5).matrix().asDiagonal();
//        std::cout << "predictMag\n" << predictMag << "\n";
        Bt[i] = tmp.sum()/predictMag.sum();
        predictMag = predictMag*Bt[i];
        error[i] = (predictMag-tmp).cwiseAbs().sum();
    }
//    std::cout << "Bt\n" << Bt << "\n";
//    std::cout << "error\n" << error << "\n";
    error.minCoeff(&matRow, &matCol);
    magnetPosition = O_B.col(matRow);
    magnetDirection *= (Bt[matRow] > 0? 1:-1);
//    std::cout << "magnetPosition\n" << magnetPosition << "\n";
//    std::cout << "magnetDirection\n" << magnetDirection << "\n";
    return true;
}

Vector3d MagnetEstimator::getMagnetPosition() const
{
    return magnetPosition;
}

Vector3d MagnetEstimator::getMagnetDirection() const
{
    return magnetDirection;
}
