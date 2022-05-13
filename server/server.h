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



    loginAndRegister * logreg;

    QTcpServer *myServer;
    QTcpSocket *myTcp;
    QTcpSocket * t;

    QList<user*> MatchQueue;

    void getTcp(QTcpSocket * , int);

    QList<user*> userList;

    bool Result;

    void openLisnt();

signals:
    void myreadyRead(QString str);
    void setTcp(QTcpSocket* tcp);

    void send04(int);
    void send05(int);
};

#endif // SERVER_H
