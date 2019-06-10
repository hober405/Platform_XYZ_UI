#include <QMessageBox>
#include <sstream>
#include "dialogcalibrate.h"
#include "ui_dialogcalibrate.h"
#include "mainwindow.h"
#include <QTimer>
#include <QFileDialog>

inline double abs(double in){
    return (in>0?in:-in);
}
DialogCalibrate::DialogCalibrate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCalibrate)
{
    ui->setupUi(this);
    _rawData = new double** [NUMBER_OF_SENSOR]{};
//    for(int i = 0; i < NUMBER_OF_SENSOR; i++) _rawData[i] = NULL;
    _rawDataIndex = 0;
    _U = new Matrix3d [NUMBER_OF_SENSOR];
    _c = new Vector3d [NUMBER_OF_SENSOR];
    _isCalibrating = false;
    _isDataReady = false;
    _X = new MatrixXd [NUMBER_OF_SENSOR]{};
    _rotation = new Matrix3d [NUMBER_OF_SENSOR];
}

void DialogCalibrate::setSerial(QSerialPort *sensor)
{
    _serialSensor = sensor;
    connect(_serialSensor, &QSerialPort::readyRead, this, &DialogCalibrate::readData);
}

void DialogCalibrate::setEnvelopeAndTracker(Envelope *en, EnvelopeTracker *tracker)
{
    _envelope = en;
    _tracker = tracker;
}

DialogCalibrate::~DialogCalibrate()
{
    delete ui;
    for(int mag = 0; mag < NUMBER_OF_SENSOR; mag++)
    {
        if(_rawData[mag])
        {
            for(int i = 0; i < _rawDataLength; i++)
            {
                delete [] _rawData[mag][i];
            }
            delete [] _rawData[mag];
        }
    }
    delete [] _rawData;
    delete [] _U;
    delete [] _c;
}

void DialogCalibrate::on_pushButtonStartCalibrate_clicked()
{
    MainWindow* main = (MainWindow*)(parent());
    if(!_isCalibrating)
    {
        int time = ui->lineEditTime->text().toInt();
        if(time <= 0) return;
        _isCalibrating = true;
        ui->plainTextEditResult->setPlainText("");
        ui->progressBar->setValue(0);
        ui->lineEditTime->setEnabled(false);
        for(int n = 0; n < NUMBER_OF_SENSOR; n++)
        {
            if(_rawData[n])
            {
                for(int i = 0; i < _rawDataLength; i++)
                {
                    delete [] _rawData[n][i];
                }
            }
            if(_rawDataLength != FS*time)
            {
                delete [] _rawData[n];
                _rawData[n] = new double* [FS*time]{};
            }
        }
        if(_rawDataLength != FS*time) _rawDataLength = FS*time;
        _rawDataIndex = 0;
        char tmp[] = {'R', static_cast<char>(time&0xFF), (char)0xFF};
        main->sendData(tmp,3);
        ui->pushButtonStartCalibrate->setText("Stop... ");
    }
    else
    {
        stopCalibrate();
    }
}

void DialogCalibrate::accept()
{
    if(_isCalibrating)
    {
        QMessageBox::critical(this, tr("Error"),
                              tr("Still calibrating. Please stop calibrate first!"));
        return;
    }
    MainWindow* main = (MainWindow*)(parent());
    disconnect(_serialSensor, &QSerialPort::readyRead, this, &DialogCalibrate::readData);
    main->finishCalibrate(true);
    QDialog::accept();
}

