#include "server.h"

#include <QTcpSocket>
#include <QThreadPool>


// send04 开始匹配 04 ID(6)
// send05 停止匹配 05 ID(6)

// 接收 04-05



server::server(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);
    QThread* sub = new QThread;

    // 有新的客户端连接
    connect(myServer, &QTcpServer::newConnection, [=]{

        t = myServer->nextPendingConnection();

        logreg = new loginAndRegister (t, this) ;
        connect(logreg, &loginAndRegister::returnTcp, this, &server::getTcp);
        connect(this, &server::send04, this, &server::beginToMatch);
        connect(this, &server::send05, this, &server::stopToMatch);


        logreg->moveToThread(sub);

        sub->start();

        logreg->work();


    });


}

void server::getResult(bool r)
{
    Result = r;
}

void server::action()
{

}


// 将用户送入匹配队列
void server::beginToMatch(int num)
{
    qDebug() << "开始排队 用户：" << num;
    for(int i = 0; i < userList.length(); i++)
    {
        if(userList[i]->id == num)
        {
            MatchQueue.append(userList.takeAt(i));
            i--;
        }

        // 当排队队列大于二时，开启线程，启动服务
        if(MatchQueue.length() >= 2)
        {
            QThread* sub2 = new QThread;
            gameAction * game = new gameAction(MatchQueue.takeAt(0), MatchQueue.takeAt(0));

            connect(game,&gameAction::sendSignal,this,&server::sendSlot);
            game->moveToThread(sub2);
            sub2->start();
        }
        qDebug() << MatchQueue.length();
    }

}

void server::stopToMatch(int num)
{

}

// 替线程发送信号
void server::sendSlot(QTcpSocket * tcp,QString str)
{
    tcp->write(str.toUtf8());
}


// 登录成功 将用户送入登录队列
// send04
// send05

// 接收 04 05
void server::getTcp(QTcpSocket *retTcp, int id)
{
    userList.append(new user(retTcp, id));
    connect(retTcp, &QTcpSocket::readyRead, this, [=]{
        QString str = retTcp->readAll().toStdString().data();
        qDebug() << "sfasdfasd" << str;
        if(str.mid(0,2) == "04")
        {
            emit send04(str.mid(2,6).toInt());
        }
        if(str.mid(0,2) == "05")
        {
            emit send05(str.mid(2,6).toInt());
        }

    });

}


// 开启监听
void server::openLisnt()
{
    unsigned short port = 8888;
    myServer->listen(QHostAddress::Any, port);
    qDebug() << "开启监听～";
}



