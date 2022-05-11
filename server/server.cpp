#include "server.h"

#include <QTcpSocket>
#include <QThreadPool>



server::server(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);

    connect(myServer, &QTcpServer::newConnection, [=]{
        QThread* sub = new QThread;
        t = myServer->nextPendingConnection();

        logreg = new loginAndRegister (t, this) ;
        connect(logreg, &loginAndRegister::returnTcp, this, &server::getTcp);

        logreg->moveToThread(sub);

        sub->start();

        logreg->work();
    });

    delete logreg;
}

void server::getResult(bool r)
{
    Result = r;
}

void server::getTcp(QTcpSocket *retTcp)
{
    qDebug() << retTcp;
    SocketList.append(retTcp);
    qDebug() << SocketList.length();

}

void server::openLisnt()
{
    unsigned short port = 8888;
    myServer->listen(QHostAddress::Any, port);
    qDebug() << "开启监听～";
}