void DialogCalibrate::readData()
{
    QByteArray data;
    if(_serialSensor->isOpen()) data = _serialSensor->readAll();
    int l = data.length();
    l=l;
    _tracker->parse(data.data(),data.length());
    while(1)
    {
        Envelope * parseResult = _tracker->getEnvelope();
        if(parseResult == NULL) break;
        QByteArray dataArray(parseResult->getPayload(), parseResult->getPayloadLength());
        char cmd = (dataArray[0]&BIG_CHAR_MASK)|0x40;
        if(cmd=='M')
        {
            int x=((dataArray[1]<<8)+int(dataArray[2]&0xFF));
            int y=((dataArray[3]<<8)+int(dataArray[4]&0xFF));
            int z=((dataArray[5]<<8)+int(dataArray[6]&0xFF));

            double xMod = x/6842.0;
            double yMod = y/6842.0;
            double zMod = z/6842.0;
            int magNum = uint8_t((dataArray[0]>>5)&0x07);
            double * magnetRawData = new double [3]{xMod,yMod,zMod};
            _rawData[magNum][_rawDataIndex] = magnetRawData;

            ////////////////////////
            // remove jump points //
            //VVVVVVVVVVVVVVVVVVVV//

            if(_rawDataIndex > 1)
            {
                for(int xyz = 0; xyz < 3; xyz++)
                {
                    double rawData[3];
                    rawData[0] = _rawData[magNum][_rawDataIndex-2][xyz];
                    rawData[1] = _rawData[magNum][_rawDataIndex-1][xyz];
                    rawData[2] = _rawData[magNum][_rawDataIndex][xyz];
                    double diff[2] = {rawData[0]-rawData[1], rawData[1]-rawData[2]};
                    if(abs(diff[0]) > 3.2e-2 && abs(diff[1]) > 3.2e-2)
                    {
                        _rawData[magNum][_rawDataIndex-1][xyz] =
                                (rawData[0]+rawData[2])/2;
                        qDebug() << magNum << _rawDataIndex-1 << xyz
                                 << rawData[1] << _rawData[magNum][_rawDataIndex-1][xyz];
                        qDebug() << rawData[0] << rawData[1] << rawData[2];
                    }
                }
            }

            //^^^^^^^^^^^^^^^^^^^^//
            // remove jump points //
            ////////////////////////

            if(_rawDataIndex == _rawDataLength-1)
            {

                for(int i = 2; i < _rawDataLength; i++)
                {
                    for(int xyz = 0; xyz < 3; xyz++)
                    {
                        double rawData[3];
                        rawData[0] = _rawData[magNum][i-2][xyz];
                        rawData[1] = _rawData[magNum][i-1][xyz];
                        rawData[2] = _rawData[magNum][i][xyz];
                        double diff[2] = {rawData[0]-rawData[1], rawData[1]-rawData[2]};
                        if(abs(diff[0]) > 3.2e-2 && abs(diff[1]) > 3.2e-2)
                        {
                            _rawData[magNum][i-1][xyz] =
                                    (rawData[0]+rawData[2])/2;
                            qDebug() << "final correct" << magNum << i-1 << xyz
                                     << rawData[1] << _rawData[magNum][i-1][xyz];
                            qDebug() << rawData[0] << rawData[1] << rawData[2];
                        }
                    }
                }

                MatrixXd X(_rawDataLength-2, 3);
                for(int i = 0; i < _rawDataLength-2; i++)
                {
                    X.row(i) << _rawData[magNum][i+1][0],
                            _rawData[magNum][i+1][1],
                            _rawData[magNum][i+1][2];
                }
                MgnCalibration calibration;
                bool OK = calibration.calibrate(X);
                if(OK)
                {
                    _U[magNum] = calibration.U();
                    _c[magNum] = calibration.c();
                    std::stringstream ss;
                    ss << "U" << magNum << ":\n" << _U[magNum] << std::endl;
                    ss << "c" << magNum << ":\n" << _c[magNum] << std::endl;

                    QString plainText = ui->plainTextEditResult->toPlainText();
                    plainText += tr(ss.str().c_str());
                    ui->plainTextEditResult->setPlainText(plainText);
                    _X[magNum] = _U[magNum]*(X.transpose().colwise()-_c[magNum]);
                    _X[magNum].transposeInPlace();
                }
                else
                {
                    QString plainText = ui->plainTextEditResult->toPlainText();
                    plainText += tr("M%1 error\n").arg(magNum);
                    ui->plainTextEditResult->setPlainText(plainText);
                }
                if(magNum == NUMBER_OF_SENSOR-1)
                {
                    _isDataReady = OK;
                    stopCalibrate();
                    std::stringstream ss;
                    int centerCoordinate = ui->comboBoxM->currentIndex();
                    _rotation[centerCoordinate] = Matrix3d::Identity();
                    for(int magN = 0; magN < NUMBER_OF_SENSOR; magN++)
                    {
//                        ss << _X[magN] << std::endl;
                        if(magN == centerCoordinate){
                            ss << _rotation[magN] << std::endl;
                            continue;
                        }
                        _rotation[magN] = (_X[magN].transpose()*_X[magN]).inverse()
                                *(_X[magN].transpose()*_X[centerCoordinate]);
                        _rotation[magN].transposeInPlace();
                        ss << _rotation[magN] << std::endl;
                    }
                    QString plainText = ui->plainTextEditResult->toPlainText();
                    plainText += tr(ss.str().c_str());
                    ui->plainTextEditResult->setPlainText(plainText);
                }
            }

            if(magNum == NUMBER_OF_SENSOR - 1) _rawDataIndex++;
        }
        int value = _rawDataIndex*100/_rawDataLength;
        ui->progressBar->setValue(value);
    }
}

