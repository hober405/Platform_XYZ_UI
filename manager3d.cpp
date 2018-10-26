#include "manager3d.h"

Manager3D::Manager3D(Qt3DCore::QEntity *rootEntity):
    m_rootEntity(rootEntity)
{

    scale = 10;
    // xyz shape data
    Qt3DRender::QCylinderMesh *x_cylinder = new Qt3DRender::QCylinderMesh();
    x_cylinder->setRadius(0.01f/scale);
    x_cylinder->setLength(1);
    x_cylinder->setRings(100);
    x_cylinder->setSlices(20);

    // CylinderMesh Transform
    Qt3DCore::QTransform *x_cylinderTransform = new Qt3DCore::QTransform();
    x_cylinderTransform->setScale(scale);
    x_cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 1.0f), 90.0f));
    x_cylinderTransform->setTranslation(QVector3D(scale/2.0f, 0.0f, 0.0f));

    Qt3DRender::QPhongMaterial *x_cylinderMaterial = new Qt3DRender::QPhongMaterial();
    x_cylinderMaterial->setDiffuse(QColor(QRgb(0xff0000)));

    // Cylinder
    Qt3DCore::QEntity* x_ax = new Qt3DCore::QEntity(m_rootEntity);
    x_ax->addComponent(x_cylinder);
    x_ax->addComponent(x_cylinderTransform);
    x_ax->addComponent(x_cylinderMaterial);

    // xyz shape data
    Qt3DRender::QCylinderMesh *y_cylinder = new Qt3DRender::QCylinderMesh();
    y_cylinder->setRadius(0.01f/scale);
    y_cylinder->setLength(1);
    y_cylinder->setRings(100);
    y_cylinder->setSlices(20);

    // CylinderMesh Transform
    Qt3DCore::QTransform *y_cylinderTransform = new Qt3DCore::QTransform();
    y_cylinderTransform->setScale(scale);
    y_cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 0.0f));
    y_cylinderTransform->setTranslation(QVector3D(0.0f, scale/2.0f, 0.0f));

    Qt3DRender::QPhongMaterial *y_cylinderMaterial = new Qt3DRender::QPhongMaterial();
    y_cylinderMaterial->setDiffuse(QColor(QRgb(0x00ff00)));

    // Cylinder
    Qt3DCore::QEntity* y_ax = new Qt3DCore::QEntity(m_rootEntity);
    y_ax->addComponent(y_cylinder);
    y_ax->addComponent(y_cylinderTransform);
    y_ax->addComponent(y_cylinderMaterial);

    // xyz shape data
    Qt3DRender::QCylinderMesh *z_cylinder = new Qt3DRender::QCylinderMesh();
    z_cylinder->setRadius(0.01f/scale);
    z_cylinder->setLength(1);
    z_cylinder->setRings(100);
    z_cylinder->setSlices(20);

    // CylinderMesh Transform
    Qt3DCore::QTransform *z_cylinderTransform = new Qt3DCore::QTransform();
    z_cylinderTransform->setScale(scale);
    z_cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 90.0f));
    z_cylinderTransform->setTranslation(QVector3D(0.0f, 0.0f, scale/2.0f));

    Qt3DRender::QPhongMaterial *z_cylinderMaterial = new Qt3DRender::QPhongMaterial();
    z_cylinderMaterial->setDiffuse(QColor(QRgb(0x0000ff)));

    // Cylinder
    Qt3DCore::QEntity* z_ax = new Qt3DCore::QEntity(m_rootEntity);
    z_ax->addComponent(z_cylinder);
    z_ax->addComponent(z_cylinderTransform);
    z_ax->addComponent(z_cylinderMaterial);

    // data shape data
    d_cylinder = new Qt3DRender::QCylinderMesh();
    d_cylinder->setRadius(0.01f);
    d_cylinder->setRings(100);
    d_cylinder->setSlices(20);

    // CylinderMesh Transform
    d_cylinderTransform = new Qt3DCore::QTransform();
    d_cylinderTransform->setScale(scale);

    d_cylinderMaterial = new Qt3DRender::QPhongMaterial();
    d_cylinderMaterial->setDiffuse(QColor(QRgb(0xffffff)));

    // Cylinder
    d_ax = new Qt3DCore::QEntity(m_rootEntity);
    d_ax->addComponent(d_cylinder);
    d_ax->addComponent(d_cylinderTransform);
    d_ax->addComponent(d_cylinderMaterial);

    // Sphere shape data
    d_sphereMesh = new Qt3DRender::QSphereMesh();
    d_sphereMesh->setRings(20);
    d_sphereMesh->setSlices(20);
    d_sphereMesh->setRadius(0.1f);

    // Sphere mesh transform
    d_sphereTransform = new Qt3DCore::QTransform();
    d_sphereTransform->setScale(scale);

    d_sphereMaterial = new Qt3DRender::QPhongMaterial;
    d_sphereMaterial->setDiffuse(QColor(QRgb(0xff0000)));

    // Sphere
    d_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
    d_sphereEntity->addComponent(d_sphereMesh);
    d_sphereEntity->addComponent(d_sphereTransform);
    d_sphereEntity->addComponent(d_sphereMaterial);
}

void Manager3D::setDirection(float x, float y, float z)
{
    float data[3] = {x,y,z};
    float length = sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
    float rotVec[3]; // origin: ey = (0,1,0), rotVec = ey X data;
    float length_scale = 2;
    rotVec[0] = data[2];
    rotVec[1] = 0;
    rotVec[2] = -data[0];

    float theta = acos(data[1]/length)*180/3.14;
    d_cylinder->setLength(length/length_scale);
    d_cylinder->setRadius(0.01f/scale);
    d_cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(rotVec[0], rotVec[1], rotVec[2]), theta));
    d_cylinderTransform->setTranslation(QVector3D(data[0]/2, data[1]/2, data[2]/2)*scale/length_scale);
    d_sphereMesh->setRadius(length/length_scale/10);
    d_sphereTransform->setTranslation(QVector3D(data[0], data[1], data[2])*scale/length_scale);
    middle_points = d_cylinderTransform->translation();
    ball_position = d_sphereTransform->translation();
    d_cylinderTransform->setTranslation(position*scale+middle_points);
    d_sphereTransform->setTranslation(position*scale+ball_position);
}

void Manager3D::setPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);
    d_cylinderTransform->setTranslation(position*scale+middle_points);
    d_sphereTransform->setTranslation(position*scale+ball_position);
}
