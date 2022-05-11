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
    QList<QTcpSocket*> SocketList;
    db * databeas;

signals:
    void returnResult(bool);
    void returnTcp(QTcpSocket*);

};

#endif // MYWORK_H
