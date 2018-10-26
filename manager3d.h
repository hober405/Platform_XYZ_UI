#ifndef MANAGER3D_H
#define MANAGER3D_H

#include <Qt3DCore/QEntity>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DRender/QCylinderMesh>
#include <Qt3DRender/QSphereMesh>
#include <Qt3DRender/QPhongMaterial>

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
    Qt3DRender::QCylinderMesh *d_cylinder;
    Qt3DRender::QPhongMaterial *d_cylinderMaterial;
    Qt3DRender::QPhongMaterial *d_sphereMaterial;
    Qt3DRender::QSphereMesh *d_sphereMesh;
    QVector3D middle_points;
    QVector3D ball_position;
    QVector3D position;
    float scale;
};

#endif // MANAGER3D_H
