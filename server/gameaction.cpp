#include "gameaction.h"

gameAction::gameAction(user * tmp1, user * tmp2, QObject *parent) :user1(tmp1), user2(tmp2), QObject(parent)
{
    user1->tcp->write(QByteArray("040" + user2->id));
    user2->tcp->write(QByteArray("041" + user1->id));
}
