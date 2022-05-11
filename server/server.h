#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

#include "loginAndRegister.h"

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    void getResult(bool r);

    loginAndRegister * logreg;

    QTcpServer *myServer;
    QTcpSocket *myTcp;
    QTcpSocket * t;

    void getTcp(QTcpSocket * retTcp);

    QList<QTcpSocket*> SocketList;

    bool Result;

    void openLisnt();

signals:
    void myreadyRead(QString str);
    void setTcp(QTcpSocket* tcp);
};

#endif // SERVER_H
