#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

#include "db.h"

class loginAndRegister : public QObject
{
    Q_OBJECT
public:
    explicit loginAndRegister(QTcpSocket* t, QObject *parent = nullptr);

    void work();
    bool ValidationData();


    QTcpSocket *myTcp;
<<<<<<< HEAD
    QList<QTcpSocket*> SocketList;  //连接服务器的Socket列表
=======
    QList<QTcpSocket*> SocketList;
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
    db * databeas;

signals:
    void returnResult(bool);
    void returnTcp(QTcpSocket*, int);

};

#endif // MYWORK_H
