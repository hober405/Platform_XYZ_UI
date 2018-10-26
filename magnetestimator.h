#ifndef MAGNETESTIMATOR_H
#define MAGNETESTIMATOR_H
#include <Eigen/Dense>
#include <QVector>

using namespace Eigen;
class MagnetEstimator
{
public:
    MagnetEstimator(int n);
private:
    int numberOfSensors;
    QVector<Matrix3f> rot_mat;
    QVector<Vector3f> pos;
};

#endif // MAGNETESTIMATOR_H