void DialogCalibrate::stopCalibrate()
{
    MainWindow* main = (MainWindow*)(parent());
    main->sendData("S",1);
    ui->pushButtonStartCalibrate->setText("Calibrate!");
    ui->lineEditTime->setEnabled(true);
    _isCalibrating = false;
}

Matrix3d *DialogCalibrate::rotation() const
{
    return _rotation;
}

bool DialogCalibrate::isDataReady() const
{
    return _isDataReady;
}

void DialogCalibrate::show()
{
    QDialog::show();
    _isDataReady = false;
}

void DialogCalibrate::reject()
{
    QDialog::reject();
    MainWindow* main = (MainWindow*)(parent());
    disconnect(_serialSensor, &QSerialPort::readyRead, this, &DialogCalibrate::readData);
    stopCalibrate();
    main->finishCalibrate(false);
}

Vector3d *DialogCalibrate::c() const
{
    return _c;
}

Matrix3d *DialogCalibrate::U() const
{
    return _U;
}

void DialogCalibrate::on_lineEditTime_editingFinished()
{
    qDebug() << "line edit finished!!";
}

void DialogCalibrate::on_pushButtonData_clicked()
{
    if(!_isDataReady)
    {
        QMessageBox::critical(this, tr("Caution"), tr("No data available."));
        return;
    }
    QString name = tr("data.log");
    QString filename = QFileDialog::getSaveFileName(
                this,"Save data...",name,tr("Log files (*.log)"));
    QFile *file = new QFile(filename);
    if(file->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream ts;
        ts.setDevice(file);
        std::stringstream ss;
        for(int magNum = 0; magNum < NUMBER_OF_SENSOR; magNum++)
        {
            ss << "M" << magNum << std::endl;
            for(int i = 0; i < _rawDataLength; i++)
            {
                ss << _rawData[magNum][i][0] << " "
                        << _rawData[magNum][i][1] << " "
                        << _rawData[magNum][i][2] << std::endl;
            }
        }
        ts << ss.str().c_str();
    }
}

void DialogCalibrate::on_pushButton_clicked()
{
    if(!_isDataReady)
    {
        QMessageBox::critical(this, tr("Caution"), tr("No result available."));
        return;
    }
    QString name = tr("result.log");
    QString filename = QFileDialog::getSaveFileName(
                this,"Save data...",name,tr("Log files (*.log)"));
    QFile *file = new QFile(filename);
    if(file->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream ts;
        ts.setDevice(file);
        std::stringstream ss;
        for(int magNum = 0; magNum < NUMBER_OF_SENSOR; magNum++)
        {
            ss << "U" << magNum << ":\n" << _U[magNum] << std::endl;
            ss << "c" << magNum << ":\n" << _c[magNum] << std::endl;
            ss << "rotation" << magNum << ":\n" << _rotation[magNum] << std::endl;
        }
        ts << ss.str().c_str();
    }
}

void DialogCalibrate::on_lineEditTime_returnPressed()
{
    qDebug() << "return pressed!!";
    on_pushButtonStartCalibrate_clicked();
}
