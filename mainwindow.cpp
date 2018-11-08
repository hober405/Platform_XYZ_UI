#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <windows.h>
#include <QMessageBox>
#include <qdebug.h>
#include <QFileDialog>

MainWindow::MainWindow(Qt3DCore::QEntity *rootEntity, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    magSelection(0x00),
    estimater(8),
    magData(8)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    en.enableHeader(std::string("H"));
    en.enableFooter(std::string("E"),8);
    en.enableCheckXOR(9);
    tracker.setEnvelope(en);
    tracker.setBufferLength(100);
    QString fileName("D:\\Magnet localization\\Platform_XYZ_UI\\log\\Motor_log ");
    fileName += QDate::currentDate().toString()+".log";
    file = new QFile(fileName);
    qDebug()<<fileName<<endl;
    record_data.reserve(list_max);
    manager = new Manager3D(rootEntity);
    isPatternRecord = false;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->comboBoxComPort->addItem(info.portName());
    }
    estimater.inititialize();
    double data[8][3] = {
        {0,	-0.487869044139141,	-1.26059631686641},
        {-0.285004384682841,	-0.204326220403391,	-0.990353697749197},
        {-0.183864367144110,	0.0368313358667054,	-0.625255773165741},
        {-0.0716164864074833,	0.0919321835720544,	-0.439929845074540},
        {0,	0.0983630517392573,	-0.388336743642210},
        {0.0716164864074829,	0.0919321835720544,	-0.439929845074540},
        {0.183864367144110,	0.0368313358667054,	-0.625255773165741},
        {0.285004384682841,	-0.204326220403391,	-0.990353697749197}
    };
    estimater.setData((double *)data);
    estimater.estimate();
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
    serial->setPortName(ui->comboBoxComPort->currentText());
    serial->setBaudRate(921600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        //        console->setEnabled(true);
        //        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect_to_NUCLEO->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        //        ui->actionConfigure->setEnabled(false);
        ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                   .arg(serial->portName()).arg(serial->baudRate()).arg(QSerialPort::Data8)
                                   .arg(QSerialPort::NoParity).arg(QSerialPort::OneStop).arg(QSerialPort::NoFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (serial->isOpen())
        serial->close();
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
       textStream.setDevice(&textFile);
       textStream.setCodec("UTF-8");
       textStream << "position:\n";
       QString text;
       for(int i = 0; i < positionHistory.size(); i++)
       {
           text = QString::number(positionHistory[i][0]) + " " +
                  QString::number(positionHistory[i][1]) + " " +
                  QString::number(positionHistory[i][2]) + "\n";
           textStream << text;
       }
       positionHistory.clear();
       textStream << "direction:\n";
       for(int i = 0; i < directionHistory.size(); i++)
       {
           text = QString::number(directionHistory[i][0]) + " " +
                  QString::number(directionHistory[i][1]) + " " +
                  QString::number(directionHistory[i][2]) + "\n";
           textStream << text;
       }
       directionHistory.clear();
   }
}

