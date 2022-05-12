#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QDebug>

class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = nullptr);
    void connectServer();
    void send(QByteArray str);
    bool gitLogtag();

signals:
    void connected();
    void disConnect();
    void ready();

    void send00();
    void send01();
    void send02(QString);
    void send03(QString);

private:
    QTcpSocket * _tcp_login;
    QString _ip;
    int _port;
    bool _logtag;

};

#endif // NETWORK_H
