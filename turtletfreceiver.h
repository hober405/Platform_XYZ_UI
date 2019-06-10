#ifndef TURTLETFRECEIVER_H
#define TURTLETFRECEIVER_H

#include <QObject>
#include <QTimer>
#include "ros/ros.h"
#include "tf/transform_listener.h"

class TurtleTfReceiver: public QObject
{
    Q_OBJECT
public:
    TurtleTfReceiver();
    bool setup(ros::NodeHandle &node);

    void startReceiveData();
    void stopReceiveData();
    void setFrames(const char *oldFrame, const char *newFrame);

    double angle() const;

    double x() const;

    double y() const;

    ~TurtleTfReceiver();

public slots:

    bool spin();

private:
    bool process();
    tf::TransformListener _listener;
    bool _isReceiveData;
    char *_originFrame;
    char *_destinationFrame;
    QTimer *_timer;
    double _angle;
    double _x;
    double _y;

//    ros::NodeHandle _node;
};

#endif // TURTLETFRECEIVER_H
