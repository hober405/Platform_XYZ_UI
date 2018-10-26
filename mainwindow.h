#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager3d.h"
#include "magnetestimator.h"
#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <QKeyEvent>
#include "envelopetracker.h"
#include "envelope.h"

#define MAX_SPEED 2.5
#define BIG_CHAR_MASK 0x1F
#define MAGNET_INDEX_MASK 0xE0

namespace Ui {
class MainWindow;
}

enum Direction{ UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};
enum MagnetometersSelection{
    M1 = 0x001,
    M2 = 0x002,
    M3 = 0x004,
    M4 = 0x008,
    M5 = 0x010,
    M6 = 0x020,
    M7 = 0x040,
    M8 = 0x080
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Qt3DCore::QEntity *rootEntity, QWidget *parent = 0);
    void addContainer(QWidget *container);
    ~MainWindow();

private slots:
    void on_actionConnect_to_NUCLEO_triggered();
    void on_actionDisconnect_triggered();
    void readData();

    void on_upButton_clicked();

    void on_rightButton_clicked();

    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_forwardButton_clicked();

    void on_backwardButton_clicked();

    void on_horizontalSliderSpeed_actionTriggered(int action);

    void on_pushButtonGo_clicked();
    void on_pushButtonEcho_clicked();

    void on_pushButtonRecord_clicked();

    void on_testButton_clicked();
    void on_actionOpen_triggered();

    void on_actionSave_triggered();
//    void checkAndResend();
private slots:
    void echo_mag();

    void on_pushButtonReset_clicked();

    void on_actionAll_triggered();

    void on_actionM1_toggled(bool arg1);

    void on_actionM2_toggled(bool arg1);

    void on_actionM3_toggled(bool arg1);

    void on_actionM4_toggled(bool arg1);

    void on_actionM5_toggled(bool arg1);

    void on_actionM6_toggled(bool arg1);

    void on_actionM7_toggled(bool arg1);

    void on_actionM8_toggled(bool arg1);

    void on_actionReset_triggered();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void setMagSel(MagnetometersSelection ms, bool sel);
    void sendData(const char* command, int size);
    void move(Direction dir);
    void stopRecord();
    void gotoXYZ(int x, int y, int z);
    void patternRecord();
    void stopPatternRecord();

    Ui::MainWindow *ui;
    QSerialPort *serial;
    EnvelopeTracker tracker;
    Envelope en;
    QFile* file;
    QTextStream textStream;
    bool record = false;
    QList<QString> record_data;
    int list_max = 1000;
    int list_index = 0;
    QMutex mutex;
    Manager3D* manager;
    int position[3];
    int xStart, xEnd, xStep, yStart, yEnd, yStep, zStart, zEnd, zStep, num;
    bool isPatternRecord;
    int count;
    bool isNext;

    char magSelection;
    MagnetEstimator estimater;
    float magData[8][3];
};

#endif // MAINWINDOW_H
