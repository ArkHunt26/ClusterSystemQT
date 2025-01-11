#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myTcpServer.h"
#include <QTimer>
#include <QtSvg/QSvgGenerator>
#include <QThread>
#include <string>
#include <QString>
#include <iostream>
#include <string>
#include <QColor>
#include <QColorDialog>


using namespace std;

static float angle = 0;

constexpr int pT = 20;
constexpr int indiT = 500;

// static int indiFlag = 0;
// static QTimer *inditimer = new QTimer(this);

// constexpr int pT = 800;
// char buff[10];

char buff[10] = "";

typedef enum
{
    LOW_SPEED = 0,
    HIGH_SPEED
}speedStatus;

typedef enum
{
    I_OFF = 0,
    PARK,
    LEFT,
    RIGHT
}indiStatus;

typedef enum
{
    ALL_OFF=0,
    INDI_ON,
    INDI_OFF
}indiDisp;

typedef enum
{
    OFF_BEAM=0,
    LOW_BEAM,
    HIGH_BEAM
}lightStates;


// struct DataFormat
// {
//     char speed[4];
//     char indiVal[2];
// }data;

static speedStatus speedIndi;

static indiStatus IndiStatus = I_OFF;
static int disCount = 0;
static int rpmdisCount = 0;
static QString gN;


static QTimer *PStart_timer;

// void MainWindow::INDILIGHTINGS(indiDisp state)
// {
//     switch(state)
//     {
//     case ALL_OFF:
//         ui->seatIndi->hide();
//         ui->oilindi->hide();
//         ui->hBrakeIndi->hide();
//         ui->warningIndi->hide();
//         ui->petrolindi->hide();
//         ui->rightIndi->hide();
//         ui->leftIndi->hide();
//         ui->topConsole->hide();


//         ui->shiftUp->hide();
//         ui->gearNum->hide();
//         ui->engLabel->hide();
//         ui->rightDial->hide();
//         ui->rightGView->hide();
//         ui->lvlFullFuel->hide();

//         ui->fuelLabel->hide();
//         ui->speed->hide();
//         ui->leftGView->hide();
//         ui->leftDial->hide();
//         ui->oilTempIndi->hide();


//         ui->odometerFrame->hide();
//         ui->odometer->hide();

//         ui->centerConsole->hide();

//         break;

//     case INDI_ON:
//         ui->seatIndi->show();
//         ui->oilindi->show();
//         ui->hBrakeIndi->show();
//         ui->warningIndi->show();
//         ui->petrolindi->show();
//         ui->rightIndi->show();
//         ui->leftIndi->show();

//         break;

//     case INDI_OFF:
//         ui->seatIndi->hide();
//         ui->oilindi->hide();
//         ui->hBrakeIndi->hide();
//         ui->warningIndi->hide();
//         ui->petrolindi->hide();
//         ui->rightIndi->hide();
//         ui->leftIndi->hide();

//         break;

