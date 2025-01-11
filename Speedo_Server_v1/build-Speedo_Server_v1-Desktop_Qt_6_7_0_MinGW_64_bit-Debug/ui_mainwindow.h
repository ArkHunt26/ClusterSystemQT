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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QListWidget *LstConsole;
    QPushButton *seatIndi;
    QPushButton *shiftUp;
    QLCDNumber *odometer;
    QGraphicsView *leftGView;
    QPushButton *hBrakeIndi;
    QPushButton *petrolindi;
    QLabel *odometerFrame;
    QPushButton *rightIndi;
    QLabel *gearNum;
    QPushButton *warningIndi;
    QLabel *rightDial;
    QPushButton *leftIndi;
    QLabel *leftDial;
    QLabel *lvlFullFuel;
    QLabel *topConsole;
    QLabel *speed;
    QPushButton *oilindi;
    QGraphicsView *rightGView;
    QLabel *oilTempIndi;
    QLabel *fuelLabel;
    QLabel *engLabel;
    QLabel *centerConsole;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(989, 650);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(80, 500, 821, 111));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 30, 201, 71));
        pushButton->setStyleSheet(QString::fromUtf8("font: 20pt \"Segoe UI\";"));
        LstConsole = new QListWidget(groupBox);
        LstConsole->setObjectName("LstConsole");
        LstConsole->setGeometry(QRect(420, 30, 371, 71));
        seatIndi = new QPushButton(centralwidget);
        seatIndi->setObjectName("seatIndi");
        seatIndi->setGeometry(QRect(520, 50, 40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../../qtResources/pics/seatBelt.svg"), QSize(), QIcon::Normal, QIcon::Off);
        seatIndi->setIcon(icon);
        seatIndi->setIconSize(QSize(22, 22));
        seatIndi->setFlat(true);
        shiftUp = new QPushButton(centralwidget);
        shiftUp->setObjectName("shiftUp");
        shiftUp->setGeometry(QRect(750, 190, 41, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../qtResources/pics/gearChange.svg"), QSize(), QIcon::Normal, QIcon::Off);
        shiftUp->setIcon(icon1);
        shiftUp->setFlat(true);
        odometer = new QLCDNumber(centralwidget);
        odometer->setObjectName("odometer");
        odometer->setGeometry(QRect(430, 350, 101, 41));
        odometer->setStyleSheet(QString::fromUtf8(""));
        odometer->setFrameShape(QFrame::NoFrame);
        odometer->setDigitCount(6);
        leftGView = new QGraphicsView(centralwidget);
        leftGView->setObjectName("leftGView");
        leftGView->setGeometry(QRect(20, 40, 360, 360));
        hBrakeIndi = new QPushButton(centralwidget);
        hBrakeIndi->setObjectName("hBrakeIndi");
        hBrakeIndi->setGeometry(QRect(420, 50, 40, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../../../qtResources/pics/handBrakesIndicator.svg"), QSize(), QIcon::Normal, QIcon::Off);
        hBrakeIndi->setIcon(icon2);
        hBrakeIndi->setIconSize(QSize(25, 25));
        hBrakeIndi->setFlat(true);
        petrolindi = new QPushButton(centralwidget);
        petrolindi->setObjectName("petrolindi");
        petrolindi->setGeometry(QRect(370, 50, 42, 42));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../../../qtResources/pics/nopetrol.svg"), QSize(), QIcon::Normal, QIcon::Off);
        petrolindi->setIcon(icon3);
        petrolindi->setFlat(true);
        odometerFrame = new QLabel(centralwidget);
        odometerFrame->setObjectName("odometerFrame");
        odometerFrame->setGeometry(QRect(270, 340, 440, 60));
        rightIndi = new QPushButton(centralwidget);
        rightIndi->setObjectName("rightIndi");
        rightIndi->setGeometry(QRect(620, 40, 81, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../../../../../qtResources/pics/rightIndi2.svg"), QSize(), QIcon::Normal, QIcon::Off);
        rightIndi->setIcon(icon4);
        rightIndi->setIconSize(QSize(70, 70));
        rightIndi->setFlat(true);
        gearNum = new QLabel(centralwidget);
        gearNum->setObjectName("gearNum");
        gearNum->setGeometry(QRect(740, 190, 61, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(22);
        font.setBold(false);
        font.setItalic(false);
        gearNum->setFont(font);
        gearNum->setStyleSheet(QString::fromUtf8("font: 22pt \"Segoe UI\";\n"
"color: rgb(255, 34, 14);"));
        gearNum->setAlignment(Qt::AlignCenter);
        warningIndi = new QPushButton(centralwidget);
        warningIndi->setObjectName("warningIndi");
        warningIndi->setGeometry(QRect(560, 50, 40, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../../../../../qtResources/pics/warningIndi.svg"), QSize(), QIcon::Normal, QIcon::Off);
        warningIndi->setIcon(icon5);
        warningIndi->setIconSize(QSize(25, 25));
        warningIndi->setFlat(true);
        rightDial = new QLabel(centralwidget);
        rightDial->setObjectName("rightDial");
        rightDial->setGeometry(QRect(590, 40, 360, 360));
        leftIndi = new QPushButton(centralwidget);
        leftIndi->setObjectName("leftIndi");
        leftIndi->setGeometry(QRect(270, 40, 81, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../../../../../qtResources/pics/leftIndi.svg"), QSize(), QIcon::Normal, QIcon::Off);
        leftIndi->setIcon(icon6);
        leftIndi->setIconSize(QSize(70, 70));
        leftIndi->setFlat(true);
        leftDial = new QLabel(centralwidget);
        leftDial->setObjectName("leftDial");
        leftDial->setGeometry(QRect(20, 40, 360, 360));
        lvlFullFuel = new QLabel(centralwidget);
        lvlFullFuel->setObjectName("lvlFullFuel");
        lvlFullFuel->setGeometry(QRect(40, 60, 331, 331));
        topConsole = new QLabel(centralwidget);
        topConsole->setObjectName("topConsole");
        topConsole->setGeometry(QRect(270, 40, 440, 60));
        speed = new QLabel(centralwidget);
        speed->setObjectName("speed");
        speed->setGeometry(QRect(170, 190, 61, 61));
        speed->setStyleSheet(QString::fromUtf8("font: 18pt \"Segoe UI\";\n"
"color: rgb(255, 34, 14);"));
        speed->setAlignment(Qt::AlignCenter);
        oilindi = new QPushButton(centralwidget);
        oilindi->setObjectName("oilindi");
        oilindi->setGeometry(QRect(470, 50, 40, 40));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../../../../../qtResources/pics/oil_Indi.svg"), QSize(), QIcon::Normal, QIcon::Off);
        oilindi->setIcon(icon7);
        oilindi->setIconSize(QSize(30, 30));
        oilindi->setFlat(true);
        rightGView = new QGraphicsView(centralwidget);
        rightGView->setObjectName("rightGView");
        rightGView->setGeometry(QRect(590, 40, 360, 360));
        oilTempIndi = new QLabel(centralwidget);
        oilTempIndi->setObjectName("oilTempIndi");
        oilTempIndi->setGeometry(QRect(610, 60, 331, 331));
        fuelLabel = new QLabel(centralwidget);
        fuelLabel->setObjectName("fuelLabel");
        fuelLabel->setGeometry(QRect(260, 280, 51, 31));
        fuelLabel->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Segoe UI\";"));
        engLabel = new QLabel(centralwidget);
        engLabel->setObjectName("engLabel");
        engLabel->setGeometry(QRect(820, 280, 91, 31));
        engLabel->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Segoe UI\";\n"
""));
        centerConsole = new QLabel(centralwidget);
        centerConsole->setObjectName("centerConsole");
        centerConsole->setGeometry(QRect(330, 120, 311, 231));
        MainWindow->setCentralWidget(centralwidget);
        rightGView->raise();
        groupBox->raise();
        seatIndi->raise();
        odometer->raise();
        leftGView->raise();
        hBrakeIndi->raise();
        petrolindi->raise();
        odometerFrame->raise();
        warningIndi->raise();
        rightDial->raise();
        leftDial->raise();
        lvlFullFuel->raise();
        topConsole->raise();
        speed->raise();
        oilindi->raise();
        oilTempIndi->raise();
        shiftUp->raise();
        gearNum->raise();
        fuelLabel->raise();
        engLabel->raise();
        centerConsole->raise();
        rightIndi->raise();
        leftIndi->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection Setting", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        seatIndi->setText(QString());
        shiftUp->setText(QString());
        hBrakeIndi->setText(QString());
        petrolindi->setText(QString());
        odometerFrame->setText(QString());
        rightIndi->setText(QString());
        gearNum->setText(QCoreApplication::translate("MainWindow", "N", nullptr));
        warningIndi->setText(QString());
        rightDial->setText(QString());
        leftIndi->setText(QString());
        leftDial->setText(QString());
        lvlFullFuel->setText(QString());
        topConsole->setText(QString());
        speed->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        oilindi->setText(QString());
        oilTempIndi->setText(QString());
        fuelLabel->setText(QCoreApplication::translate("MainWindow", "Fuel", nullptr));
        engLabel->setText(QCoreApplication::translate("MainWindow", "Eng Temp", nullptr));
        centerConsole->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
