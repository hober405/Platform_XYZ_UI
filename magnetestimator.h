#ifndef MAGNETESTIMATOR_H
#define MAGNETESTIMATOR_H
#include <Eigen/Dense>
#include <QVector>

using namespace Eigen;
class MagnetEstimator
{
public:
    MagnetEstimator(int n);
    void inititialize();
    void setData(double *data);
    bool estimate();
    Vector3d getMagnetPosition() const;
    Vector3d getMagnetDirection() const;
    VectorXd getEigenValues() const;



    void setRotMat(double *rotMat);
    void setRotMat(Matrix3d *rotMat);

    MatrixXd getEigenVectors() const;

private:
    int _numberOfSensor;
    QVector<Matrix3d> _rotMat;
    MatrixXd _pos;
    MatrixXd _magneticData;
    Vector3d _magnetPosition;
    Vector3d _magnetDirection;
    VectorXd _eigenValues;
    MatrixXd _eigenVectors;

};

#endif // MAGNETESTIMATOR_H