//     default:
//         break;
//     }
// }


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = nullptr;


    QPixmap pix1("C:/Users/Rohith/Desktop/qtResources/pics/leftDial.png");
    int width1 = ui->leftDial->width();
    int height1 = ui->leftDial->height();
    ui->leftDial->setPixmap(pix1.scaled(width1,height1,Qt::KeepAspectRatio));


    QPixmap pix2("C:/Users/Rohith/Desktop/qtResources/pics/rightDial.png");
    int width2 = ui->rightDial->width();
    int height2 = ui->rightDial->height();
    ui->rightDial->setPixmap(pix2.scaled(width2,height2,Qt::KeepAspectRatio));


    QPixmap pix3("C:/Users/Rohith/Desktop/qtResources/pics/topConsoleUpdate1.png");
    int width3 = ui->topConsole->width();
    int height3 = ui->topConsole->height();
    ui->topConsole->setPixmap(pix3.scaled(width3,height3,Qt::KeepAspectRatio));


    QPixmap pix4("C:/Users/Rohith/Desktop/qtResources/pics/bottomConsoleUpdate1.png");
    int width4 = ui->odometerFrame->width();
    int height4 = ui->odometerFrame->height();
    ui->odometerFrame->setPixmap(pix4.scaled(width4,height4,Qt::KeepAspectRatio));


    QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/lvlFull.png");
    int width5 = ui->lvlFullFuel->width();
    int height5 = ui->lvlFullFuel->height();
    ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));

    QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/full.png");
    int width6 = ui->oilTempIndi->width();
    int height6 = ui->oilTempIndi->height();
    ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
    // QPixmap pix7("C:/Users/Rohith/Desktop/qtResources/pics/clusterCarModelImgBgR2.png");

    // QPixmap pix7("C:/Users/Rohith/Downloads/mclaren-removebg-preview.png");
    QPixmap pix7("C:/Users/Rohith/Desktop/qtResources/pics/car4-removebg-preview.png");
    int width7 = ui->centerConsole->width();
    int height7 = ui->centerConsole->height();
    ui->centerConsole->setPixmap(pix7.scaled(width7,height7,Qt::KeepAspectRatio));

    // QPixmap pix8("C:/Users/Rohith/Desktop/qtResources/pics/car1-removebg-preview.png");
    // int width8 = ui->centerConsole->width();
    // int height8 = ui->centerConsole->height();
    // ui->centerConsole->setPixmap(pix8.scaled(width8,height8,Qt::KeepAspectRatio));

    Scene1 = new QGraphicsScene(this);
    Scene1->addPixmap(QPixmap("C:/Users/Rohith/Desktop/qtResources/pics/needle3.png"));
    ui->leftGView->setScene(Scene1);



    Scene2 = new QGraphicsScene(this);
    Scene2->addPixmap(QPixmap("C:/Users/Rohith/Desktop/qtResources/pics/needle3.png"));
    ui->rightGView->setScene(Scene2);


    // QPixmap pix3("C:/Users/Rohith/Desktop/qtResources/pics/centerCircle4.png");
    // int width3 = ui->rightDial->width();
    // int height3 = ui->rightDial->height();
    // ui->centerCircle->setPixmap(pix3.scaled(width3,height3,Qt::KeepAspectRatio));


    // ui->centerCircle->setPixmap(pixmap.scaled(32,32,Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ///ROTATE ANIMATION///
    ///
                            // static float angle = 0;
                            // static int F_flag =0, R_Flag = 0;

                            // static QTimer *PStart_timer = new QTimer(this);


                            // PStart_timer->setInterval(pT);
                            // connect(PStart_timer, &QTimer::timeout, this, [this]{
                            //     ui->leftGView->rotate(angle);
                            //     ui->rightGView->rotate(angle);

                            //     if(angle < 7.2)
                            //     {
                            //         angle += 0.1;
                            //     }
                            //     else
                            //     {
                            //         PStart_timer->stop();
                            //         ui->leftGView->resetTransform();
                            //         ui->rightGView->resetTransform();
                            //         R_Flag = 1;

                            //         ui->rightIndi->hide();
                            //         ui->leftIndi->hide();
                            //     }
                            //     // if(angle < 5.2 && F_flag == 0)
                            //     // {
                            //     //     angle += 0.1;
                            //     //     if(angle >= 5.1)
                            //     //         F_flag++;
                            //     //     // ui->graphicsView->rotate(angle);

                            //     // }
                            //     // else if(/*angle >= 0 &&*/ F_flag == 1)
                            //     // {
                            //     //     angle -= 0.1;
                            //     //     if(angle <= 0.1)
                            //     //     {
                            //     //         F_flag++;
                            //     //         PStart_timer->stop();
                            //     //         ui->graphicsView->resetTransform();
                            //     //         ui->graphicsView_2->resetTransform();
                            //     //     }
                            //     // }
                            //     // else
                            //     //     PStart_timer->stop();
                            // });
                            // PStart_timer->start();


    // static QTimer *PSTPStart_timer = new QTimer(this);
    // static QTimer *PSTPStart_timer = new QTimer(this);

    // if(R_Flag == 1)
    // {
    //     static QTimer *RStart_timer = new QTimer(this);

    //     RStart_timer->setInterval(pT);
    //     connect(RStart_timer, &QTimer::timeout, this, [this]{
    //         ui->graphicsView->rotate(angle);
    //         ui->graphicsView_2->rotate(angle);

    //         if(angle >= 0)
    //         {
    //             angle -= 0.1;
    //         }
    //         else
    //             RStart_timer->stop();

    //         // if(angle < 5.2 && F_flag == 0)
    //         // {
    //         //     angle += 0.1;
    //         //     if(angle >= 5.1)
    //         //         F_flag++;
    //         //     // ui->graphicsView->rotate(angle);

    //         // }
    //         // else if(/*angle >= 0 &&*/ F_flag == 1)
    //         // {
    //         //     angle -= 0.1;
    //         //     if(angle <= 0.1)
    //         //     {
    //         //         F_flag++;
    //         //         PStart_timer->stop();
    //         //         ui->graphicsView->resetTransform();
    //         //         ui->graphicsView_2->resetTransform();
    //         //     }
    //         // }
    //         // else
    //         //     PStart_timer->stop();


    // });
    // RStart_timer->start();


    // for(int i = 0; i < 10 ; i++)
    // {
    //     angle+=10;
    //     ui->graphicsView->rotate(angle);
    //     QThread::msleep(500);
    // }

    // startUpSequence();
    // }

        ui->seatIndi->hide();
        ui->oilindi->hide();
        ui->hBrakeIndi->hide();
        ui->warningIndi->hide();
        ui->petrolindi->hide();

        ui->shiftUp->hide();

        ui->gearNum->show();

        // ui->rightIndi->hide();
        // ui->leftIndi->hide();

        ui->centerConsole->show();

    //// STARTUP SEQUENCE ////

    // ui->seatIndi->hide();
    // ui->oilindi->hide();
    // ui->hBrakeIndi->hide();
    // ui->warningIndi->hide();
    // ui->petrolindi->hide();
    // ui->rightIndi->hide();
    // ui->leftIndi->hide();
    // ui->topConsole->hide();


    // ui->shiftUp->hide();
    // ui->gearNum->hide();
    // ui->engLabel->hide();
    // ui->rightDial->hide();
    // ui->rightGView->hide();
    // ui->lvlFullFuel->hide();

    // ui->fuelLabel->hide();
    // ui->speed->hide();
    // ui->leftGView->hide();
    // ui->leftDial->hide();
    // ui->oilTempIndi->hide();


    // ui->odometerFrame->hide();
    // ui->odometer->hide();

    gN = 'N';
    ui->gearNum->setText(gN);

    ui->fuelLabel->setStyleSheet("color: #3DFF73");
    ui->engLabel->setStyleSheet("color: #3DFF73");


        // static int indiFlag = 0;
        // static QTimer *inditimer = new QTimer(this);

        // inditimer->setInterval(indiT);
        // connect(inditimer, &QTimer::timeout, this, [this]{
        //     if(IndiStatus == I_OFF )
        //     {
        //         ui->leftIndi->hide();
        //         ui->rightIndi->hide();
        //     }
        //     if(IndiStatus == PARK )
        //     {
        //         if(indiFlag == 0)
        //         {
        //             ui->leftIndi->hide();
        //             ui->rightIndi->hide();
        //         }
        //         else
        //         {
        //             ui->leftIndi->show();
        //             ui->rightIndi->show();
        //         }
        //         indiFlag=!indiFlag;

        //     }
        // });
        // inditimer->start();


    // ui->groupBox->show();

    /////////////////////////
    ///
    ///


    //// DISCONNECT SEQUENCE ////

    ui->seatIndi->hide();
    ui->oilindi->hide();
    ui->hBrakeIndi->hide();
    ui->warningIndi->hide();
    ui->petrolindi->hide();
    ui->rightIndi->hide();
    ui->leftIndi->hide();
    ui->topConsole->hide();


    ui->shiftUp->hide();
    ui->gearNum->hide();
    ui->engLabel->hide();
    ui->rightDial->hide();
    ui->rightGView->hide();
    ui->lvlFullFuel->hide();

    ui->fuelLabel->hide();
    ui->speed->hide();
    ui->leftGView->hide();
    ui->leftDial->hide();
    ui->oilTempIndi->hide();


    ui->odometerFrame->hide();
    ui->odometer->hide();

    ui->centerConsole->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(_server == nullptr)
    {
        auto port = 12345;
        _server = new myTcpServer(port);
        connect(_server, &myTcpServer::newClientConnected, this, &MainWindow::newClientConnected);
        connect(_server, &myTcpServer::dataReceived, this, &MainWindow::clientDataReceived);
        connect(_server, &myTcpServer::clientDisconnect, this, &MainWindow::clientDisconnected);

    }

    auto state = (_server->isStarted())? "1" : "0";
    // ui->lblConnectionStatus->setProperty("state", state);
    // style()->polish(ui->lblConnectionStatus);
}

