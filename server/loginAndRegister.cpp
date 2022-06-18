#include "loginAndRegister.h"

#include <QDebug>

<<<<<<< HEAD

// 当
=======
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
loginAndRegister::loginAndRegister(QTcpSocket* t, QObject *parent) : myTcp(t),QObject(parent)
{
    SocketList.append(myTcp);
}

void loginAndRegister::work()
{
<<<<<<< HEAD
    databeas = new db;

    connect(myTcp, &QTcpSocket::readyRead, this, [=]{
        ValidationData();
    });

}



// send00 密码错误 00
// send01 注册失败 01
// send02 登录成功 02+ID(6)
// send03 注册成功 03+ID(6)
// 接收 00 01 02 03
=======
    qDebug() << "子线程" << myTcp;

    databeas = new db;

    connect(myTcp, &QTcpSocket::readyRead, this, [=]{


        ValidationData();

    });



}

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
bool loginAndRegister::ValidationData()
{
    for(int i = 0; i < SocketList.size(); i++)
    {
        if(SocketList[i]->bytesAvailable() > 0)
        {
            QString str = SocketList[i]->readAll();
<<<<<<< HEAD
            qDebug() << "登录请求：" << str;

=======
            qDebug() << str;
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
            if(str.mid(0,2) == "00")
            {
                if(databeas->sel(str.mid(2,6).toInt(), str.mid(8)))
                {
                    // send02
                    SocketList[i]->write(QByteArray("02"+str.mid(2,6).toUtf8()));
                    emit returnTcp(SocketList.takeAt(i), str.mid(2,6).toInt());
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
                    emit returnTcp(SocketList.takeAt(i), str.mid(2,6).toInt());
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
<<<<<<< HEAD
=======

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
        }
    }
}

<<<<<<< HEAD
=======




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
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
