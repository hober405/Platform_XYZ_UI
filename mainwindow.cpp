#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <QMessageBox>
#include <qdebug.h>
#include <QFileDialog>
#include "mgncalibration.h"

#define NUMBER_OF_SENSOR 8
MainWindow::MainWindow(Qt3DCore::QEntity *rootEntity, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _magSelection(0x00),
    _estimater(NUMBER_OF_SENSOR),
    _magDataPreprocessor(NUMBER_OF_SENSOR),
    _isShowMag(false)////
{
    ui->setupUi(this);
    _serialMotor = new QSerialPort(this);
    _serialSensor = new QSerialPort(this);
    connect(_serialMotor, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(_serialSensor, &QSerialPort::readyRead, this, &MainWindow::readData);
    _en.enableHeader(std::string("H"));
    _en.enableFooter(std::string("E"),8);
    _en.enableCheckXOR(9);
    _tracker.setEnvelope(_en);
    _tracker.setBufferLength(100);
    _listIndex = 0;
    QString fileName("D:\\Magnet localization\\Platform_XYZ_UI\\log\\Motor_log ");
    fileName += QDate::currentDate().toString()+".log";
    _file = new QFile(fileName);
    qDebug()<<fileName<<endl;
    _recordData.reserve(_listMax);
    _manager = new Manager3D(rootEntity);
    _isPatternRecord = false;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBoxComPortMotor->addItem(info.portName());
        ui->comboBoxComPortSensor->addItem(info.portName());
    }
    ui->comboBoxComPortMotor->setCurrentIndex(1);
    _estimater.inititialize();
//    double data[][3] = {
//        {0,	-0.487869044139141,	-1.26059631686641},
//        {-0.285004384682841,	-0.204326220403391,	-0.990353697749197},
//        {-0.183864367144110,	0.0368313358667054,	-0.625255773165741},
//        {-0.0716164864074833,	0.0919321835720544,	-0.439929845074540},
//        {0,	0.0983630517392573,	-0.388336743642210},
//        {0.0716164864074829,	0.0919321835720544,	-0.439929845074540},
//        {0.183864367144110,	0.0368313358667054,	-0.625255773165741},
//        {0.285004384682841,	-0.204326220403391,	-0.990353697749197}
//    };
//    estimater.setData((double *)data);
//    estimater.estimate();
}

void MainWindow::addContainer(QWidget *container)
{
    ui->horizontalLayoutContainer->addWidget(container);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_to_NUCLEO_triggered()
{
    //    SettingsDialog::Settings p = settings->settings();
    _serialMotor->setPortName(ui->comboBoxComPortMotor->currentText());
    _serialMotor->setBaudRate(ui->lineEditBaudMotor->text().toInt());
    _serialMotor->setDataBits(QSerialPort::Data8);
    _serialMotor->setParity(QSerialPort::NoParity);
    _serialMotor->setStopBits(QSerialPort::OneStop);
    _serialMotor->setFlowControl(QSerialPort::NoFlowControl);
    _serialSensor->setPortName(ui->comboBoxComPortSensor->currentText());
    _serialSensor->setBaudRate(ui->lineEditBaudSensor->text().toInt());
    _serialSensor->setDataBits(QSerialPort::Data8);
    _serialSensor->setParity(QSerialPort::NoParity);
    _serialSensor->setStopBits(QSerialPort::OneStop);
    _serialSensor->setFlowControl(QSerialPort::NoFlowControl);
    if (_serialMotor->open(QIODevice::ReadWrite) && _serialSensor->open(QIODevice::ReadWrite)) {
        //        console->setEnabled(true);
        //        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect_to_NUCLEO->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        //        ui->actionConfigure->setEnabled(false);
        ui->statusBar->showMessage(tr("Sensor Connected to %1 : %2, %3, %4, %5, %6; Motor Connect to %7 : %8, %9, %10, %11, %12 ")
                                   .arg(_serialSensor->portName()).arg(_serialSensor->baudRate()).arg(QSerialPort::Data8)
                                   .arg(QSerialPort::NoParity).arg(QSerialPort::OneStop).arg(QSerialPort::NoFlowControl)
                                   .arg(_serialMotor->portName()).arg(_serialMotor->baudRate()).arg(QSerialPort::Data8)
                                   .arg(QSerialPort::NoParity).arg(QSerialPort::OneStop).arg(QSerialPort::NoFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"),
                              tr("Motor: %1; Sensor: %2")
                              .arg(_serialMotor->errorString())
                              .arg(_serialSensor->errorString()));

        ui->statusBar->showMessage(tr("Open error"));
        _serialMotor->close();
        _serialSensor->close();
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (_serialMotor->isOpen()||_serialMotor->isOpen())
    {
        _serialMotor->close();
        _serialSensor->close();
    }
    //    console->setEnabled(false);
    ui->actionConnect_to_NUCLEO->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    //    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
    QString fileName = QFileDialog::getSaveFileName(this, "save pos and dir...","",tr("Text files. (*.txt)"));
    if(fileName == "") return;
    QFile textFile(fileName);
    if(textFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        _textStream.setDevice(&textFile);
        _textStream.setCodec("UTF-8");
        _textStream << "position:\n";
        QString text;
        for(int i = 0; i < _positionHistory.size(); i++)
        {
            text = QString::number(_positionHistory[i][0]) + " " +
                    QString::number(_positionHistory[i][1]) + " " +
                    QString::number(_positionHistory[i][2]) + "\n";
            _textStream << text;
        }
        _textStream << "direction:\n";
        for(int i = 0; i < _directionHistory.size(); i++)
        {
            text = QString::number(_directionHistory[i][0]) + " " +
                    QString::number(_directionHistory[i][1]) + " " +
                    QString::number(_directionHistory[i][2]) + "\n";
            _textStream << text;
        }
    }
    _positionHistory.clear();
    _directionHistory.clear();
}

void MainWindow::readData()
{
//    mutex.lock();
    QByteArray data = _serialMotor->readAll();
    data = data + _serialSensor->readAll();
    QElapsedTimer timer;
    timer.start();
    if(!_record&&!_isPatternRecord) qDebug()<<"data: "<<data;
    _tracker.parse(data.data(),data.length());
    while(1){
        Envelope * parseResult = _tracker.getEnvelope();
        if(parseResult == NULL) break;
        QByteArray dataArray(parseResult->getPayload(),parseResult->getPayloadLength());
        char cmd = (dataArray[0]&BIG_CHAR_MASK)|0x40;
        if(!_record&&!_isPatternRecord) qDebug()<<"parse command:"<<dataArray;
        if(cmd=='M'||cmd=='O')
        {
            int x=((dataArray[1]<<8)+int(dataArray[2]&0xFF));
            int y=((dataArray[3]<<8)+int(dataArray[4]&0xFF));
            int z=((dataArray[5]<<8)+int(dataArray[6]&0xFF));

            QString magIndex = "0";
            if(cmd=='M')
            {
                double xMod = x/6842.0;
                double yMod = y/6842.0;
                double zMod = z/6842.0;
                int magNum = uint8_t((dataArray[0]>>5)&0x07);
                double magnetRawData[] = {xMod,yMod,zMod};
                if(_magDataPreprocessor.input(magnetRawData, magNum))
                {
                    double * dataProcessed = _magDataPreprocessor.data();
                    for(int i = 0; i < NUMBER_OF_SENSOR; i++)
                        if(_isShowMag) qDebug("M%d %f %f %f\n",i+1, dataProcessed[i*3], dataProcessed[i*3+1], dataProcessed[i*3+2]);
                    _isShowMag = false;
                    _estimater.setData(dataProcessed);
//                    ui->statusBar->showMessage("data...");
                    if(_estimater.estimate())
                    {
                        Vector3d pos = _estimater.getMagnetPosition();
                        Vector3d dir = _estimater.getMagnetDirection();
                        _positionHistory.push_back(pos);
                        _directionHistory.push_back(dir);
                        QString pd = "pos = (" + QString::number(pos[0]) + ", " + QString::number(pos[1]) + ", " + QString::number(pos[2]) +
                                "),  dir = ("  + QString::number(dir[0]) + ", " + QString::number(dir[1]) + ", " + QString::number(dir[2])
                                + ")";
                        ui->statusBar->showMessage(pd);
                        _manager->setPosition(pos[0],pos[1],pos[2]);
                        _manager->setDirection(dir[0],dir[1],dir[2]);
                    }
                }

                magIndex = QString::number(magNum+1);
                if(!_record&&!_isPatternRecord&&magIndex=="1"){
                    sendData("O",1);
                }
            }
            else if(cmd == 'O')
            {
                if(_isNext && (x == _position[0]&&y==_position[1]&&z==_position[2])) break;
                _position[0] = x;
                _position[1] = y;
                _position[2] = z;
                ui->lineEditX->setText(QString::number(x));
                ui->lineEditY->setText(QString::number(y));
                ui->lineEditZ->setText(QString::number(z));
            }

            QTime current = QTime::currentTime();
            QString data = QString(QChar(cmd))+magIndex+" "+QString::number(x)+" "+QString::number(y)+" "+QString::number(z)+" "+current.toString();
            if(!_record&&!_isPatternRecord) qDebug()<< data;
            _listIndex %= _listMax;
            if(_listMax == _recordData.size())
                _recordData[_listIndex++]=data;
            else{
                _recordData.append(data);
                _listIndex++;
            }
            if(!_record&&!_isPatternRecord)
            {
                if(_file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
                    _textStream.setDevice(_file);

                    _textStream.setCodec("UTF-8");
                    _textStream << data <<endl;
                    _textStream.flush();
                }
                else qDebug() << _file->errorString();
                _file->close();
            }
            else if(_listIndex == _listMax)
            {
                if(_file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
                    _textStream.setDevice(_file);
                    _textStream.setCodec("UTF-8");
                    QString tmp = "";
                    for(int i = 0; i < _listMax; i++){
                        tmp += _recordData[i]+'\n';
                    }
                    _textStream << tmp;
                    _textStream.flush();
                }
                else qDebug() << _file->errorString();
                _file->close();
                qDebug()<<"process time: "<<timer.nsecsElapsed()<<"ns";
            }
            _listIndex %= _listMax;
        } else if(cmd == 'S')
        {
            if(dataArray[1] == 1){
                ui->statusBar->showMessage("Recording finished.");
                stopRecord();
            }
            else if(dataArray[0] == 0)
            {
                stopPatternRecord();
                ui->statusBar->showMessage("Pattern recording finished.");
            }
        } else if(cmd == 'B')
        {
            if(_isPatternRecord) _count = 0;
            char command[7];
            command[0] = 'P';
            command[1] = (_position[0]>>8)&0xFF;
            command[2] = _position[0]&0xFF;
            command[3] = (_position[1]>>8)&0xFF;
            command[4] = _position[1]&0xFF;
            command[5] = (_position[2]>>8)&0xFF;
            command[6] = _position[2]&0xFF;
            sendData(command,7);
        }
    }
//    mutex.unlock();
}


void MainWindow::sendData(const char *command, int size)
{
    _en.setEnvelopeData(command,size);
    QByteArray dataToSend(_en.getEnvelopeArray(),_en.length());
    if(command[0] == 'M' || command[0] == 'B' || command[0] == 'R') _serialSensor->write(dataToSend);
    else _serialMotor->write(dataToSend);
    qDebug()<<dataToSend;
}

void MainWindow::echo_mag()
{
    char tmp[2] = {'M',_magSelection};
    sendData(tmp,2);
}

void MainWindow::move(Direction dir)
{
    switch(dir)
    {
    case UP:
        sendData("Z\x80",2);
        ui->statusBar->showMessage("up",1000);
        break;
    case DOWN:
        sendData("Z\x00",2);
        ui->statusBar->showMessage("down",1000);
        break;
    case RIGHT:
        sendData("X\x80",2);
        ui->statusBar->showMessage("right",1000);
        break;
    case LEFT:
        sendData("X\x00",2);
        ui->statusBar->showMessage("left",1000);
        break;
    case BACKWARD:
        sendData("Y\x00",2);
        ui->statusBar->showMessage("backward",1000);
        break;
    case FORWARD:
        sendData("Y\x80",2);
        ui->statusBar->showMessage("forward",1000);
        break;
    default:
        break;
    }
}

void MainWindow::stopRecord()
{
    if(!_record) return;
    _record=false;
    ui->pushButtonRecord->setText("Record");
    //    qDebug()<<QByteArray::fromRawData(en.getEnvelopeArray(),en.length()) << endl;
    if(_file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        _textStream.setDevice(_file);
        _textStream.setCodec("UTF-8");
        for(int i = 0; i < _listIndex; i++){
            _textStream << _recordData[i] <<endl;
        }
        _textStream.flush();
        _file->close();
    }
    else qDebug() << _file->errorString();
    _listIndex = 0;
    ui->pushButtonEcho->setEnabled(true);
}

void MainWindow::gotoXYZ(int x, int y, int z)
{
    char command[7];
    command[0] = 'C';
    command[1] = (x>>8)&0xFF;
    command[2] = x&0xFF;
    command[3] = (y>>8)&0xFF;
    command[4] = y&0xFF;
    command[5] = (z>>8)&0xFF;
    command[6] = z&0xFF;
    sendData(command,7);
//    qDebug() << QByteArray::fromRawData(en.getEnvelopeArray(),en.length());
}

void MainWindow::patternRecord()
{
//    gotoXYZ(xStart,yStart,zStart);
//    Sleep(10);
    if((_yStart-_yEnd)*_yStep>0) _yStep = -_yStep;
    if((_zStart-_zEnd)*_zStep>0) _zStep = -_zStep;
//    count = num;
//    isNext = true;
    _isPatternRecord = true;
//    gotoXYZ(xStart,yStart,zStart);
    char command[7];
    command[0] = 'I';
    command[1] = 'X';
    command[2] = (_xStart>>8)&0xFF;
    command[3] = _xStart&0xFF;
    command[4] = (_xEnd>>8)&0xFF;
    command[5] = _xEnd&0xFF;
    command[6] = abs(_xStep)&0xFF;
    sendData(command,7);
    command[1] = 'Y';
    command[2] = (_yStart>>8)&0xFF;
    command[3] = _yStart&0xFF;
    command[4] = (_yEnd>>8)&0xFF;
    command[5] = _yEnd&0xFF;
    command[6] = abs(_yStep)&0xFF;
    sendData(command,7);
    command[1] = 'Z';
    command[2] = (_zStart>>8)&0xFF;
    command[3] = _zStart&0xFF;
    command[4] = (_zEnd>>8)&0xFF;
    command[5] = _zEnd&0xFF;
    command[6] = abs(_zStep)&0xFF;
    sendData(command,7);
    command[1] = 'N';
    command[2] = (_num>>8)&0xFF;
    command[3] = _num&0xFF;
    sendData(command,4);
    if(ui->lineEditX->text()!="0"){
        command[1] = 'M';
        command[2] = 'B';
        command[3] = (ui->lineEditX->text().toInt()>>8)&0xFF;
        command[4] = ui->lineEditX->text().toInt()&0xFF;
        command[5] = (ui->lineEditY->text().toInt()>>8)&0xFF;
        command[6] = ui->lineEditY->text().toInt()&0xFF;
        sendData(command,7);
        command[1] = 'M';
        command[2] = 'U';
        command[3] = (ui->lineEditZ->text().toInt()>>8)&0xFF;
        command[4] = ui->lineEditZ->text().toInt()&0xFF;
        sendData(command,5);
    }
    else{
        command[1] = 'B';
        sendData(command,2);
    }
}

void MainWindow::stopPatternRecord()
{
    ui->testButton->setText("Pattern Record");
    _isPatternRecord = false;
    if(_file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        _textStream.setDevice(_file);
        _textStream.setCodec("UTF-8");
        for(int i = 0; i < _listIndex; i++){
            _textStream << _recordData[i] <<endl;
        }
        _textStream.flush();
        _file->close();
    }
    else qDebug() << _file->errorString();
    _listIndex = 0;
}

void MainWindow::on_upButton_clicked()
{
    move(UP);
}

void MainWindow::on_rightButton_clicked()
{
    move(RIGHT);
}

void MainWindow::on_downButton_clicked()
{
    move(DOWN);
}

void MainWindow::on_leftButton_clicked()
{
    move(LEFT);
}

void MainWindow::on_forwardButton_clicked()
{
    move(FORWARD);
}

void MainWindow::on_backwardButton_clicked()
{
    move(BACKWARD);
}

void MainWindow::on_horizontalSliderSpeed_actionTriggered(int action)
{
    char tmp[2] = {'V',static_cast<char>(ui->horizontalSliderSpeed->sliderPosition()*5)};
//    qDebug()<<ui->horizontalSliderSpeed->sliderPosition();
    sendData(tmp,2);
}

void MainWindow::on_pushButtonGo_clicked()
{
    int x=ui->lineEditX->text().toInt();
    int y=ui->lineEditY->text().toInt();
    int z=ui->lineEditZ->text().toInt();
    gotoXYZ(x,y,z);
    ui->statusBar->showMessage("GO~",1000);
}

void MainWindow::on_pushButtonEcho_clicked()
{
    //sendData("O",1);
    echo_mag();
}

void MainWindow::on_pushButtonRecord_clicked()
{
    if(_record)
    {
        sendData("S",1);
        stopRecord();
        return;
    }
    _record=true;
    ui->pushButtonEcho->setEnabled(false);
    int time = ui->horizontalSliderRecordTime->sliderPosition();
    char tmp[] = { 'R', static_cast<char>(time&0xFF), _magSelection };
    sendData(tmp,3);
    qDebug()<<QByteArray::fromRawData(_en.getEnvelopeArray(),_en.length()) << endl;
    ui->pushButtonRecord->setText("Stop");
    _isShowMag = true;
}

void MainWindow::on_testButton_clicked()
{
//    manager->setDirection(0.5,0.5,0.5);
    if(!_isPatternRecord){
        ui->testButton->setText("stop pattern recording");
        patternRecord();
    }
    else
    {
        sendData("IS",2);
        stopPatternRecord();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case 'w':
    case 'W':
        move(FORWARD);
        break;
    case 'S':
    case 's':
        move(BACKWARD);
        break;
    case 'a':
    case 'A':
        move(LEFT);
        break;
    case 'd':
    case 'D':
        move(RIGHT);
        break;
    case 'r':
    case 'R':
        move(UP);
        break;
    case 'f':
    case 'F':
        move(DOWN);
        break;
    case 'p':
    case 'P':
        char tmp[] = { 'R', static_cast<char>(60&0xFF), _magSelection };
        sendData(tmp,3);
        qDebug()<<"p pressed";
        break;
    }
}

void MainWindow::setMagSel(MagnetometersSelection ms, bool sel)
{
    _magSelection &= ~(ms);
    _magSelection |= (sel ? ms : 0);
    ui->statusBar->showMessage(QString::number((uint)_magSelection,16),1000);
}

void MainWindow::on_actionOpen_triggered()
{
    QString inputFileName = QFileDialog::getOpenFileName(this, "open record pattern", "", tr("Pattern files (*.ptn)"));
//    QString inputFileName = "D:\\Magnet localization\\electroMag.ptn";
    QFile *inputFile = new QFile(inputFileName);
    if(inputFile->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        _textStream.setDevice(inputFile);
        _textStream.setCodec("UTF-8");
        _textStream >> _xStart >> _xEnd >> _xStep >> _yStart >> _yEnd >> _yStep >> _zStart >> _zEnd >> _zStep >> _num;
        qDebug() << _xStart << _xEnd << _xStep << _yStart << _yEnd << _yStep << _zStart << _zEnd << _zStep << _num;

        inputFile->close();
        delete inputFile;
        qDebug()<<"opened";
    }
    ui->lineEditX->setText("0");
    ui->lineEditY->setText("0");
    ui->lineEditZ->setText("0");
}

void MainWindow::on_actionSave_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save as...","",tr("Log files (*.log)"));
    if(saveFileName=="") return;
    _file->close();
    delete _file;
    _file = new QFile(saveFileName);
    qDebug()<<"saved file!!";
}

void MainWindow::on_pushButtonReset_clicked()
{
    sendData("N",1);
}

void MainWindow::on_actionAll_triggered()
{
    if(ui->actionAll->isChecked())
    {
        ui->actionM1->setChecked(true);
        ui->actionM2->setChecked(true);
        ui->actionM3->setChecked(true);
        ui->actionM4->setChecked(true);
        ui->actionM5->setChecked(true);
        ui->actionM6->setChecked(true);
        ui->actionM7->setChecked(true);
        ui->actionM8->setChecked(true);
    }
    else
    {
        ui->actionM1->setChecked(false);
        ui->actionM2->setChecked(false);
        ui->actionM3->setChecked(false);
        ui->actionM4->setChecked(false);
        ui->actionM5->setChecked(false);
        ui->actionM6->setChecked(false);
        ui->actionM7->setChecked(false);
        ui->actionM8->setChecked(false);
    }
}

void MainWindow::on_actionM1_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M1, arg1);
}

void MainWindow::on_actionM2_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M2, arg1);
}