void MainWindow::readData()
{
//    mutex.lock();
    QByteArray data = serial->readAll();
    QElapsedTimer timer;
    timer.start();
    if(!record&&!isPatternRecord) qDebug()<<"data: "<<data;
    char * stringToParse = new char [data.length()];
    for(int i = 0; i < data.length(); i++){ stringToParse[i] = data[i];
        tracker.parse(&stringToParse[i], 1);}
    while(1){
        Envelope * parseResult = tracker.getEnvelope();
        if(parseResult == NULL) break;
        QByteArray dataArray(parseResult->getPayload(),parseResult->getPayloadLength());
        char cmd = dataArray[0]&BIG_CHAR_MASK|0x40;
        if(!record&&!isPatternRecord) qDebug()<<"parse command:"<<dataArray;
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
                manager->setDirection(xMod,yMod,zMod);
                int magNum = uint8_t((dataArray[0]>>5)&0x07);
                double data[] = {xMod,yMod,zMod};
                if(magData.input(data, magNum))
                {
                    estimater.setData((double *)magData.data());
                    ui->statusBar->showMessage("data...");
                    if(estimater.estimate())
                    {
                        Vector3d pos = estimater.getMagnetPosition();
                        Vector3d dir = estimater.getMagnetDirection();
                        positionHistory.push_back(pos);
                        directionHistory.push_back(dir);
                        QString pd = "pos = (" + QString::number(pos[0]) + ", " + QString::number(pos[1]) + ", " + QString::number(pos[2]) +
                                "),  dir = ("  + QString::number(dir[0]) + ", " + QString::number(dir[1]) + ", " + QString::number(dir[2])
                                + ")";
                        ui->statusBar->showMessage(pd);
                    }
                }
//                magData[magNum][0] = xMod;
//                magData[magNum][1] = yMod;
//                magData[magNum][2] = zMod;

                magIndex = QString::number(magNum+1);
                if(!record&&!isPatternRecord&&magIndex=="1"){
                    sendData("O",1);
                }
            }
            else if(cmd == 'O')
            {
                manager->setPosition(x/100.0,y/100.0,z/100.0);
                if(isNext && (x == position[0]&&y==position[1]&&z==position[2])) break;
                position[0] = x;
                position[1] = y;
                position[2] = z;
                ui->lineEditX->setText(QString::number(x));
                ui->lineEditY->setText(QString::number(y));
                ui->lineEditZ->setText(QString::number(z));
            }

            QTime current = QTime::currentTime();
            QString data = QString(QChar(cmd))+magIndex+" "+QString::number(x)+" "+QString::number(y)+" "+QString::number(z)+" "+current.toString();
            if(!record&&!isPatternRecord) qDebug()<< data;
            list_index%=list_max;
            if(list_index < record_data.size())
                record_data[list_index++]=data;
            else
                record_data.append(data);
            if(!record&&!isPatternRecord)
            {
                if(file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
                    textStream.setDevice(file);

                    textStream.setCodec("UTF-8");
                    textStream << data <<endl;
                    textStream.flush();
                }
                else qDebug() << file->errorString();
                file->close();
            }
            else if(list_index == list_max)
            {
                if(file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
                    textStream.setDevice(file);
                    textStream.setCodec("UTF-8");
                    QString tmp = "";
                    for(int i = 0; i < list_max; i++){
                        tmp += record_data[i]+'\n';
                    }
                    textStream << tmp;
                    textStream.flush();
                }
                else qDebug() << file->errorString();
                file->close();
                qDebug()<<"process time: "<<timer.nsecsElapsed()<<"ns";
            }
        } else if(cmd == 'S')
        {
            if(record){
                ui->statusBar->showMessage("Recording finished.");
                stopRecord();
            }
            else
            {
                stopPatternRecord();
                ui->statusBar->showMessage("Pattern recording finished.");
            }
        } else if(cmd == 'B')
        {
            if(isPatternRecord) count = 0;
            char command[7];
            command[0] = 'P';
            command[1] = (position[0]>>8)&0xFF;
            command[2] = position[0]&0xFF;
            command[3] = (position[1]>>8)&0xFF;
            command[4] = position[1]&0xFF;
            command[5] = (position[2]>>8)&0xFF;
            command[6] = position[2]&0xFF;
            sendData(command,7);
        }
    }
//    mutex.unlock();
}


void MainWindow::sendData(const char *command, int size)
{
    en.setEnvelopeData(command,size);
    QByteArray dataToSend(en.getEnvelopeArray(),en.length());
    serial->write(dataToSend);
    qDebug()<<dataToSend;
}