void MainWindow::newClientConnected()
{
    ui->LstConsole->addItem("New Client connected");

    //// ICONS DISPLAY ////

    ui->seatIndi->hide();
    ui->oilindi->hide();
    ui->hBrakeIndi->hide();
    ui->warningIndi->hide();
    ui->petrolindi->hide();
    ui->rightIndi->hide();
    ui->leftIndi->hide();
    ui->topConsole->show();


    ui->shiftUp->hide();
    ui->gearNum->show();
    ui->engLabel->show();
    ui->rightDial->show();
    ui->rightGView->show();
    ui->lvlFullFuel->show();

    ui->fuelLabel->show();
    ui->speed->show();
    ui->leftGView->show();
    ui->leftDial->show();
    ui->oilTempIndi->show();

    ui->odometerFrame->show();
    ui->odometer->show();

    ui->centerConsole->show();

    //////////////////////



    ////ROTATE ANIMATION STARTS
    ///

    static float angle = 0;
    static int F_flag =0, R_Flag = 0;

    PStart_timer = new QTimer(this);

    // static QTimer *PStart_timer = new QTimer(this);


    PStart_timer->setInterval(pT);
    connect(PStart_timer, &QTimer::timeout, this, [this]{
        ui->leftGView->rotate(angle);
        ui->rightGView->rotate(angle);
        // PStart_timer->start();

        if(angle < 7.2)
        {
            // INDILIGHTINGS(INDI_ON);
            angle += 0.1;

            ui->seatIndi->show();
            ui->oilindi->show();
            ui->hBrakeIndi->show();
            ui->warningIndi->show();
            ui->petrolindi->show();
            ui->rightIndi->show();
            ui->leftIndi->show();
        }
        else
        {
            PStart_timer->stop();
            ui->leftGView->resetTransform();
            ui->rightGView->resetTransform();
            R_Flag = 1;

            ui->rightIndi->hide();
            ui->leftIndi->hide();

            ui->seatIndi->hide();
            ui->oilindi->hide();
            ui->hBrakeIndi->hide();
            ui->warningIndi->hide();
            ui->petrolindi->hide();
            ui->rightIndi->hide();
            ui->leftIndi->hide();

            // INDILIGHTINGS(INDI_OFF);
            // PStart_timer->stop();

        }
        // if(angle < 5.2 && F_flag == 0)
        // {
        //     angle += 0.1;
        //     if(angle >= 5.1)
        //         F_flag++;
        //     // ui->graphicsView->rotate(angle);

        // }
        // else if(/*angle >= 0 &&*/ F_flag == 1)
        // {
        //     angle -= 0.1;
        //     if(angle <= 0.1)
        //     {
        //         F_flag++;
        //         PStart_timer->stop();
        //         ui->graphicsView->resetTransform();
        //         ui->graphicsView_2->resetTransform();
        //     }
        // }
        // else
        //     PStart_timer->stop();
    });
    PStart_timer->start();

    // if(R_Flag==1)
    //     PStart_timer->stop();



    //// STARTUP SEQUENCE ////

    // static float angle = 0;
    // static int F_flag =0, R_Flag = 0;

    // static QTimer *PStart_timer = new QTimer(this);


    // PStart_timer->setInterval(pT);
    // connect(PStart_timer, &QTimer::timeout, this, [this]{
    //     ui->leftGView->rotate(angle);
    //     ui->rightGView->rotate(angle);

    //     if(angle < 7.2)
    //     {
    //         angle += 0.1;
    //     }
    //     else
    //     {
    //         PStart_timer->stop();
    //         ui->leftGView->resetTransform();
    //         ui->rightGView->resetTransform();
    //         R_Flag = 1;
    //     }
    //     // if(angle < 5.2 && F_flag == 0)
    //     // {
    //     //     angle += 0.1;
    //     //     if(angle >= 5.1)
    //     //         F_flag++;
    //     //     // ui->graphicsView->rotate(angle);

    //     // }
    //     // else if(/*angle >= 0 &&*/ F_flag == 1)
    //     // {
    //     //     angle -= 0.1;
    //     //     if(angle <= 0.1)
    //     //     {
    //     //         F_flag++;
    //     //         PStart_timer->stop();
    //     //         ui->graphicsView->resetTransform();
    //     //         ui->graphicsView_2->resetTransform();
    //     //     }
    //     // }
    //     // else
    //     //     PStart_timer->stop();
    // });
    // PStart_timer->start();



    //     ui->seatIndi->hide();
    //     ui->oilindi->hide();
    //     ui->hBrakeIndi->hide();
    //     ui->warningIndi->hide();
    //     ui->petrolindi->hide();
    //     ui->rightIndi->hide();
    //     ui->leftIndi->hide();
    //     ui->topConsole->hide();


    //     ui->shiftUp->hide();
    //     ui->gearNum->hide();
    //     ui->engLabel->hide();
    //     ui->rightDial->hide();
    //     ui->rightGView->hide();
    //     ui->lvlFullFuel->hide();

    //     ui->fuelLabel->hide();
    //     ui->speed->hide();
    //     ui->leftGView->hide();
    //     ui->leftDial->hide();
    //     ui->oilTempIndi->hide();


    //     ui->odometerFrame->hide();
    //     ui->odometer->hide();

    //     _sleep(1);

    //         // ui->seatIndi->hide();
    //         // ui->oilindi->hide();
    //         // ui->hBrakeIndi->hide();
    //         // ui->warningIndi->hide();
    //         // ui->petrolindi->hide();
    //         // ui->rightIndi->hide();
    //         // ui->leftIndi->hide();
    //         // ui->topConsole->show();


    //         // ui->shiftUp->show();
    //         // ui->gearNum->show();
    //         // ui->engLabel->show();
    //         // ui->rightDial->show();
    //         // ui->rightGView->show();
    //         // ui->lvlFullFuel->show();

    //         // ui->fuelLabel->show();
    //         // ui->speed->show();
    //         // ui->leftGView->show();
    //         // ui->leftDial->show();
    //         // ui->oilTempIndi->show();


    //         // ui->odometerFrame->show();
    //         // ui->odometer->show();
    //         // gN = 'N';
    //         // ui->gearNum->setText(gN);

    //     // ui->seatIndi->hide();
    //     // ui->oilindi->hide();
    //     // ui->hBrakeIndi->hide();
    //     // ui->warningIndi->hide();
    //     // ui->petrolindi->hide();
    //     // ui->rightIndi->hide();
    //     // ui->leftIndi->hide();
    //     ui->topConsole->show();


    //     // ui->shiftUp->show();
    //     // ui->gearNum->show();
    //     // ui->engLabel->show();
    //     // ui->rightDial->show();
    //     ui->rightGView->show();
    //     ui->oilTempIndi->show();

    //     // ui->fuelLabel->show();
    //     // ui->speed->show();
    //     ui->leftGView->show();
    //     // ui->leftDial->show();
    //     ui->lvlFullFuel->show();


    //     // ui->odometerFrame->show();
    //     // ui->odometer->show();
    //     // gN = 'N';
    //     // ui->gearNum->setText(gN);

    //     _sleep(1);

    // ui->seatIndi->hide();
    // ui->oilindi->hide();
    // ui->hBrakeIndi->hide();
    // ui->warningIndi->hide();
    // ui->petrolindi->hide();
    // ui->rightIndi->hide();
    // ui->leftIndi->hide();
    // ui->topConsole->show();


    // ui->shiftUp->show();
    // ui->gearNum->show();
    // ui->engLabel->show();
    // ui->rightDial->show();
    // ui->rightGView->show();
    // ui->lvlFullFuel->show();

    // ui->fuelLabel->show();
    // ui->speed->show();
    // ui->leftGView->show();
    // ui->leftDial->show();
    // ui->oilTempIndi->show();


    // ui->odometerFrame->show();
    // ui->odometer->show();
    // gN = 'N';
    // ui->gearNum->setText(gN);

}


