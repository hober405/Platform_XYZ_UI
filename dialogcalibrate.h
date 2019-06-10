#ifndef DIALOGCALIBRATE_H
#define DIALOGCALIBRATE_H

#include <QDialog>
#include <QSerialPort>
#include "envelope.h"
#include "envelopetracker.h"
#include "mgncalibration.h"


namespace Ui {
class DialogCalibrate;
}

class DialogCalibrate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCalibrate(QWidget *parent = 0);
    void setSerial(QSerialPort* sensor);
    void setEnvelopeAndTracker(Envelope* en, EnvelopeTracker* tracker);
    ~DialogCalibrate();

    Matrix3d *U() const;
    Vector3d *c() const;
    Matrix3d *rotation() const;

    bool isDataReady() const;

    virtual void show();
    virtual void reject();
    virtual void accept();

private slots:
    void on_pushButtonStartCalibrate_clicked();

    void readData();

    void on_lineEditTime_editingFinished();

    void on_pushButtonData_clicked();

    void on_pushButton_clicked();

    void on_lineEditTime_returnPressed();

private:
    void stopCalibrate();
    Ui::DialogCalibrate *ui;
    QSerialPort *_serialSensor;
    EnvelopeTracker* _tracker;
    Envelope* _envelope;
    double*** _rawData;
    int _rawDataLength;
    int _rawDataIndex;
    Matrix3d* _U;
    Vector3d* _c;
    bool _isCalibrating;
    bool _isDataReady;
    MatrixXd* _X;
    Matrix3d* _rotation;
};

#endif // DIALOGCALIBRATE_H
