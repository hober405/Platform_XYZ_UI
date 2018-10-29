#include "magnetestimator.h"
#include "iostream"
#include <QDebug>

MagnetEstimator::MagnetEstimator(int n):
    magneticData(3,n)
{
    numberOfSensor = n;
//    for(int i = 0; i < numberOfSensor; i++) magData.push_back(Vector3f::Zero());
}

void MagnetEstimator::inititialize()
{
    Vector3f rotDir; rotDir << 0, 0, 1;
    Matrix3f rotBase; rotBase << 0, -1, 0,
                                 1, 0, 0,
                                 0, 0, 1;
    Vector3f posBase; posBase << 1.5, 0, 0;
    rotDir.normalize();
    float rotRad = 2*EIGEN_PI/numberOfSensor;
    rotMat.push_back(rotBase);
    pos.push_back(posBase);

    Matrix3f rot;
    rot = AngleAxisf(rotRad, rotDir);

    for(int i = 1; i < numberOfSensor; i++)
    {
        rotMat.push_back(rot*rotMat[i-1]);
        pos.push_back(rot*pos[i-1]);
        std::cout<<rotMat[i]<<"\n";
        std::cout<<pos[i]<<"\n";
    }
}

void MagnetEstimator::setData(float data[][3])
{
    Map<MatrixXf> magneticData((float *)data,3,numberOfSensor);
//    std::cout << magneticData << "\n";
}

void MagnetEstimator::estimate()
{

}