void MainWindow::on_actionM3_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M3, arg1);
}

void MainWindow::on_actionM4_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M4, arg1);
}
void MainWindow::on_actionM5_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M5, arg1);
}

void MainWindow::on_actionM6_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M6, arg1);
}

void MainWindow::on_actionM7_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M7, arg1);
}

void MainWindow::on_actionM8_toggled(bool arg1)
{
    setMagSel(MagnetometersSelection::M8, arg1);
}

void MainWindow::on_actionReset_triggered()
{
    char tmp[] = {'B', _magSelection};
    sendData(tmp,2);
    qDebug()<<QByteArray::fromRawData(_en.getEnvelopeArray(),_en.length()) << endl;
}

void MainWindow::on_actionload_calibration_file_triggered()
{
    QString calibrationFileName = QFileDialog::getOpenFileName(this, "load calibration file", "", tr("Text file (*.txt)"));
    QFile * calibrationFile = new QFile(calibrationFileName);
    double *U = new double [3*3*NUMBER_OF_SENSOR];
    double *c = new double [3*NUMBER_OF_SENSOR];
    double *rot = new double [3*3*NUMBER_OF_SENSOR];
    QString line;
    if(calibrationFile->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        _textStream.setDevice(calibrationFile);
        _textStream.setCodec("UTF-8");
        for(int i = 0; i < NUMBER_OF_SENSOR; i++)
        {
            line = _textStream.readLine();
            for(int j = 0; j < 9; j++) _textStream >> U[i*9+j];
            line = _textStream.readLine();
        }
        for(int i = 0; i < NUMBER_OF_SENSOR; i++)
        {
            line = _textStream.readLine();
            for(int j = 0; j < 9; j++) _textStream >> rot[i*9+j];
            line = _textStream.readLine();
        }
        line = _textStream.readLine();
        for(int i = 0; i < 3*NUMBER_OF_SENSOR; i++) _textStream >> c[i];
        _magDataPreprocessor.setUAndC(U,c);
//        _estimater.setRotMat(rot);


        calibrationFile->close();
        delete calibrationFile;
    }
    delete [] U;
    delete [] rot;
    delete [] c;
}

void MainWindow::on_comboBoxComPort_editTextChanged(const QString &arg1)
{
    qDebug()<<"editTextChanged";
}

void MainWindow::on_pushButton_clicked()
{
    QFile f("data.txt");
    bool isFileOpen = f.open(QIODevice::ReadOnly|QIODevice::Text);
    _textStream.setDevice(&f);
    MatrixXd X(2000,3);
    for(int i = 0; i < 2000; i++)
    {
        _textStream >> X(i,0) >> X(i,1) >> X(i,2);
    }
    MgnCalibration m;
    if(m.calibrate(X))
        ;

}
