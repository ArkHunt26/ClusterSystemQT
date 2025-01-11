#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "DeviceController.h"

#include <QAbstractSocket>
#include <QMetaEnum>
#include <QString>
#include <QTextStream>

#include <iostream>
#include <string>
#include <stdlib.h>


typedef enum
{
    OFF_BEAM=0,
    LOW_BEAM,
    HIGH_BEAM
}lightStates;

// typedef enum
// {
//     H_OFF = 0,
//     H_ON
// }handBrkStatus;

// typedef enum
// {
//     O_OFF = 0,
//     O_ON
// }oilStatus;


typedef enum
{
    OFF = 0,
    ON
}binStatus;

typedef enum
{
    I_OFF = 0,
    PARK,
    LEFT,
    RIGHT
}indiStatus;

typedef enum
{
    REVERSE = -1,
    NEUTRAL,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
}gearShift;

struct dataInfo
{
    char lightStatus;
    char FanStatus;
    char speedValue;


    // uint8_t
}info;


// struct DataFormat
// {
//     char speed[4];
//     char indiVal[2];
//     char handbrake[3];
//     char oil[2];
//     char seat[2];
//     char warning[2];

// }DataFT;


struct DataFormat
{
    char speed[4];
    char indiVal[2];
    QString handbrake[3];
    char oil[2];
    char seat[3];
    char warning[2];

};

char buff[10];

// String buff;


lightStates lState = OFF_BEAM;
binStatus hStatus = OFF;
binStatus oStatus = OFF;
binStatus sStatus = OFF;
binStatus wStatus = OFF;

static gearShift gearState = NEUTRAL;

static indiStatus IndiStatus =I_OFF;

static int numFlag = 0;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setDeviceController();



    // info.FanStatus = 0;
    // info.lightStatus = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::device_connected()
{
    ui->LstConsole->addItem("Connected to device");
    // ui->btnConnect->setText("Disconnect");
    // ui->groupBox_2->setEnabled(true);
}

void MainWindow::device_disconnected()
{
    ui->LstConsole->addItem("Disconnected from device");
    // ui->btnConnect->setText("Connect");
    // ui->groupBox_2->setEnabled(false);

}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    ui->LstConsole->addItem(metaEnum.valueToKey(state));
}

void MainWindow::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError >();
    ui->LstConsole->addItem(metaEnum.valueToKey(error));
}

void MainWindow::device_dataReady(QByteArray data)
{
    ui->LstConsole->addItem(QString(data));
}

void MainWindow::setDeviceController()
{
    connect(&_controller, &DeviceController::connected, this, &MainWindow::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &MainWindow::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &MainWindow::device_stateChanged);
    connect(&_controller, &DeviceController::errorOccurred, this, &MainWindow::device_errorOccurred);
    connect(&_controller, &DeviceController::dataReady, this, &MainWindow::device_dataReady);
}

void MainWindow::on_btnConnect_clicked()
{
    if(_controller.isConnected())
    {
        _controller.disconnect();
        // LightOn->setEnable(false);
    }
    else
    {

        auto ip = "127.0.0.1";
        auto port = 12345;

        _controller.connectToDevice(ip, port);

    }
}


void MainWindow::on_LightSw_clicked()
{
    // auto buf = "1";
    // auto message = ui->buf->text().trimmed();


    if(lState == OFF_BEAM)
    {
        // info.FanStatus = '1';
        // info.lightStatus = '1';
        // sprintf(buff,"%c%c",info.FanStatus, info.lightStatus);
        lState = LOW_BEAM;
        sprintf(buff,"%c%d",'L', (int)lState);
        // sprintf(buff,"%c%d",'L', (int)LOW_BEAM);

    }
    else if(lState == LOW_BEAM)
    {
        lState = HIGH_BEAM;
        sprintf(buff,"%c%d",'L', (int)lState);
        // sprintf(buff,"%c%d",'L', (int)HIGH_BEAM);

    }
    else if(lState == HIGH_BEAM)
    {
        lState = OFF_BEAM;
        sprintf(buff,"%c%d",'L', (int)lState);
        // sprintf(buff,"%c%d",'L', (int)OFF);
    }

    // lState =!lState;


    // auto message = buf;

    // _controller.send(message);
    // _controller.send((QString)buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);

}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    sprintf(buff,"%c%d",'S',value);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);


}


void MainWindow::on_HandBrk_clicked()
{
    char tempr[2];
    // hStatus
    if(hStatus == OFF)
    {
        hStatus = ON;
        sprintf(buff,"%c%d",'H', (int)hStatus);
            // DataFT.handbrake=buff;

        // sprintf(tempr,"%c%d",'H', (int)hStatus);
        // DataFT.handbrake=tempr;
            // sprintf(DataFT.handbrake,"%c%d",'H', (int)hStatus);
        // DataFT.handbrake
    }
    else
    {
        hStatus = OFF;
        sprintf(buff,"%c%d",'H', (int)hStatus);

        // sprintf(tempr,"%c%d",'H', (int)hStatus);
        // DataFT.handbrake=tempr;
            // sprintf(DataFT.handbrake,"%c%d",'H', (int)hStatus);

    }
        // _controller.send((QString)DataFT);
    // buf=
    // QString hrstatus = structToString(DataFT.handbrake/*, sizeof(data.handbrake) - 1*/);
        // QString hrstatus = structToString(DataFT);

        // _controller.send(hrstatus);
    // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);


}


