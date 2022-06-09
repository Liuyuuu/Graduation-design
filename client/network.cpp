#include "network.h"



network::network(QObject *parent) : QObject(parent)
{
    //连接服务器
    _tcp_login = new QTcpSocket(this);
    _ip = "192.168.154.128";
    _port = 8888;
    _logtag = false;

    myConnect();
    // 连接服务器
    connectServer();

}

void network::myConnect()
{
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
<<<<<<< HEAD
    connect(_tcp_login, &QTcpSocket::readyRead, this, &network::command);
=======
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

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9

}

// 游戏开始
void network::beginToMatch(int id)
{
    QString  str = "04" + QString::number(id,10);
    send(str.toUtf8());
}

// 游戏结束
void network::StopToMatch(int id)
{
    QString  str = "05" + QString::number(id,10);
    send(str.toUtf8());
}

// 连接服务器
void network::connectServer()
{
    _tcp_login->connectToHost(QHostAddress(_ip), _port);
}

// 发送消息到服务器
void network::send(QByteArray str)
{
    _tcp_login->write(str);
}

// 获取登录状态
bool network::gitLogtag()
{
    return _logtag;
}

// 接收网络命令
void network::command()
{
    QString instruct = _tcp_login->readAll().toStdString().data();

    qDebug() <<instruct;
    switch (instruct.mid(0,2).toInt()) {

        case 0: qDebug() << "密码错误"; emit instruct00(); break;
        case 1: qDebug() << "注册失败"; emit instruct01(); break;
        case 2: qDebug() << "登录成功"; emit instruct02(instruct.mid(2,6).toUInt()); break;
        case 3: qDebug() << "注册成功"; emit instruct03(instruct.mid(2,6).toUInt()); break;
//        case 4: qDebug() << "开始匹配"; emit instruct04();break;
//        case 5: qDebug() << "停止匹配";break;
        case 6: qDebug() << "对局开始黑方红方";emit instruct06(instruct.mid(2,7));break;
        case 7: qDebug() << "对方求和";break;
        case 8: qDebug() << "对方悔棋";break;
        case 9: qDebug() << "我方悔棋结果";break;
        case 10: qDebug() << "我方求和结果";break;
        case 11: qDebug() << "对局结束结果"; emit instruct11();break;
        case 12: qDebug() << "对方走棋路径"; emit instruct12(instruct.mid(2));break;
        case 13: qDebug() << "注册成功"; break;
        case 14: qDebug() << "对方发送的消息"; emit instruct14(instruct.mid(2));break;

    }
}

void network::clearTcp()
{

}