void MainWindow::echo_mag()
{
    char tmp[2] = {'M',magSelection};
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
    if(!record) return;
    record=false;
    ui->pushButtonRecord->setText("Record");
    //    qDebug()<<QByteArray::fromRawData(en.getEnvelopeArray(),en.length()) << endl;
    if(file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        textStream.setDevice(file);
        textStream.setCodec("UTF-8");
        for(int i = 0; i < list_index; i++){
            textStream << record_data[i] <<endl;
        }
        textStream.flush();
        file->close();
    }
    else qDebug() << file->errorString();
    list_index = 0;
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
    if((yStart-yEnd)*yStep>0) yStep = -yStep;
    if((zStart-zEnd)*zStep>0) zStep = -zStep;
//    count = num;
//    isNext = true;
    isPatternRecord = true;
//    gotoXYZ(xStart,yStart,zStart);
    char command[7];
    command[0] = 'I';
    command[1] = 'X';
    command[2] = (xStart>>8)&0xFF;
    command[3] = xStart&0xFF;
    command[4] = (xEnd>>8)&0xFF;
    command[5] = xEnd&0xFF;
    command[6] = abs(xStep)&0xFF;
    sendData(command,7);
    command[1] = 'Y';
    command[2] = (yStart>>8)&0xFF;
    command[3] = yStart&0xFF;
    command[4] = (yEnd>>8)&0xFF;
    command[5] = yEnd&0xFF;
    command[6] = abs(yStep)&0xFF;
    sendData(command,7);
    command[1] = 'Z';
    command[2] = (zStart>>8)&0xFF;
    command[3] = zStart&0xFF;
    command[4] = (zEnd>>8)&0xFF;
    command[5] = zEnd&0xFF;
    command[6] = abs(zStep)&0xFF;
    sendData(command,7);
    command[1] = 'N';
    command[2] = (num>>8)&0xFF;
    command[3] = num&0xFF;
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
    ui->testButton->setText("test");
    isPatternRecord = false;
    if(file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        textStream.setDevice(file);
        textStream.setCodec("UTF-8");
        for(int i = 0; i < list_index; i++){
            textStream << record_data[i] <<endl;
        }
        textStream.flush();
        file->close();
    }
    else qDebug() << file->errorString();
    list_index = 0;
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
    char tmp[2] = {'V',(char)ui->horizontalSliderSpeed->sliderPosition()*5};
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
    if(record)
    {
        sendData("S",1);
        stopRecord();
        return;
    }
    record=true;
    ui->pushButtonEcho->setEnabled(false);
    int time = ui->horizontalSliderRecordTime->sliderPosition();
    char tmp[] = { 'R', static_cast<char>(time&0xFF), magSelection };
    sendData(tmp,3);
    qDebug()<<QByteArray::fromRawData(en.getEnvelopeArray(),en.length()) << endl;
    ui->pushButtonRecord->setText("Stop");
}

void MainWindow::on_testButton_clicked()
{
//    manager->setDirection(0.5,0.5,0.5);
    if(!isPatternRecord){
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
        char tmp[] = { 'R', static_cast<char>(60&0xFF), magSelection };
        sendData(tmp,3);
        qDebug()<<"p pressed";
        break;
    }
}

void MainWindow::setMagSel(MagnetometersSelection ms, bool sel)
{
    magSelection &= ~(ms);
    magSelection |= (sel ? ms : 0);
    ui->statusBar->showMessage(QString::number((uint)magSelection,16),1000);
}

void MainWindow::on_actionOpen_triggered()
{
    QString inputFileName = QFileDialog::getOpenFileName(this, "open record pattern", "", tr("Pattern files (*.ptn)"));
//    QString inputFileName = "D:\\Magnet localization\\electroMag.ptn";
    QFile *inputFile = new QFile(inputFileName);
    if(inputFile->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        textStream.setDevice(inputFile);
        textStream.setCodec("UTF-8");
        textStream >> xStart >> xEnd >> xStep >> yStart >> yEnd >> yStep >> zStart >> zEnd >> zStep >> num;
        qDebug() << xStart << xEnd << xStep << yStart << yEnd << yStep << zStart << zEnd << zStep << num;

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
    file->close();
    delete file;
    file = new QFile(saveFileName);
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
    char tmp[] = {'B', magSelection};
    sendData(tmp,2);
    qDebug()<<QByteArray::fromRawData(en.getEnvelopeArray(),en.length()) << endl;
}
