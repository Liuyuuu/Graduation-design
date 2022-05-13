#ifndef GAMEACTION_H
#define GAMEACTION_H

#include <QObject>
#include <QTcpSocket>
#include "user.h"


class gameAction : public QObject
{
    Q_OBJECT
public:

    user* user1;
    user* user2;
    gameAction(user* tmp1, user* tmp2, QObject *parent = nullptr);


signals:

};

#endif // GAMEACTION_H
