/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect_to_NUCLEO;
    QAction *actionDisconnect;
    QWidget *centralWidget;
    QPushButton *testButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBoxDirection;
    QPushButton *backwardButton;
    QPushButton *leftButton;
    QPushButton *downButton;
    QPushButton *upButton;
    QPushButton *forwardButton;
    QPushButton *rightButton;
    QGroupBox *groupBoxPosition;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *labelX;
    QLineEdit *lineEditX;
    QLabel *labelY;
    QLineEdit *lineEditY;
    QLabel *labelZ;
    QLineEdit *lineEditZ;
    QPushButton *pushButtonGo;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxSpeed;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSliderSpeed;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *horizontalSliderRecordTime;
    QPushButton *pushButtonRecord;
    QPushButton *pushButtonEcho;
    QGraphicsView *graphicsViewXYZ;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(968, 655);
        QIcon icon;
        QString iconThemeName = QStringLiteral("qwe");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        actionConnect_to_NUCLEO = new QAction(MainWindow);
        actionConnect_to_NUCLEO->setObjectName(QStringLiteral("actionConnect_to_NUCLEO"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setEnabled(true);
        testButton->setGeometry(QRect(10, 570, 951, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 201, 551));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBoxDirection = new QGroupBox(layoutWidget);
        groupBoxDirection->setObjectName(QStringLiteral("groupBoxDirection"));
        backwardButton = new QPushButton(groupBoxDirection);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(70, 90, 61, 81));
        backwardButton->setStyleSheet(QLatin1String("#backwardButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/backward.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        leftButton = new QPushButton(groupBoxDirection);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(10, 90, 61, 81));
        leftButton->setStyleSheet(QLatin1String("\n"
"#leftButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/left.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        downButton = new QPushButton(groupBoxDirection);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(130, 10, 61, 81));
        downButton->setStyleSheet(QLatin1String("#downButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/down.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        upButton = new QPushButton(groupBoxDirection);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(10, 10, 61, 81));
        upButton->setStyleSheet(QLatin1String("#upButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/up.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        forwardButton = new QPushButton(groupBoxDirection);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(70, 10, 61, 81));
        forwardButton->setStyleSheet(QLatin1String("#forwardButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/forward.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        rightButton = new QPushButton(groupBoxDirection);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(130, 90, 61, 81));
        rightButton->setStyleSheet(QLatin1String("#rightButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/right.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));

        verticalLayout_4->addWidget(groupBoxDirection);

        groupBoxPosition = new QGroupBox(layoutWidget);
        groupBoxPosition->setObjectName(QStringLiteral("groupBoxPosition"));
        widget = new QWidget(groupBoxPosition);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 14, 181, 151));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        labelX = new QLabel(widget);
        labelX->setObjectName(QStringLiteral("labelX"));

        gridLayout_3->addWidget(labelX, 0, 0, 1, 1);

        lineEditX = new QLineEdit(widget);
        lineEditX->setObjectName(QStringLiteral("lineEditX"));
        lineEditX->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(lineEditX, 0, 1, 1, 1);

        labelY = new QLabel(widget);
        labelY->setObjectName(QStringLiteral("labelY"));

        gridLayout_3->addWidget(labelY, 1, 0, 1, 1);

        lineEditY = new QLineEdit(widget);
        lineEditY->setObjectName(QStringLiteral("lineEditY"));
        lineEditY->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(lineEditY, 1, 1, 1, 1);

        labelZ = new QLabel(widget);
        labelZ->setObjectName(QStringLiteral("labelZ"));

        gridLayout_3->addWidget(labelZ, 2, 0, 1, 1);

        lineEditZ = new QLineEdit(widget);
        lineEditZ->setObjectName(QStringLiteral("lineEditZ"));
        lineEditZ->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(lineEditZ, 2, 1, 1, 1);

        pushButtonGo = new QPushButton(widget);
        pushButtonGo->setObjectName(QStringLiteral("pushButtonGo"));

        gridLayout_3->addWidget(pushButtonGo, 3, 0, 1, 2);


        verticalLayout_4->addWidget(groupBoxPosition);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBoxSpeed = new QGroupBox(layoutWidget);
        groupBoxSpeed->setObjectName(QStringLiteral("groupBoxSpeed"));
        gridLayout = new QGridLayout(groupBoxSpeed);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(groupBoxSpeed);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBoxSpeed);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        horizontalSliderSpeed = new QSlider(groupBoxSpeed);
        horizontalSliderSpeed->setObjectName(QStringLiteral("horizontalSliderSpeed"));
        horizontalSliderSpeed->setMinimum(1);
        horizontalSliderSpeed->setMaximum(20);
        horizontalSliderSpeed->setPageStep(5);
        horizontalSliderSpeed->setValue(1);
        horizontalSliderSpeed->setSliderPosition(1);
        horizontalSliderSpeed->setOrientation(Qt::Horizontal);
        horizontalSliderSpeed->setTickPosition(QSlider::TicksAbove);
        horizontalSliderSpeed->setTickInterval(1);

        gridLayout_2->addWidget(horizontalSliderSpeed, 1, 0, 1, 2);


        gridLayout->addLayout(gridLayout_2, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBoxSpeed);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 181, 68));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalSliderRecordTime = new QSlider(layoutWidget1);
        horizontalSliderRecordTime->setObjectName(QStringLiteral("horizontalSliderRecordTime"));
        horizontalSliderRecordTime->setMinimum(1);
        horizontalSliderRecordTime->setMaximum(10);
        horizontalSliderRecordTime->setPageStep(2);
        horizontalSliderRecordTime->setOrientation(Qt::Horizontal);
        horizontalSliderRecordTime->setTickPosition(QSlider::TicksAbove);
        horizontalSliderRecordTime->setTickInterval(1);

        verticalLayout_3->addWidget(horizontalSliderRecordTime);


        horizontalLayout_6->addLayout(verticalLayout_3);

        pushButtonRecord = new QPushButton(layoutWidget1);
        pushButtonRecord->setObjectName(QStringLiteral("pushButtonRecord"));

        horizontalLayout_6->addWidget(pushButtonRecord);


        verticalLayout_2->addWidget(groupBox);


        verticalLayout_4->addLayout(verticalLayout_2);

        pushButtonEcho = new QPushButton(layoutWidget);
        pushButtonEcho->setObjectName(QStringLiteral("pushButtonEcho"));

        verticalLayout_4->addWidget(pushButtonEcho);

        graphicsViewXYZ = new QGraphicsView(centralWidget);
        graphicsViewXYZ->setObjectName(QStringLiteral("graphicsViewXYZ"));
        graphicsViewXYZ->setGeometry(QRect(220, 10, 741, 551));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 968, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionConnect_to_NUCLEO);
        menuFile->addAction(actionDisconnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Platform XYZ", 0));
        actionConnect_to_NUCLEO->setText(QApplication::translate("MainWindow", "Connect to NUCLEO", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        testButton->setText(QApplication::translate("MainWindow", "Test", 0));
        groupBoxDirection->setTitle(QApplication::translate("MainWindow", "Direction", 0));
        backwardButton->setText(QString());
        leftButton->setText(QString());
        downButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        upButton->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline;\">r</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        upButton->setText(QString());
        forwardButton->setText(QString());
        rightButton->setText(QString());
        groupBoxPosition->setTitle(QApplication::translate("MainWindow", "Position (mm)", 0));
        labelX->setText(QApplication::translate("MainWindow", "X:", 0));
        lineEditX->setText(QApplication::translate("MainWindow", "0", 0));
        labelY->setText(QApplication::translate("MainWindow", "Y:", 0));
        lineEditY->setText(QApplication::translate("MainWindow", "0", 0));
        labelZ->setText(QApplication::translate("MainWindow", "Z:", 0));
        lineEditZ->setText(QApplication::translate("MainWindow", "0", 0));
        pushButtonGo->setText(QApplication::translate("MainWindow", "GO!!", 0));
        groupBoxSpeed->setTitle(QApplication::translate("MainWindow", "Speed (cm/s)", 0));
        label->setText(QApplication::translate("MainWindow", "0.125", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">2.5</p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Record (sec)", 0));
        label_3->setText(QApplication::translate("MainWindow", "1", 0));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">10</p></body></html>", 0));
        pushButtonRecord->setText(QApplication::translate("MainWindow", "record", 0));
        pushButtonEcho->setText(QApplication::translate("MainWindow", "echo", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
