#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include <QHostAddress>
#include "DeviceController.h"

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
    void on_btnConnect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void device_dataReady(QByteArray data);


    void on_LightSw_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_HandBrk_clicked();

    void on_oilSw_clicked();

    void on_seatSw_clicked();

    void on_warningSw_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_parkIndiSw_clicked();

    void streamMaker(char sLabel, int qValue);


    void on_oilSlider_valueChanged(int value);

    void on_rpmSlider_valueChanged(int value);

    void on_gearUp_clicked();

    void on_gearRevrs_clicked();

    void on_gearDown_clicked();

    void on_leftIndiSw_clicked();

    void on_rightIndiSw_clicked();

private:
    Ui::MainWindow *ui;
    DeviceController _controller;

    //methods;
    void setDeviceController();
};
#endif // MAINWINDOW_H
