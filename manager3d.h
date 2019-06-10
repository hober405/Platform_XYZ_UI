#ifndef MANAGER3D_H
#define MANAGER3D_H

#include <Qt3DCore/QEntity>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

class Manager3D
{
public:
    Manager3D(Qt3DCore::QEntity *rootEntity);
    void setDirection(float x, float y, float z);
    void setPosition(float x, float y, float z);
private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QTransform *d_cylinderTransform;
    Qt3DCore::QEntity* d_ax;
    Qt3DCore::QTransform *d_sphereTransform;
    Qt3DCore::QEntity *d_sphereEntity;
    Qt3DExtras::QCylinderMesh *d_cylinder;
    Qt3DExtras::QPhongMaterial *d_cylinderMaterial;
    Qt3DExtras::QPhongMaterial *d_sphereMaterial;
    Qt3DExtras::QSphereMesh *d_sphereMesh;
    QVector3D middle_points;
    QVector3D ball_position;
    QVector3D position;
    float scale;
};

#endif // MANAGER3D_H
