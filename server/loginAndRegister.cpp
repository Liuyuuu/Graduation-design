#include "loginAndRegister.h"

#include <QDebug>


// 当
loginAndRegister::loginAndRegister(QTcpSocket* t, QObject *parent) : myTcp(t),QObject(parent)
{
    SocketList.append(myTcp);
}

void loginAndRegister::work()
{
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
bool loginAndRegister::ValidationData()
{
    for(int i = 0; i < SocketList.size(); i++)
    {
        if(SocketList[i]->bytesAvailable() > 0)
        {
            QString str = SocketList[i]->readAll();
            qDebug() << "登录请求：" << str;

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
        }
    }
}

