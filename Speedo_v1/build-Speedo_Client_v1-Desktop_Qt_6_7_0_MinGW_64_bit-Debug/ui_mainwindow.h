/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnConnect;
    QListWidget *LstConsole;
    QPushButton *LightSw;
    QSlider *horizontalSlider;
    QPushButton *HandBrk;
    QPushButton *oilSw;
    QPushButton *seatSw;
    QPushButton *warningSw;
    QSlider *verticalSlider;
    QPushButton *leftIndiSw;
    QPushButton *rightIndiSw;
    QPushButton *parkIndiSw;
    QSlider *oilSlider;
    QSlider *rpmSlider;
    QPushButton *gearUp;
    QPushButton *gearDown;
    QPushButton *gearRevrs;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(779, 545);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");
        btnConnect->setGeometry(QRect(180, 100, 141, 111));
        btnConnect->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 49, 8);\n"
"font: 700 16pt \"Segoe UI\";"));
        LstConsole = new QListWidget(centralwidget);
        LstConsole->setObjectName("LstConsole");
        LstConsole->setGeometry(QRect(490, 40, 270, 441));
        LightSw = new QPushButton(centralwidget);
        LightSw->setObjectName("LightSw");
        LightSw->setGeometry(QRect(60, 80, 101, 41));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(90, 440, 331, 20));
        horizontalSlider->setMaximum(22);
        horizontalSlider->setOrientation(Qt::Horizontal);
        HandBrk = new QPushButton(centralwidget);
        HandBrk->setObjectName("HandBrk");
        HandBrk->setGeometry(QRect(200, 40, 101, 41));
        oilSw = new QPushButton(centralwidget);
        oilSw->setObjectName("oilSw");
        oilSw->setGeometry(QRect(60, 180, 101, 41));
        seatSw = new QPushButton(centralwidget);
        seatSw->setObjectName("seatSw");
        seatSw->setGeometry(QRect(340, 80, 101, 41));
        warningSw = new QPushButton(centralwidget);
        warningSw->setObjectName("warningSw");
        warningSw->setGeometry(QRect(340, 180, 101, 41));
        verticalSlider = new QSlider(centralwidget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setGeometry(QRect(30, 60, 18, 361));
        verticalSlider->setOrientation(Qt::Vertical);
        leftIndiSw = new QPushButton(centralwidget);
        leftIndiSw->setObjectName("leftIndiSw");
        leftIndiSw->setGeometry(QRect(150, 250, 83, 29));
        rightIndiSw = new QPushButton(centralwidget);
        rightIndiSw->setObjectName("rightIndiSw");
        rightIndiSw->setGeometry(QRect(270, 250, 83, 29));
        parkIndiSw = new QPushButton(centralwidget);
        parkIndiSw->setObjectName("parkIndiSw");
        parkIndiSw->setGeometry(QRect(210, 290, 83, 29));
        oilSlider = new QSlider(centralwidget);
        oilSlider->setObjectName("oilSlider");
        oilSlider->setGeometry(QRect(460, 60, 18, 361));
        oilSlider->setOrientation(Qt::Vertical);
        rpmSlider = new QSlider(centralwidget);
        rpmSlider->setObjectName("rpmSlider");
        rpmSlider->setGeometry(QRect(90, 480, 331, 20));
        rpmSlider->setMaximum(22);
        rpmSlider->setOrientation(Qt::Horizontal);
        gearUp = new QPushButton(centralwidget);
        gearUp->setObjectName("gearUp");
        gearUp->setGeometry(QRect(270, 330, 83, 29));
        gearDown = new QPushButton(centralwidget);
        gearDown->setObjectName("gearDown");
        gearDown->setGeometry(QRect(140, 330, 83, 29));
        gearRevrs = new QPushButton(centralwidget);
        gearRevrs->setObjectName("gearRevrs");
        gearRevrs->setGeometry(QRect(210, 370, 83, 29));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Power", nullptr));
        LightSw->setText(QCoreApplication::translate("MainWindow", "Light", nullptr));
        HandBrk->setText(QCoreApplication::translate("MainWindow", "Hand brake", nullptr));
        oilSw->setText(QCoreApplication::translate("MainWindow", "Oil", nullptr));
        seatSw->setText(QCoreApplication::translate("MainWindow", "Seat Belt", nullptr));
        warningSw->setText(QCoreApplication::translate("MainWindow", "Warnings", nullptr));
        leftIndiSw->setText(QCoreApplication::translate("MainWindow", "Left", nullptr));
        rightIndiSw->setText(QCoreApplication::translate("MainWindow", "Right", nullptr));
        parkIndiSw->setText(QCoreApplication::translate("MainWindow", "Park", nullptr));
        gearUp->setText(QCoreApplication::translate("MainWindow", "gearUp", nullptr));
        gearDown->setText(QCoreApplication::translate("MainWindow", "gearDown", nullptr));
        gearRevrs->setText(QCoreApplication::translate("MainWindow", "gearRevrs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
