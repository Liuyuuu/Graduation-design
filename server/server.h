#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

#include "loginAndRegister.h"
#include "gameaction.h"
#include "user.h"



class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    void getResult(bool r);
    void action();
    void beginToMatch(int num);
    void stopToMatch(int num);

<<<<<<< HEAD
    void sendSlot(QTcpSocket * tcp,QString str);



    loginAndRegister * logreg;  //Sock
=======


    loginAndRegister * logreg;
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9

    QTcpServer *myServer;
    QTcpSocket *myTcp;
    QTcpSocket * t;

<<<<<<< HEAD
    QList<user*> MatchQueue; // 对局队列

    void getTcp(QTcpSocket * , int);

    QList<user*> userList; //用户登录队列
=======
    QList<user*> MatchQueue;

    void getTcp(QTcpSocket * , int);

    QList<user*> userList;
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9

    bool Result;

    void openLisnt();

signals:
    void myreadyRead(QString str);
    void setTcp(QTcpSocket* tcp);

    void send04(int);
    void send05(int);
};

#endif // SERVER_H
