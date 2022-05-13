#include "server.h"

#include <QTcpSocket>
#include <QThreadPool>



server::server(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);
    QThread* sub = new QThread;

    connect(myServer, &QTcpServer::newConnection, [=]{

        t = myServer->nextPendingConnection();
        logreg = new loginAndRegister (t, this) ;
        connect(logreg, &loginAndRegister::returnTcp, this, &server::getTcp);

        logreg->moveToThread(sub);

        sub->start();

        logreg->work();
        connect(t, &QTcpSocket::readyRead,this, [=]{
            QString str = t->readAll();
            switch (str.mid(0,2).toUInt()) {

                case 4: qDebug() << "开始匹配"; beginToMatch(str.mid(2,6).toInt()); break;
                case 5: qDebug() << "停止匹配"; emit send05(str.mid(2,6).toInt()); break;

            }
        });

    });


}

void server::getResult(bool r)
{
    Result = r;
}

void server::action()
{

}

void server::beginToMatch(int num)
{
    for(int i = 0; i < userList.length(); i++)
    {
        if(userList[i]->id == num)
        {
            MatchQueue.append(userList.takeAt(i));
            i--;
        }
        if(MatchQueue.length() >= 2)
        {
            QThread* sub2 = new QThread;
            gameAction * game = new gameAction(MatchQueue.takeAt(0), MatchQueue.takeAt(0));

            game->moveToThread(sub2);
            sub2->start();
        }
    }

}

void server::stopToMatch(int num)
{

}

void server::getTcp(QTcpSocket *retTcp, int id)
{
    qDebug() << retTcp;
    userList.append(new user(retTcp, id));

}

void server::openLisnt()
{
    unsigned short port = 8888;
    myServer->listen(QHostAddress::Any, port);
    qDebug() << "开启监听～";
}

