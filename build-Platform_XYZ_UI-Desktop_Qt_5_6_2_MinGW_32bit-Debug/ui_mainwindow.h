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
    QGroupBox *groupBoxPosition;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelX;
    QLineEdit *lineEditX;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelY;
    QLineEdit *lineEditY;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelZ;
    QLineEdit *lineEditZ;
    QPushButton *pushButtonGo;
    QGroupBox *groupBoxDirection;
    QPushButton *backwardButton;
    QPushButton *leftButton;
    QPushButton *downButton;
    QPushButton *upButton;
    QPushButton *forwardButton;
    QPushButton *rightButton;
    QGroupBox *groupBoxSpeed;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSliderSpeed;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(490, 389);
        QIcon icon(QIcon::fromTheme(QStringLiteral("qwe")));
        MainWindow->setWindowIcon(icon);
        actionConnect_to_NUCLEO = new QAction(MainWindow);
        actionConnect_to_NUCLEO->setObjectName(QStringLiteral("actionConnect_to_NUCLEO"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBoxPosition = new QGroupBox(centralWidget);
        groupBoxPosition->setObjectName(QStringLiteral("groupBoxPosition"));
        groupBoxPosition->setGeometry(QRect(280, 20, 121, 141));
        horizontalLayout_5 = new QHBoxLayout(groupBoxPosition);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelX = new QLabel(groupBoxPosition);
        labelX->setObjectName(QStringLiteral("labelX"));

        horizontalLayout_2->addWidget(labelX);

        lineEditX = new QLineEdit(groupBoxPosition);
        lineEditX->setObjectName(QStringLiteral("lineEditX"));
        lineEditX->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_2->addWidget(lineEditX);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelY = new QLabel(groupBoxPosition);
        labelY->setObjectName(QStringLiteral("labelY"));

        horizontalLayout_3->addWidget(labelY);

        lineEditY = new QLineEdit(groupBoxPosition);
        lineEditY->setObjectName(QStringLiteral("lineEditY"));
        lineEditY->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_3->addWidget(lineEditY);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labelZ = new QLabel(groupBoxPosition);
        labelZ->setObjectName(QStringLiteral("labelZ"));

        horizontalLayout_4->addWidget(labelZ);

        lineEditZ = new QLineEdit(groupBoxPosition);
        lineEditZ->setObjectName(QStringLiteral("lineEditZ"));
        lineEditZ->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_4->addWidget(lineEditZ);


        verticalLayout->addLayout(horizontalLayout_4);

        pushButtonGo = new QPushButton(groupBoxPosition);
        pushButtonGo->setObjectName(QStringLiteral("pushButtonGo"));

        verticalLayout->addWidget(pushButtonGo);


        horizontalLayout_5->addLayout(verticalLayout);

        groupBoxDirection = new QGroupBox(centralWidget);
        groupBoxDirection->setObjectName(QStringLiteral("groupBoxDirection"));
        groupBoxDirection->setGeometry(QRect(20, 20, 201, 191));
        backwardButton = new QPushButton(groupBoxDirection);
        backwardButton->setObjectName(QStringLiteral("backwardButton"));
        backwardButton->setGeometry(QRect(70, 100, 61, 81));
        backwardButton->setStyleSheet(QLatin1String("#backwardButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/backward.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        leftButton = new QPushButton(groupBoxDirection);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        leftButton->setGeometry(QRect(10, 100, 61, 81));
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
        downButton->setGeometry(QRect(130, 20, 61, 81));
        downButton->setStyleSheet(QLatin1String("#downButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/down.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        upButton = new QPushButton(groupBoxDirection);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(10, 20, 61, 81));
        upButton->setStyleSheet(QLatin1String("#upButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/up.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        forwardButton = new QPushButton(groupBoxDirection);
        forwardButton->setObjectName(QStringLiteral("forwardButton"));
        forwardButton->setGeometry(QRect(70, 20, 61, 81));
        forwardButton->setStyleSheet(QLatin1String("#forwardButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/forward.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        rightButton = new QPushButton(groupBoxDirection);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        rightButton->setGeometry(QRect(130, 100, 61, 81));
        rightButton->setStyleSheet(QLatin1String("#rightButton{\n"
"background-color:transparent;\n"
"border-image:url(:/arrows/right.png);\n"
"background:none;\n"
"border:none;\n"
"background-repeat:none;\n"
"}"));
        groupBoxSpeed = new QGroupBox(centralWidget);
        groupBoxSpeed->setObjectName(QStringLiteral("groupBoxSpeed"));
        groupBoxSpeed->setGeometry(QRect(260, 170, 191, 81));
        gridLayout = new QGridLayout(groupBoxSpeed);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBoxSpeed);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBoxSpeed);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

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

        gridLayout->addWidget(horizontalSliderSpeed, 2, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        groupBoxPosition->raise();
        groupBoxDirection->raise();
        downButton->raise();
        groupBoxSpeed->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 490, 21));
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
        groupBoxPosition->setTitle(QApplication::translate("MainWindow", "Position", 0));
        labelX->setText(QApplication::translate("MainWindow", "X:", 0));
        labelY->setText(QApplication::translate("MainWindow", "Y:", 0));
        labelZ->setText(QApplication::translate("MainWindow", "Z:", 0));
        pushButtonGo->setText(QApplication::translate("MainWindow", "GO!!", 0));
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
        groupBoxSpeed->setTitle(QApplication::translate("MainWindow", "Speed", 0));
        label->setText(QApplication::translate("MainWindow", "0.125", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">2.5</p></body></html>", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