// void MainWindow::on_btnSendToAll_clicked()
// {
//     auto message = ui->lnMessage->text().trimmed();
//     _server->sendToAll(message);
// }

void MainWindow::clientDisconnected()
{
    ui->LstConsole->addItem("Client Disconnected");

    //// DISCONNECT SEQUENCE ////

    ui->seatIndi->hide();
    ui->oilindi->hide();
    ui->hBrakeIndi->hide();
    ui->warningIndi->hide();
    ui->petrolindi->hide();
    ui->rightIndi->hide();
    ui->leftIndi->hide();
    ui->topConsole->hide();


    ui->shiftUp->hide();
    ui->gearNum->hide();
    ui->engLabel->hide();
    ui->rightDial->hide();
    ui->rightGView->hide();
    ui->lvlFullFuel->hide();

    ui->fuelLabel->hide();
    ui->speed->hide();
    ui->leftGView->hide();
    ui->leftDial->hide();
    ui->oilTempIndi->hide();


    ui->odometerFrame->hide();
    ui->odometer->hide();

    ui->centerConsole->hide();

    // extern QTimer *PStart_timer;

    PStart_timer->stop();


}

void MainWindow::clientDataReceived(QString message)
{
    static int prevValue = 0;
    static int rpmprevValue = 0;


    static int indiFlag = 0;
    static QTimer *inditimer = new QTimer(this);

            // inditimer->setInterval(indiT);
            // connect(inditimer, &QTimer::timeout, this, [this]{
            //     if(IndiStatus == (int)I_OFF )
            //     {
            //         ui->leftIndi->hide();
            //         ui->rightIndi->hide();
            //     }
            //     if(IndiStatus == (int)PARK )
            //     {
            //         if(indiFlag == 0)
            //         {
            //             ui->leftIndi->hide();
            //             ui->rightIndi->hide();
            //         }
            //         else
            //         {
            //             ui->leftIndi->show();
            //             ui->rightIndi->show();
            //         }

            //         indiFlag=!indiFlag;

            //     }
            //     if(IndiStatus == (int)LEFT )
            //     {
            //         if(indiFlag == 0)
            //         {
            //             ui->leftIndi->show();
            //             ui->rightIndi->hide();
            //         }
            //         else
            //         {
            //             ui->leftIndi->hide();
            //             ui->rightIndi->hide();
            //         }
            //         indiFlag=!indiFlag;

            //     }

            //     if(IndiStatus == (int)RIGHT )
            //     {
            //         if(indiFlag == 0)
            //         {
            //             ui->leftIndi->hide();
            //             ui->rightIndi->show();
            //         }
            //         else
            //         {
            //             ui->leftIndi->hide();
            //             ui->rightIndi->hide();
            //         }
            //         indiFlag=!indiFlag;

            //     }
            // });
            // inditimer->start();

    static lightStates hlStatus = OFF_BEAM;


    int speedVal = 0;
    int rpmVal = 0;

    // char dummy[3]="";
    QString dummy;
    QString oDummy;

        string buffg = message.toStdString();

        // const char* bufrr =buffg.c_str();
        const char* bufrr =buffg.c_str();

        sprintf(buff,"%s",message.toStdString());
        ui->LstConsole->addItem(message);

        if(strcmp(bufrr,"C0")==0)
        {
            ui->seatIndi->hide();
        }
        if(strcmp(bufrr,"C1")==0)
        {
            ui->seatIndi->show();
        }

        /////////////////////////////
        if(strcmp(bufrr,"H0")==0)
        {
            ui->hBrakeIndi->hide();
        }
        if(strcmp(bufrr,"H1")==0)
        {
            ui->hBrakeIndi->show();
        }

        /////////////////////////////
        // if(strcmp(bufrr,"O0")==0)
        // {
        //     ui->oilindi->hide();
        // }
        // if(strcmp(bufrr,"O1")==0)
        // {
        //     ui->oilindi->show();
        // }

        /////////////////////////////
        if(strcmp(bufrr,"W0")==0)
        {
            ui->warningIndi->hide();
        }
        if(strcmp(bufrr,"W1")==0)
        {
            ui->warningIndi->show();
        }

        //////// LIGHT BEAM ///////////
        ///


        if(strcmp(bufrr,"L0")==0)
        {
            hlStatus = OFF_BEAM;
        }
        if(strcmp(bufrr,"L1")==0)
        {
            hlStatus = LOW_BEAM;
        }
        if(strcmp(bufrr,"L2")==0)
        {
            hlStatus = HIGH_BEAM;
        }


        /////////////////////////////
        if(bufrr[0] == 'S')
        {
            // QString dummy = QString::fromLatin1(bufrr + 1, 3);

                for(int i=0;i<4;i++)
                {
                    dummy.append(bufrr[i+1]);
                }
            // speedVal = atoi(dummy);
            // ui->LstConsole->addItem((QString)speedVal);
            // cout<<speedVal;
            bool ok;
            speedVal = dummy.toInt(&ok);
            // ui->graphicsView->rotate(speedVal);

            /////////////////////////////////////

            disCount = disCount + speedVal;
            // ui->odometer->display(disCount);

            if(prevValue < speedVal)
            {
                ui->leftGView->rotate(speedVal);
                // prevValue = (value);
            }
            else
            {
                ui->leftGView->rotate(-speedVal);
                // prevValue = -value;
            }

            if(speedVal <= 0)
            {
                ui->leftGView->resetTransform();
                prevValue = 0;
            }

            else if(speedVal >= 23)
            {
                ui->leftGView->rotate(22);
                prevValue = 22;
            }
            else
                prevValue = speedVal;

            // static lightStates hlStatus = 0;

            // if(strcmp(bufrr,"L0")==0)
            // {
            //     hlStatus = OFF_BEAM;
            // }
            // if(strcmp(bufrr,"L1")==0)
            // {
            //     hlStatus = LOW_BEAM;
            // }
            // if(strcmp(bufrr,"L2")==0)
            // {
            //     hlStatus = HIGH_BEAM;
            // }


            if(speedVal >= 15)
            {
                speedIndi = HIGH_SPEED;

                // if(hlStatus == OFF_BEAM)
                // {
                //     QPixmap pix8("C:/Users/Rohith/Desktop/qtResources/pics/car3-removebg-preview.png");
                //     int width8 = ui->centerConsole->width();
                //     int height8 = ui->centerConsole->height();
                //     ui->centerConsole->setPixmap(pix8.scaled(width8,height8,Qt::KeepAspectRatio));
                //     // ui->centerConsole->
                // }
                // else if(hlStatus == LOW_BEAM || hlStatus == HIGH_BEAM)
                // {
                //     QPixmap pix9("C:/Users/Rohith/Desktop/qtResources/pics/car6.png");
                //     int width9 = ui->centerConsole->width();
                //     int height9 = ui->centerConsole->height();
                //     ui->centerConsole->setPixmap(pix9.scaled(width9,height9,Qt::KeepAspectRatio));
                //     // ui->centerConsole->
                // }

            }
            else
            {
                speedIndi = LOW_SPEED;

                // if(hlStatus == OFF_BEAM)
                // {
                //     QPixmap pix7("C:/Users/Rohith/Desktop/qtResources/pics/car4-removebg-preview.png");
                //     int width7 = ui->centerConsole->width();
                //     int height7 = ui->centerConsole->height();
                //     ui->centerConsole->setPixmap(pix7.scaled(width7,height7,Qt::KeepAspectRatio));
                // }
                // else if(hlStatus == LOW_BEAM || hlStatus == HIGH_BEAM)
                // {
                //     QPixmap pix10("C:/Users/Rohith/Desktop/qtResources/pics/car5.png");
                //     int width10 = ui->centerConsole->width();
                //     int height10 = ui->centerConsole->height();
                //     ui->centerConsole->setPixmap(pix10.scaled(width10,height10,Qt::KeepAspectRatio));
                // }
            }

            char daBuff[10];
            sprintf(daBuff,"%d\0",speedVal*4);
            QString mm = QString(daBuff);
            // _controller.send(QString(buff));
            // _controller.send(mm);

            ui->speed->setText(mm);

            /////// ODOMETER  //////////////////
            ///
            static int preDist=0;
            preDist = preDist + speedVal*4;

            // char disBuff[10];
            // sprintf(daBuff,"%d\0",preDist);
            // QString disMeasurement = QString(daBuff);
            ui->odometer->display(preDist);



            ////////////////////////////////////
        }


        if(speedIndi == LOW_SPEED)
        {
            if(hlStatus == OFF_BEAM)
            {
                QPixmap pix7("C:/Users/Rohith/Desktop/qtResources/pics/car4-removebg-preview.png");
                int width7 = ui->centerConsole->width();
                int height7 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix7.scaled(width7,height7,Qt::KeepAspectRatio));
            }
            else if(hlStatus == LOW_BEAM /*|| hlStatus == HIGH_BEAM*/)
            {
                QPixmap pix10("C:/Users/Rohith/Desktop/qtResources/pics/car8.png");
                int width10 = ui->centerConsole->width();
                int height10 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix10.scaled(width10,height10,Qt::KeepAspectRatio));
            }

            else if(hlStatus == HIGH_BEAM)
            {
                QPixmap pix11("C:/Users/Rohith/Desktop/qtResources/pics/car5.png");
                int width11 = ui->centerConsole->width();
                int height11 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix11.scaled(width11,height11,Qt::KeepAspectRatio));
            }
        }
        else if(speedIndi == HIGH_SPEED)
        {
            if(hlStatus == OFF_BEAM)
            {
                QPixmap pix8("C:/Users/Rohith/Desktop/qtResources/pics/car3-removebg-preview.png");
                int width8 = ui->centerConsole->width();
                int height8 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix8.scaled(width8,height8,Qt::KeepAspectRatio));
                // ui->centerConsole->
            }
            else if(hlStatus == LOW_BEAM /*|| hlStatus == HIGH_BEAM*/)
            {
                QPixmap pix9("C:/Users/Rohith/Desktop/qtResources/pics/car7.png");
                int width9 = ui->centerConsole->width();
                int height9 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix9.scaled(width9,height9,Qt::KeepAspectRatio));
                // ui->centerConsole->
            }
            else if(hlStatus == HIGH_BEAM)
            {
                QPixmap pix12("C:/Users/Rohith/Desktop/qtResources/pics/car6.png");
                int width12 = ui->centerConsole->width();
                int height12 = ui->centerConsole->height();
                ui->centerConsole->setPixmap(pix12.scaled(width12,height12,Qt::KeepAspectRatio));
                // ui->centerConsole->
            }
        }

        /////////////////////////////
        // if(bufrr[0] == 'G')
        // {
        //     for(int i=0;i<2;i++)
        //     {
        //         dummy[i]=bufrr[i+1];
        //     }

        //     bool ok;
        //     speedVal = dummy.toInt(&ok);


        //     // speedVal = atoi(dummy);
        //     // ui->LstConsole->addItem((QString)speedVal);
        //     cout<<speedVal;

        //     ui->graphicsView->rotate(speedVal);
        // }

        //////////////////////////////
        ///
        ///

        // static QTimer *Ptimer = new QTimer(this);
        // constexpr int pT = 800;

        // if(bufrr[0]=='I')
        // {
        //     connect(Ptimer, &QTimer::timeout, this, [this]{
        //         // IndiChecker(1);

        //         if(strcmp(bufrr,"I0")==0)
        //         {
        //             pStatus =! pStatus;

        //             if(pStatus==1)
        //             {
        //                 ui->rightIndi->show();
        //                 ui->leftIndi->show();
        //             }
        //             else
        //             {
        //                 ui->rightIndi->hide();
        //                 ui->leftIndi->hide();
        //             }
        //         }


        //         // if(pKStatus==0)
        //         // {
        //         //     ui->rightIndi->hide();
        //         //     ui->leftIndi->hide();
        //         //     // Ptimer->stop();

        //         // }
        //     });
        // }


        ////////////////////////////// INDICATOR////
        ///



        if(bufrr[0]=='I')
        {
            if(strcmp(bufrr,"I0"))
            {
               IndiStatus=I_OFF;
            }
            if(strcmp(bufrr,"I1"))
            {
                IndiStatus=PARK;
            }
            if(strcmp(bufrr,"I2"))
            {
                IndiStatus=LEFT;
            }
            if(strcmp(bufrr,"I3"))
            {
                IndiStatus=RIGHT;
            }


                // inditimer->setInterval(indiT);
                // connect(inditimer, &QTimer::timeout, this, [this]{
                //     if(IndiStatus == (int)I_OFF )
                //     {
                //         ui->leftIndi->hide();
                //         ui->rightIndi->hide();
                //         inditimer->stop();
                //     }
                //     if(IndiStatus == (int)PARK )
                //     {
                //         if(indiFlag == 0)
                //         {
                //             ui->leftIndi->hide();
                //             ui->rightIndi->hide();
                //         }
                //         else
                //         {
                //             ui->leftIndi->show();
                //             ui->rightIndi->show();
                //         }

                //         indiFlag=!indiFlag;

                //     }
                //     if(IndiStatus == (int)LEFT )
                //     {
                //         if(indiFlag == 0)
                //         {
                //             ui->leftIndi->show();
                //             ui->rightIndi->hide();
                //         }
                //         else
                //         {
                //             ui->leftIndi->hide();
                //             ui->rightIndi->hide();
                //         }
                //         indiFlag=!indiFlag;

                //     }

                //     if(IndiStatus == (int)RIGHT )
                //     {
                //         if(indiFlag == 0)
                //         {
                //             ui->leftIndi->hide();
                //             ui->rightIndi->show();
                //         }
                //         else
                //         {
                //             ui->leftIndi->hide();
                //             ui->rightIndi->hide();
                //         }
                //         indiFlag=!indiFlag;

                //     }
                // });
                // inditimer->start();



                // static int indiFlag = 0;

                // inditimer->setInterval(indiT);
                // connect(inditimer, &QTimer::timeout, this, [this]{
                //     if(IndiStatus == I_OFF )
                //     {
                //         ui->leftIndi->hide();
                //         ui->rightIndi->hide();
                //     }
                //     if(IndiStatus == PARK )
                //     {
                //         if(indiFlag == 0)
                //         {
                //             ui->leftIndi->hide();
                //             ui->rightIndi->hide();
                //         }
                //         else
                //         {
                //             ui->leftIndi->show();
                //             ui->rightIndi->show();
                //         }
                //         indiFlag=!indiFlag;

                //     }
                // });
                // inditimer->start();

        }

        inditimer->setInterval(indiT);
        connect(inditimer, &QTimer::timeout, this, [this]{

            if(IndiStatus == I_OFF )
            {
                ui->leftIndi->hide();
                ui->rightIndi->hide();
                inditimer->stop();
            }
            if(IndiStatus == PARK )
            {
                if(indiFlag == 0)
                {
                    ui->leftIndi->hide();
                    ui->rightIndi->hide();
                }
                else
                {
                    ui->leftIndi->show();
                    ui->rightIndi->show();
                }

                indiFlag=!indiFlag;

            }
            if(IndiStatus == LEFT )
            {
                if(indiFlag == 0)
                {
                        // ui->leftIndi->show();
                    ui->leftIndi->hide();
                    ui->rightIndi->show();
                }
                else
                {
                    ui->leftIndi->hide();
                    ui->rightIndi->hide();
                }
                indiFlag=!indiFlag;

            }

            if(IndiStatus == RIGHT )
            {
                if(indiFlag == 0)
                {
                    ui->leftIndi->show();
                    ui->rightIndi->hide();

                        // ui->rightIndi->show();
                }
                else
                {
                    ui->leftIndi->hide();
                    ui->rightIndi->hide();
                }
                indiFlag=!indiFlag;

            }
        });
        inditimer->start();

        // static int indiFlag = 0;
        // static QTimer *inditimer = new QTimer(this);

        // inditimer->setInterval(indiT);
        // connect(inditimer, &QTimer::timeout, this, [this]{
        //     if(IndiStatus == I_OFF )
        //     {
        //         ui->leftIndi->hide();
        //         ui->rightIndi->hide();
        //     }
        //     if(IndiStatus == PARK )
        //     {
        //         if(indiFlag == 0)
        //         {
        //             ui->leftIndi->hide();
        //             ui->rightIndi->hide();
        //         }
        //         else
        //         {
        //             ui->leftIndi->show();
        //             ui->rightIndi->show();
        //         }
        //         indiFlag=!indiFlag;

        //     }
        // });
        // inditimer->start();

            // if(strcmp(bufrr,"I0")==0)
            // {
            //     ui->rightIndi->hide();
            //     ui->leftIndi->hide();
            //     // ui->pushButton_2->hide();
            // }

        // static QTimer *Ptimer = new QTimer(this);
        // constexpr int pT = 800;

        // if(strcmp(bufrr,"I1")==0)
        // {
        //     // static QTimer *Ptimer = new QTimer(this);
        //     // constexpr int pT = 800;
        //     static int pStatus = 0;
        //     static int pKStatus = 0;

        //     pKStatus =! pKStatus;
        //     Ptimer->setInterval(pT);
        //     connect(Ptimer, &QTimer::timeout, this, [this]{
        //         // IndiChecker(1);
        //         pStatus =! pStatus;
        //         if(pStatus==1)
        //         {
        //             ui->rightIndi->show();
        //             ui->leftIndi->show();
        //         }
        //         else
        //         {
        //             ui->rightIndi->hide();
        //             ui->leftIndi->hide();
        //         }

        //         if(pKStatus==0)
        //         {
        //             ui->rightIndi->hide();
        //             ui->leftIndi->hide();
        //             // Ptimer->stop();

        //         }
        //     });
        //     // Ptimer->start();
        //     if(pKStatus==0)
        //     {
        //         ui->rightIndi->hide();
        //         ui->leftIndi->hide();
        //         // Ptimer->stop();

        //     }

        // }
        // Ptimer->start();

        // if(strcmp(bufrr,"I2")==0)
        // {
        //     static int liStatus = 0;
        //     static int liKStatus = 0;

        //     liKStatus =! liKStatus;
        //     Ptimer->setInterval(pT);
        //     connect(Ptimer, &QTimer::timeout, this, [this]{
        //         // IndiChecker(1);
        //         liStatus =! liStatus;
        //         if(liStatus==1)
        //         {
        //             // ui->rightIndi->show();
        //             ui->leftIndi->show();
        //         }
        //         else
        //         {
        //             // ui->rightIndi->hide();
        //             ui->leftIndi->hide();
        //         }

        //         if(liKStatus==0)
        //         {
        //             ui->rightIndi->hide();
        //             ui->leftIndi->hide();
        //             // Ptimer->stop();

        //         }
        //     });
        //     // Ptimer->start();
        //     if(liKStatus==0)
        //     {
        //         ui->rightIndi->hide();
        //         ui->leftIndi->hide();
        //         // Ptimer->stop();

        //     }
        //     // ui->warningIndi->hide();
        // }
            // if(strcmp(bufrr,"I3")==0)
            // {
            //     ui->warningIndi->show();
            // }

        ////////////////////////////////////////
        // if(strcmp(bufrr,"F2")==0)
        if(bufrr[0]=='F')
        {
            // ui->warningIndi->hide();

            for(int i=0;i<4;i++)
            {
                dummy.append(bufrr[i+1]);
            }
            // speedVal = atoi(dummy);
            // ui->LstConsole->addItem((QString)speedVal);
            // cout<<speedVal;
            bool ok;
            int fuelVal = dummy.toInt(&ok);


            if(fuelVal >= 90)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/full.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                ui->fuelLabel->setStyleSheet("color: #3DFF73");
                ui->petrolindi->hide();
            }
            if(fuelVal >= 75 && fuelVal < 90)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/fullmOne.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                ui->fuelLabel->setStyleSheet("color: #3DFF73");
                ui->petrolindi->hide();
            }
            if(fuelVal >= 60 && fuelVal < 75)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/fullmTwo.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                ui->fuelLabel->setStyleSheet("color: #3DFF73");
                ui->petrolindi->hide();
            }
            if(fuelVal >= 50 && fuelVal < 60)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/quaterY.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                ui->fuelLabel->setStyleSheet("color: #FBFF3D");
                ui->petrolindi->hide();

            }
            if(fuelVal >= 20 && fuelVal < 50)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/lessY.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                ui->fuelLabel->setStyleSheet("color: #FBFF3D");
                ui->petrolindi->hide();

            }
            if(fuelVal <= 20)
            {
                QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/veryLess.png");
                int width5 = ui->lvlFullFuel->width();
                int height5 = ui->lvlFullFuel->height();
                ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
                // ui->fuelLabel->setStyleSheet("{color: #F91818}");
                ui->fuelLabel->setStyleSheet("color: #F91818;");


                // QColor color = QColorDialog::getColor(Qt::red, this);
                // QPalette palette = ui->fuelLabel->palette();
                // palette.setColor(QPalette::WindowText, color);
                // ui->fuelLabel->setPalette(palette);

                ui->petrolindi->show();
            }

        }



    // if(buff == "C0")
    // {
    //     ui->seatIndi->hide();
    // }
    // if(buff == "C1")
    // {
    //     ui->seatIndi->show();
    // }
        // }


        /////////////////////////////////////////////////////////////////////
        ///

        ////////////////////////////////////////
        // if(strcmp(bufrr,"F2")==0)
        if(bufrr[0]=='O')
        {
            // ui->warningIndi->hide();

            for(int i=0;i<4;i++)
            {
                oDummy.append(bufrr[i+1]);
            }
            // speedVal = atoi(dummy);
            // ui->LstConsole->addItem((QString)speedVal);
            // cout<<speedVal;
            bool ok;
            int oilVal = oDummy.toInt(&ok);


            if(oilVal >= 90)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/full.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #3DFF73");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->hide();

            }
            if(oilVal >= 75 && oilVal < 90)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/fullmOne.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #3DFF73");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->hide();
            }
            if(oilVal >= 60 && oilVal < 75)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/fullmTwo.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #3DFF73");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->hide();
            }
            if(oilVal >= 50 && oilVal < 60)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/quaterY.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #FBFF3D");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->hide();
            }
            if(oilVal >= 20 && oilVal < 50)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/lessY.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #FBFF3D");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->hide();

            }
            if(oilVal <= 20)
            {
                QPixmap pix6("C:/Users/Rohith/Desktop/qtResources/pics/veryLess.png");
                int width6 = ui->oilTempIndi->width();
                int height6 = ui->oilTempIndi->height();
                ui->oilTempIndi->setPixmap(pix6.scaled(width6,height6,Qt::KeepAspectRatio));
                ui->engLabel->setStyleSheet("color: #F91818;");
                // ui->engLabel->setStyleSheet("font-weight: bold;");
                ui->oilindi->show();
            }



            // if(fuelVal <= 10)
            // {
            //     QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/veryLess");
            //     int width5 = ui->lvlFullFuel->width();
            //     int height5 = ui->lvlFullFuel->height();
            //     ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
            // }
            // if(fuelVal <= 10)
            // {
            //     QPixmap pix5("C:/Users/Rohith/Desktop/qtResources/pics/veryLess");
            //     int width5 = ui->lvlFullFuel->width();
            //     int height5 = ui->lvlFullFuel->height();
            //     ui->lvlFullFuel->setPixmap(pix5.scaled(width5,height5,Qt::KeepAspectRatio));
            // }


        }


        /////////////////////////////////////////////////////////
        ///
        /////////////////////////////
        if(bufrr[0] == 'R')
        {
            // QString dummy = QString::fromLatin1(bufrr + 1, 3);

            for(int i=0;i<4;i++)
            {
                dummy.append(bufrr[i+1]);
            }
            // speedVal = atoi(dummy);
            // ui->LstConsole->addItem((QString)speedVal);
            // cout<<speedVal;
            bool ok;
            rpmVal = dummy.toInt(&ok);
            // ui->graphicsView->rotate(speedVal);

            /////////////////////////////////////

            rpmdisCount = rpmdisCount + rpmVal;
            // ui->odometer->display(disCount);

            if(rpmprevValue < rpmVal)
            {
                ui->rightGView->rotate(rpmVal);
                // prevValue = (value);
            }
            else
            {
                ui->rightGView->rotate(-rpmVal);
                // prevValue = -value;
            }

            if(rpmVal <= 0)
            {
                ui->rightGView->resetTransform();
                rpmprevValue = 0;
            }

            else if(rpmVal >= 22)
            {
                ui->rightGView->rotate(22);
                rpmprevValue = 22;
            }
            else
                rpmprevValue = rpmVal;


            if(rpmprevValue >=18)
            {
                ui->shiftUp->show();
            }
            else
            {
                ui->shiftUp->hide();
            }

            ////////////////////////////////////
        }

        //////////////////////////////////////////
        ///
        // static QString gN;
        if(strcmp(bufrr,"G-1")==0)
        {
            gN = 'R';
            // ui->gearNum->setText('R');
        }
        if(strcmp(bufrr,"G0")==0)
        {
            gN = 'N';

            // ui->gearNum->setText('N');
        }
        if(strcmp(bufrr,"G1")==0)
        {
            gN = '1';

            // ui->gearNum->setText('1');
        }
        if(strcmp(bufrr,"G2")==0)
        {
            gN = '2';

            // ui->gearNum->setText('2');
        }
        if(strcmp(bufrr,"G3")==0)
        {
            gN = '3';

            // ui->gearNum->setText('3');
        }
        if(strcmp(bufrr,"G4")==0)
        {
            gN = '4';

            // ui->gearNum->setText('4');
        }
        if(strcmp(bufrr,"G5")==0)
        {
            gN = '5';

            // ui->gearNum->setText('5');
        }
        if(strcmp(bufrr,"G6")==0)
        {
            gN = '6';

            // ui->gearNum->setText('6');
        }

        ui->gearNum->setText(gN);

    // buff=" ";
}
