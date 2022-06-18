#include "gameaction.h"

<<<<<<< HEAD

// send06 对局开始黑方红方 06 bool(1) ID(6)
gameAction::gameAction(user * tmp1, user * tmp2, QObject *parent) :user1(tmp1), user2(tmp2), QObject(parent)
{
    lock = true;
    //qDebug() << "用户1 id ：" << user1->id << "用户2 id ：" << user2->id;

    tmp1->tcp->disconnect();
    tmp2->tcp->disconnect();

    // send06
    user1->tcp->write(QByteArray(QByteArray("060") + QByteArray::number(user2->id)));
    user2->tcp->write(QByteArray(QByteArray("061") + QByteArray::number(user1->id)));


    // 对句中的消息
    connect(user1->tcp, &QTcpSocket::readyRead, this, [=]{
        str = user1->tcp->readAll();
        instruction(true);
    });
    connect(user2->tcp, &QTcpSocket::readyRead, this, [=]{
        str = user2->tcp->readAll();
        instruction(false);
    });

}

//
void gameAction::instruction(bool temp)
{
    // 延时
    switch (str.mid(0,2).toInt())
    {
        case 6: qDebug() << "请求和棋";send07(temp); break;
        case 7: qDebug() << "请求悔棋";send08(temp); break;
        case 8: qDebug() << "和棋结果";send09(temp, str.mid(2,1).toInt()); break;
        case 9: qDebug() << "悔棋结果";send10(temp, str.mid(2,1).toInt()); break;
        case 10: qDebug() << "走棋"; move(temp); break;
        case 11: qDebug() << "输棋"; send11(temp);break;
        case 12: qDebug() << "聊天消息";send12(temp, str.mid(2)); break;
        //case 13: qDebug() << "请求和棋"; break;

    }

}void gameAction::move(bool tmp)
{
    if(tmp)
    {

        int id = str.mid(2,2).toInt();
        int x = 11 - str.mid(4,2).toInt();
        int y = 10 - str.mid(6,2).toInt();

        id = (id + 16) % 32;


        QString str = "12";
        if(id < 10) str = str + "0" + QString::number(id, 10);
        else str += QString::number(id, 10);
        if(x < 10) str = str + "0" + QString::number(x, 10);
        else str += QString::number(x, 10);
        if(y < 10) str = str + "0" + QString::number(y, 10);
        else str += QString::number(y, 10);

        emit sendSignal(user2->tcp,str);

    }
    else
    {

        int id = str.mid(2,2).toInt();
        int x = 11 - str.mid(4,2).toInt();
        int y = 10 - str.mid(6,2).toInt();

        id = (id + 16) % 32;


        QString str = "12";
        if(id < 10) str = str + "0" + QString::number(id, 10);
        else str += QString::number(id, 10);
        if(x < 10) str = str + "0" + QString::number(x, 10);
        else str += QString::number(x, 10);
        if(y < 10) str = str + "0" + QString::number(y, 10);
        else str += QString::number(y, 10);

        qDebug()<< "通过服务器发送的走起信息：" << str;
        emit sendSignal(user1->tcp,str);

    }
}



void gameAction::send07(bool tmp)
{
    if(tmp == true)
    {
        user2->tcp->write(QByteArray("07"));
    }
    else
    {
        user1->tcp->write(QByteArray("07"));
    }

}

void gameAction::send08(bool tmp)
{
    if(tmp == true)
    {
        user2->tcp->write(QByteArray("08"));
    }
    else
    {
        user1->tcp->write(QByteArray("08"));
    }

}

void gameAction::send09(bool tmp, int num)
{
    if(tmp)
    {
        if(num == 0)
        {

        }
        else
        {

        }
    }
    else
    {
        if(num == 0)
        {

        }
        else
        {

        }
    }
}

void gameAction::send10(bool tmp, int num)
{
    if(tmp)
    {
        if(num == 0)
        {

        }
        else
        {

        }
    }
    else
    {
        if(num == 0)
        {

        }
        else
        {

        }
    }
}

void gameAction::send11(bool tmp)
{
    if(tmp)
    {
        sendSignal(user2->tcp,"11");
    }
    else
    {
        sendSignal(user1->tcp,"11");
    }
}

void gameAction::send12(bool tmp,QString str)
{
    if(tmp)
    {
        sendSignal(user2->tcp, "14" + (QString::number(user2->id) + ":" + str).toUtf8());
        sendSignal(user1->tcp, "14" + (QString::number(user2->id) + ":" + str).toUtf8());
    }
    else
    {
        sendSignal(user1->tcp, "14" + (QString::number(user1->id) + ":" + str).toUtf8());
        sendSignal(user2->tcp, "14" + (QString::number(user1->id) + ":" + str).toUtf8());
    }
}

=======
gameAction::gameAction(user * tmp1, user * tmp2, QObject *parent) :user1(tmp1), user2(tmp2), QObject(parent)
{
    user1->tcp->write(QByteArray("040" + user2->id));
    user2->tcp->write(QByteArray("041" + user1->id));
}
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
