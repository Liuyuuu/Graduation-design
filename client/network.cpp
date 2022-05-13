#include "network.h"

#include <QHostAddress>
#include <QMessageBox>

network::network(QObject *parent) : QObject(parent)
{
    //连接服务器
    _tcp_login = new QTcpSocket(this);
    _ip = "192.168.154.128";
    _port = 8888;
    _logtag = false;

    connectServer();

    // 连接成功槽函数
    connect(_tcp_login, &QTcpSocket::connected, this, [=](){
        _logtag = true;
        qDebug() << "服务器连接成功！";
        emit connected();
    });

    // 断开连接
    connect(_tcp_login, &QTcpSocket::disconnected, this, [=]{
        _logtag = false;
        qDebug() << "服务器断开连接";
        //QMessageBox::information(NULL, "提示", "服务器断开连接");
        emit disConnect();
    });

    // 收到数据
    connect(_tcp_login, &QTcpSocket::readyRead, this, [=]{
         QString str = _tcp_login->readAll().toStdString().data();
         switch (str.mid(0,2).toUInt()) {
             case 0: qDebug()<<"登录失败"; emit send00(); break;
             case 1: qDebug()<<"注册失败"; emit send01(); break;
             case 2: qDebug()<<"登录成功"; emit send02(str.mid(2,6)); break;
             case 3: qDebug()<<"注册成功"; emit send03(str.mid(2,6)); break;
         case 4: qDebug()<<"游戏开始"; emit send04(str.mid(2,1).toShort(), str.mid(3,6).toInt());break;
         }
    });


}

void network::connectServer()
{
    _tcp_login->connectToHost(QHostAddress(_ip), _port);
}

void network::send(QByteArray str)
{
    _tcp_login->write(str);
}

bool network::gitLogtag()
{
    return _logtag;
}

