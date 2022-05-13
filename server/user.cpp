#include "user.h"

user::user(QTcpSocket * tmp, int tmp1, QObject *parent) : tcp(tmp), id(tmp1), QObject(parent)
{
}
