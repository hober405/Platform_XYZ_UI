#include "magnetestimator.h"
#include "iostream"
#include <QDebug>

MagnetEstimator::MagnetEstimator(int n):
    _pos(3,n),
    _magneticData(3,n)
{
    _numberOfSensor = n;
}

void MagnetEstimator::inititialize()
{
    Vector3d rotDir; rotDir << 0, 0, 1;
    Matrix3d rotBase; rotBase << 0, -1, 0,
                                 1, 0, 0,
                                 0, 0, 1;
    Vector3d posBase; posBase << 1.5, 0, 0;
    rotDir.normalize();
    double rotRad = 45.0*EIGEN_PI/180.0;
    _rotMat.push_back(rotBase);
    _pos.col(0) = (posBase);

    Matrix3d rot;
    rot = AngleAxisd(rotRad, rotDir);

    for(int i = 1; i < _numberOfSensor; i++)
    {
        _rotMat.push_back(rot*_rotMat[i-1]);
        _pos.col(i) = (rot*_pos.col(i-1));

//        std::cout << "rotMat[" << i << "]\n" << rotMat[i] << "\n";
    }
//    std::cout << "pos\n" << pos << "\n";
}

void MagnetEstimator::setData(double *data)
{
    Map<MatrixXd> mag((double *)data,3,_numberOfSensor);
    _magneticData = mag;
//    std::cout << "magneticData\n" << magneticData << "\n";
}
bool MagnetEstimator::estimate()
{
    if(_magneticData.cwiseAbs().mean() < 1e-2)
    {
//        qDebug()<<"data too small";
        return false;
    }
    MatrixXd tmp = _magneticData;
//    std::cout << "tmp\n" << tmp << "\n";
    for(int i = 0; i < _numberOfSensor; i++) tmp.col(i) = _rotMat[i]*tmp.col(i);
//    std::cout << "tmp\n" << tmp << "\n";
    MatrixXd magCrossPos = MatrixXd::Zero(3,_numberOfSensor);
    for(int i = 0; i < _numberOfSensor; i++)
        magCrossPos.col(i) = Vector3d(tmp.col(i)).cross(Vector3d(_pos.col(i)));
//    std::cout << "magCrossPos\n" << magCrossPos << "\n";
    MatrixXd F(_numberOfSensor,6);
    F = (MatrixXd(6,_numberOfSensor)<<tmp,magCrossPos).finished().transpose();
    MatrixXd FTF = F.transpose()*F;
//    std::cout << "FTF\n" << FTF << "\n";
    SelfAdjointEigenSolver<MatrixXd> eigenSolution(FTF);
    if(eigenSolution.info() != Success) abort();
    MatrixXd::Index matRow, matCol;
//    eigenSolution.eigenvalues().cwiseAbs().minCoeff(&matRow,&matCol);
//    std::cout << "eigenSolution.eigenvalues()\n" << eigenSolution.eigenvalues() << "\n";
    VectorXd V = eigenSolution.eigenvectors().col(0);
//    std::cout << "V\n" << V << "\n";
    V = V*1/V.tail<3>().norm();
    Vector3d r = V.head(3);
//    std::cout << "r\n" << r << "\n";
    Vector3d H = V.tail<3>();
//    std::cout << "H\n" << H << "\n";
    float lrl2 = r.norm()*r.norm();
    MatrixXd lposl2 = _pos.colwise().norm().cwiseAbs2();
    MatrixXd rxH = r.cross(H);
    MatrixXd rxH_n = rxH.replicate(1,_numberOfSensor);
    MatrixXd HTpos = H.transpose()*_pos;
    MatrixXd G2 = 2*H.replicate(1,_numberOfSensor);
//    std::cout << "G2\n" << G2 << "\n";
    MatrixXd G1 = (-3*_pos+3*rxH_n-H*(HTpos));
//    std::cout << "G1\n" << G1 << "\n";
    MatrixXd G0 = 3*(_pos-rxH_n)*(HTpos).asDiagonal()
                  -H*(lposl2+lrl2*MatrixXd::Ones(1,_numberOfSensor)-2*rxH.transpose()*_pos);
//    std::cout << "G0\n" << G0 << "\n";
    MatrixXd coef2(3,_numberOfSensor);
    MatrixXd coef1(3,_numberOfSensor);
    MatrixXd coef0(3,_numberOfSensor);
    for(int i = 0; i < _numberOfSensor; i++)
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
    MatrixXd c2(3*_numberOfSensor, 2);
    c2 << coef2 , coef1;
    VectorXd t2_t = c2.bdcSvd(ComputeThinU|ComputeThinV).solve(-coef0);
    _magnetPosition = rxH+H*t2_t(1);
    _magnetDirection = H;
    //////////////////////////////////////////////////////////////////////

//    std::cout << "c2\n" << c2 << "\n";
    MatrixXd coef(3*_numberOfSensor, 3);
    coef << coef2 , coef1, coef0;
    MatrixXd rt = MatrixXd::Zero(3*_numberOfSensor, 2);
    for(int i = 0, j = 0; i < 3*_numberOfSensor; i++)
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
    O_B << rxH.replicate(1,rt.rows())+H*rt.transpose(), _magnetPosition;
//    std::cout << "O_B\n" << O_B << "\n";
    MatrixXd predictMag(3,_numberOfSensor);
    VectorXd error(rt.size()+1);
    VectorXd Bt(rt.size()+1);
    for(int i = 0; i < rt.size()+1; i++)
    {
        MatrixXd X = _pos-O_B.col(i).replicate(1,_numberOfSensor);
//        std::cout << "X\n" << X << "\n";
        MatrixXd XnormV2 = X.colwise().norm().cwiseAbs2();
//        std::cout << "XnormDiag\n" << XnormV2 << "\n";
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
    _magnetPosition = O_B.col(matRow);
    _magnetDirection *= (Bt[matRow] > 0? 1:-1);
//    std::cout << "magnetPosition\n" << magnetPosition << "\n";
//    std::cout << "magnetDirection\n" << magnetDirection << "\n";
    return true;
}

Vector3d MagnetEstimator::getMagnetPosition() const
{
    return _magnetPosition;
}

Vector3d MagnetEstimator::getMagnetDirection() const
{
    return _magnetDirection;
}

void MagnetEstimator::setRotMat(double *rotMat)
{
    for(int i = 0; i < _numberOfSensor; i++)
    {
        _rotMat[i] << rotMat[i*9+0], rotMat[i*9+1], rotMat[i*9+2],
                      rotMat[i*9+3], rotMat[i*9+4], rotMat[i*9+5],
                      rotMat[i*9+6], rotMat[i*9+7], rotMat[i*9+8];
    }
}

