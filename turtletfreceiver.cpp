#include "turtletfreceiver.h"
#include <QTimer>
#include <QDebug>

TurtleTfReceiver::TurtleTfReceiver()
{
    _originFrame = new char[200]{};
    _destinationFrame = new char[200]{};
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(spin()));
}

bool TurtleTfReceiver::setup(ros::NodeHandle &node)
{

    return true;
}

void TurtleTfReceiver::startReceiveData()
{
    _timer->start(10);
    qDebug() << "start receive...";
}

void TurtleTfReceiver::stopReceiveData()
{
    _timer->stop();
    qDebug() << "stop receive";
}

bool TurtleTfReceiver::spin()
{
//    qDebug() << "spin";
    ros::spinOnce();

    // try processing buffered data
    return process();

}

void TurtleTfReceiver::setFrames(const char *oldFrame, const char *newFrame)
{
    strcpy(_originFrame,oldFrame);
    strcpy(_destinationFrame,newFrame);
}

bool TurtleTfReceiver::process()
{
    tf::StampedTransform transform;
    try{
        _listener.lookupTransform(_destinationFrame, _originFrame,
                                  ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
        ROS_ERROR("%s", ex.what());
        return false;
    }
//    qDebug() << "angle: " << transform.getRotation().getAngle();
    _angle = transform.getRotation().getAngle();
    _x = transform.getOrigin().x();
    _y = transform.getOrigin().y();
    return true;
}

double TurtleTfReceiver::y() const
{
    return _y;
}

TurtleTfReceiver::~TurtleTfReceiver()
{
    delete [] _originFrame;
    delete [] _destinationFrame;
    delete _timer;
}

double TurtleTfReceiver::x() const
{
    return _x;
}

double TurtleTfReceiver::angle() const
{
    return _angle;
}
