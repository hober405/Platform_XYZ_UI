#ifndef MGNCALIBRATION_H
#define MGNCALIBRATION_H

#include <Eigen/Dense>
using namespace Eigen;

class MgnCalibration
{
public:
    MgnCalibration();
    bool calibrate(MatrixXd X);
    Matrix3d U() const;
    Vector3d c() const;
    bool isReady() const;

    MatrixXd X() const;

private:
    bool fchol(int n, MatrixXd A);
    VectorXd Utsolve(MatrixXd U, VectorXd b, int n);
    VectorXd Usolve(MatrixXd U, VectorXd b, int n);
    bool _isReady;
    Matrix3d _U;
    Vector3d _c;
    MatrixXd _cholA;
    MatrixXd _X;
};

#endif // MGNCALIBRATION_H
