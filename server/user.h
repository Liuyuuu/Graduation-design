#ifndef USER_H
#define USER_H

#include <QObject>
#include <QTcpSocket>

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QTcpSocket * tmp, int tmp1, QObject *parent = nullptr);
    user();
    QTcpSocket *tcp;
    int id;

signals:

};

#endif // USER_H
