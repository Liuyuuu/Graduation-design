#include "server.h"

#include <QTcpSocket>



server::server(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);
    unsigned short port = 8888;
    myServer->listen(QHostAddress::Any, port);

    qDebug() << "开启监听～";

    connect(myServer, &QTcpServer::newConnection, this, [=]()
    {
        myTcp = myServer->nextPendingConnection();
        qDebug("成功和客户端建立了新的连接...");

        // 检测是否有客户端数据
        connect(myTcp, &QTcpSocket::readyRead, this, [=]()
        {
            // 接收数据
            QString recvMsg = myTcp->readAll();
            qDebug() << "客户端Say: " << recvMsg;
        });
        // 客户端断开了连接
        connect(myTcp, &QTcpSocket::disconnected, this, [=]()
        {
            qDebug() << "客户端已经断开了连接...";
            myTcp->deleteLater();
        });
    });

}
