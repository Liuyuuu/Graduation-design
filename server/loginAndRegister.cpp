#include "loginAndRegister.h"

#include <QDebug>

loginAndRegister::loginAndRegister(QTcpSocket* t, QObject *parent) : myTcp(t),QObject(parent)
{
    SocketList.append(myTcp);
}

void loginAndRegister::work()
{
    qDebug() << "子线程" << myTcp;

    databeas = new db;

    connect(myTcp, &QTcpSocket::readyRead, this, [=]{

        ValidationData();

    });



}

bool loginAndRegister::ValidationData()
{
    for(int i = 0; i < SocketList.size(); i++)
    {
        if(SocketList[i]->bytesAvailable() > 0)
        {
            QString str = SocketList[i]->readAll();
            if(str.mid(0,2) == "00")
            {
                if(databeas->sel(str.mid(2,6).toInt(), str.mid(8)))
                {
                    // send02
                    SocketList[i]->write(QByteArray("02"+str.mid(2,6).toUtf8()));
                    emit returnTcp(SocketList.takeAt(i));
                    i--;
                    return true;
                }else
                {
                    // send00
                    SocketList[i]->write(QByteArray("00"));
                    return false;
                }

            }

            if(str.mid(0,2) == "01")
            {
                if(databeas->ins(str.mid(2,6).toInt(), str.mid(8)))
                {
                    // send03
                    SocketList[i]->write(QByteArray("03"+str.mid(2,6).toUtf8()));
                    emit returnTcp(SocketList.takeAt(i));
                    i--;
                    return true;
                }
                else
                {
                    // send01
                    SocketList[i]->write("01");
                    return false;
                }
            }

        }
    }
}





#if 0
void loginAndRegister::run()
{
    setAutoDelete(false);

    connect(myTcp, &QTcpSocket::readyRead, this, [=]{
        foreach (QTcpSocket * temp, SocketList)
        {
            if(temp->bytesAvailable() > 0)
            {
                qDebug() << temp->readAll();
            }
        }
    });

    qDebug() << "子线程";






//    qDebug("成功和客户端建立了新的连接...");

//    // 检测是否有客户端数据
//    connect(myTcp, &QTcpSocket::readyRead, this, [=]()
//    {
//        // 接收数据
//        QString recvMsg = myTcp->readAll();
//        qDebug() << "客户端Say: " << recvMsg ;
//        qDebug() << "线程" << myTcp;

//        emit returnResult(true);
//    });
//    // 客户端断开了连接
//    connect(myTcp, &QTcpSocket::disconnected, this, [=]()
//    {
//        qDebug() << "客户端已经断开了连接...";
//        myTcp->deleteLater();
//    });

}

#endif
