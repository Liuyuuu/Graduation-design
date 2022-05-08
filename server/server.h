#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    QTcpServer *myServer;
    QTcpSocket *myTcp;

signals:

};

#endif // SERVER_H
