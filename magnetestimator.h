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
    void setData(float data[][3]);
    void estimate();
private:
    int numberOfSensor;
    QVector<Matrix3f> rotMat;
    QVector<Vector3f> pos;
    MatrixXf magneticData;
    Vector3f magnetPosition;
    Vector3f magnetDirection;
};

#endif // MAGNETESTIMATOR_H