void MainWindow::on_oilSw_clicked()
{
    // oStatus
    if(oStatus == OFF)
    {
        oStatus = ON;
        sprintf(buff,"%c%d",'O', (int)oStatus);
    }
    else
    {
        oStatus = OFF;
        sprintf(buff,"%c%d",'O', (int)oStatus);
    }
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_seatSw_clicked()
{
    // seatSw
    // sStatus

    if(sStatus == OFF)
    {
        sStatus = ON;
        sprintf(buff,"%c%d",'C', (int)sStatus);
        // streamMaker('C', (int)sStatus);
    }
    else
    {
        sStatus = OFF;
        sprintf(buff,"%c%d",'C', (int)sStatus);
        // streamMaker('C', (int)sStatus);

    }
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_warningSw_clicked()
{
    // warningSw

    if(wStatus == OFF)
    {
        wStatus = ON;
        sprintf(buff,"%c%d",'W', (int)wStatus);
    }
    else
    {
        wStatus = OFF;
        sprintf(buff,"%c%d",'W', (int)wStatus);
    }
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    sprintf(buff,"%c%d",'F',value);
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_parkIndiSw_clicked()
{

    static int pFlag = 0;
    // if(pFlag == 0)
    // {

    // }
    sprintf(buff,"%c%d",'I',(int)PARK);
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}

void MainWindow::streamMaker(char sLabel, int qValue)
{
    // DataFormat DataFT;

    // if(sLabel == 'C')
    // {
    //     sprintf(DataFT.seat,"%c%d",'C', (int)qValue);
    // }
    // _controller.send(DataFT);

}




void MainWindow::on_oilSlider_valueChanged(int value)
{
    sprintf(buff,"%c%d",'O',value);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_rpmSlider_valueChanged(int value)
{
    sprintf(buff,"%c%d",'R',value);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_gearUp_clicked()
{
    // static int numFlag = 0;
    if(numFlag <6)
        numFlag++;

    if(numFlag == -1)
    {
        gearState = NEUTRAL;
        // numFlag++;

    }
    if(numFlag == 0)
    {
        gearState = NEUTRAL;
        // numFlag++;

    }
    else if(numFlag == 1)
    {
        gearState = ONE;
        // numFlag++;
    }
    else if(numFlag == 2)
    {
        gearState = TWO;
        // numFlag++;
    }
    else if(numFlag == 3)
    {
        gearState = THREE;
        // numFlag++;
    }
    else if(numFlag == 4)
    {
        gearState = FOUR;
        // numFlag++;
    }
    else if(numFlag == 5)
    {
        gearState = FIVE;
        // numFlag++;
    }
    else if(numFlag == 6)
    {
        gearState = SIX;
    }


    sprintf(buff,"%c%d",'G',(int)gearState);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_gearRevrs_clicked()
{
    gearState = REVERSE;
    numFlag=-1;
    sprintf(buff,"%c%d",'G',(int)gearState);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_gearDown_clicked()
{
    // static int MnumFlag = 0;

    // if(numFlag == -1)
    // {
    //     gearState = ONE;
    //     // numFlag--;

    // }
    if(numFlag >0)
        numFlag--;

    if(numFlag == 0)
    {
        gearState = NEUTRAL;
        // numFlag--;

    }
    else if(numFlag == 1)
    {
        gearState = ONE;
        // numFlag--;
    }
    else if(numFlag == 2)
    {
        gearState = TWO;
        // numFlag--;
    }
    else if(numFlag == 3)
    {
        gearState = THREE;
        // numFlag--;
    }
    else if(numFlag == 4)
    {
        gearState = FOUR;
        // numFlag--;
    }
    else if(numFlag == 5)
    {
        gearState = FIVE;
        // numFlag--;
    }
    else if(numFlag == 6)
    {
        gearState = SIX;
    }


    sprintf(buff,"%c%d",'G',(int)gearState);
    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_leftIndiSw_clicked()
{
    // static int pFlag = 0;
    // if(pFlag == 0)
    // {

    // }
    sprintf(buff,"%c%d",'I',(int)LEFT);
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}


void MainWindow::on_rightIndiSw_clicked()
{
    sprintf(buff,"%c%d",'I',(int)RIGHT);
        // _controller.send(buff);

    QString mm = QString(buff);
    // _controller.send(QString(buff));
    _controller.send(mm);
}

