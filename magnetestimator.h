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

private:
    int numberOfSensor;
    QVector<Matrix3d> rotMat;
    MatrixXd pos;
    MatrixXd magneticData;
    Vector3d magnetPosition;
    Vector3d magnetDirection;
};

#endif // MAGNETESTIMATOR_H
