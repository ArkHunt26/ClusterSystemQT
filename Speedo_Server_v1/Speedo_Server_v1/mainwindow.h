#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStyle>
#include "myTcpServer.h"

#include <QGraphicsScene>
#include <QString>
#include <QDebug>

// typedef enum
// {
//     ALL_OFF=0,
//     INDI_ON,
//     INDI_OFF
// }indiDisp;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    // void on_newClient_Connected();
    void newClientConnected();


    void on_btnSendToAll_clicked();

    void clientDisconnected();

    void clientDataReceived(QString message);

    // void INDILIGHTINGS(indiDisp state);


private:
    Ui::MainWindow *ui;
    myTcpServer *_server;

    QGraphicsScene *Scene1;
    QGraphicsScene *Scene2;


};
#endif // MAINWINDOW_H
