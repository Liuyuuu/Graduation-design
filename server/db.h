#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>


class db : public QObject
{
    Q_OBJECT
public:
    explicit db(QObject *parent = nullptr);
    QSqlDatabase * myDb;
    bool sel(int user, QString passwd);
    bool ins(int user, QString passwd);

signals:

};

#endif // DB_H
