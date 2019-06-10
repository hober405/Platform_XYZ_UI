#include "mgncalibration.h"
#include <sstream>
#include <QDebug>
#include <QFile>

MgnCalibration::MgnCalibration():_isReady(false)
{
}

bool MgnCalibration::calibrate(MatrixXd X)
{
    if(X.rows()==3 && X.cols()>3) X.transposeInPlace();
    if(X.rows()<=10) return true;
    std::stringstream ss;
    ss << X << std::endl;
    QFile file("tmp.log");
    bool isFileOpen = file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream ts;
    ts.setDevice(&file);
    ts.setCodec("UTF-8");

    ArrayXd x = X.col(0).array();
    ArrayXd y = X.col(1).array();
    ArrayXd z = X.col(2).array();
    MatrixXd D(X.rows(), 10);
    D << x*x, y*y, z*z, x*y, x*z, y*z, x, y, z, VectorXd::Ones(X.rows());
    bool OK = fchol(10,D.transpose()*D);
    if(OK) D = _cholA;
    else return false;
    D = D.triangularView<Upper>();
    JacobiSVD<MatrixXd> svd(D,ComputeThinU|ComputeThinV);
    MatrixXd V = svd.matrixV();
    VectorXd p = V.rightCols<1>();
    if(p(0)<0) p = -p;
    Matrix3d A;
    A << p(0),      p(3)/2, p(4)/2,
         p(3)/2,    p(1),   p(5)/2,
         p(4)/2,    p(5)/2, p(2);
    MatrixXd U;
    OK = fchol(3, A);
    if(OK) U = _cholA;
    else return false;
    Vector3d b;
    b << p(6), p(7), p(8);
    Vector3d v = Utsolve(U,b/2,3);
    double d = p(9);
    double s = 1/sqrt((v.dot(v))-d);
    _c = -Usolve(U,v,3);
    _U = s*U;
    ss << "c:\n" << _c << std::endl;
    ss << "U:\n" << _U << std::endl;

    if(isFileOpen)
    {
        ts << QString(ss.str().c_str());
    }
    _isReady = true;
    return true;
}

Matrix3d MgnCalibration::U() const
{
    if(!_isReady) return Matrix3d::Identity();
    return _U;
}

Vector3d MgnCalibration::c() const
{
    if(!_isReady) return Vector3d::Zero();
    return _c;
}

bool MgnCalibration::isReady() const
{
    return _isReady;
}

bool MgnCalibration::fchol(int n, MatrixXd A)
{
    A.block(0,0,1,n) = A.block(0,0,1,n)/sqrt(A(0,0));
    A.block(1,0,n-1,1) = VectorXd::Zero(n-1,1);
    for(int j = 1; j < n; j++)
    {
        A.block(j,j,1,n-j) = A.block(j,j,1,n-j) - A.block(0,j,j,1).transpose()*A.block(0,j,j,n-j);
        if(A(j,j)<=0) return false;
        A.block(j,j,1,n-j) = A.block(j,j,1,n-j)/sqrt(A(j,j));
        A.block(j+1,j,n-j-1,1) = VectorXd::Zero(n-1-j,1);
    }
    _cholA = A;
    return true;
}

VectorXd MgnCalibration::Utsolve(MatrixXd U, VectorXd b, int n)
{
    VectorXd x = VectorXd::Zero(n);
    x(0) = b(0)/U(0,0);
    for(int i = 1; i < n; i++)
    {
        VectorXd Uv(Map<VectorXd>(U.block(0,i,i,1).data(),i));
        double xU = x.head(i).dot(Uv);
        x(i) = (b(i)-xU)/U(i,i);
    }
    return x;
}

VectorXd MgnCalibration::Usolve(MatrixXd U, VectorXd b, int n)
{
    VectorXd x = VectorXd::Zero(n);
    x(n-1) = b(n-1)/U(n-1,n-1);
    for(int i = n-2; i >= 0; i--)
    {
        VectorXd Uv = U.row(i).tail(n-i-1);
        double Ux = Uv.dot(x.tail(n-i-1));
        x(i) = (b(i)-Ux)/U(i,i);
    }
    return x;
}
