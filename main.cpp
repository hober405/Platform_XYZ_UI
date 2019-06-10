#include "mainwindow.h"
#include <QApplication>

#include <ros/ros.h>

//#include "window.h"
//#include <QSize>
//#include <QScreen>
//#include <Qt3DRender/qcamera.h>
//#include <Qt3DCore/qentity.h>
//#include <Qt3DRender/qcameralens.h>

//#include <Qt3DInput/QInputAspect>

//#include <Qt3DExtras/qtorusmesh.h>
//#include <Qt3DRender/qmesh.h>
//#include <Qt3DRender/qtechnique.h>
//#include <Qt3DRender/qmaterial.h>
//#include <Qt3DRender/qeffect.h>
//#include <Qt3DRender/qtexture.h>
//#include <Qt3DRender/qrenderpass.h>
//#include <Qt3DRender/qsceneloader.h>

//#include <Qt3DCore/qtransform.h>
//#include <Qt3DCore/qaspectengine.h>

//#include <Qt3DRender/qrenderaspect.h>
////#include <Qt3DRender/qframegraph.h>
//#include <Qt3DExtras/qforwardrenderer.h>

//#include <QtCore/QObject>
//#include <QDockWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ros::init(argc, argv, "Turtle_Tf_Receiver");
    ros::NodeHandle node;

//    Window *view = new Window();
//    QWidget *container = QWidget::createWindowContainer(view);
//    QSize screenSize = view->screen()->size();
//    container->setMinimumSize(QSize(200, 100));
//    container->setMaximumSize(screenSize);

//    Qt3DCore::QAspectEngine engine;
//    engine.registerAspect(new Qt3DRender::QRenderAspect());
//    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
//    engine.registerAspect(input);
//    QVariantMap data;
//    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(view)));
//    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(view));
//    engine.setData(data);

//    // Root entity
//    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

//    // Camera
//    Qt3DRender::QCamera *cameraEntity = new Qt3DRender::QCamera(rootEntity);
//    cameraEntity->setObjectName(QStringLiteral("cameraEntity"));

//    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
//    cameraEntity->setPosition(QVector3D(20.0f, -50.0f, 10.0f));
//    cameraEntity->setUpVector(QVector3D(0, 0, 1));
//    cameraEntity->setViewCenter(QVector3D(20,10,10));
//    input->setCamera(cameraEntity);

//    // FrameGraph
////    Qt3DRender::QFrameGraph *frameGraph = new Qt3DRender::QFrameGraph();
//    Qt3DExtras::QForwardRenderer *forwardRenderer = new Qt3DExtras::QForwardRenderer();

//    forwardRenderer->setCamera(cameraEntity);
//    forwardRenderer->setClearColor(QColor(QRgb(0xf0f0f0)));
////    frameGraph->setActiveFrameGraph(forwardRenderer);

//    // Setting the FrameGraph
//    rootEntity->addComponent(forwardRenderer);

//    // Set root object of the scene
//    engine.setRootEntity(rootEntity);
    MainWindow w/*(rootEntity)*/;
//    w.addContainer(container);
    w.setup(node);
    w.show();

    return a.exec();
}
