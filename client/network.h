#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = nullptr);
    void connectServer();
    void send(QByteArray str);
    bool gitLogtag();
    void myConnect();
    void beginToMatch(int id);
    void StopToMatch(int id);
    void command();
    void clearTcp();

signals:

    void connected();
    void disConnect();
    void ready();
    void instruct00();
    void instruct01();
    void instruct02(int);
    void instruct03(int);
    void instruct06(QString str);
    void instruct11();
    void instruct12(QString str);
    void instruct14(QString str);

private:
    QTcpSocket * _tcp_login;
    QString _ip;
    int _port;
    bool _logtag;

};

#endif // NETWORK_H
