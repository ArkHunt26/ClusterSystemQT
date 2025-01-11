#include "myTcpServer.h"

#include <QDebug>


myTcpServer::myTcpServer(int port, QObject *parent)
    : QObject{parent}
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection, this, &myTcpServer::on_client_connecting);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted)
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started...";
    }


}

void myTcpServer::on_client_connecting()
{
    qDebug() << "a client connected to server";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, myTcpServer::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, myTcpServer::clientDisconnected);

    _socketsList.append(socket);
    socket->write("Welcome to this server");
    emit newClientConnected();
}

void myTcpServer::clientDisconnected()
{
    emit clientDisconnect();
}

void myTcpServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);
    foreach (auto s, _socketsList)
    {
        if(s != socket)
        {
            // continue;
            s->write(data.toUtf8());
        }
        // s->write(data.toUtf8());
    }
    // sendToAll(QString(data));
}

bool myTcpServer::isStarted() const
{
    return _isStarted;
}

// void myTcpServer::sendToAll(QString message)
// {
//     foreach (auto socket, _socketsList)
//     {
//         socket->write(message.toUtf8());
//     }
// }
