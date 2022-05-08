#include "db.h"

#include <QSqlQuery>


db::db(QObject *parent) : QObject(parent)
{
    myDb = new QSqlDatabase;
    *myDb = QSqlDatabase::addDatabase("QMYSQL");

    if(myDb->isValid())
    {
        myDb->setHostName("127.0.0.1"); // 本地连接
        myDb->setPort(3306);       // 如果使用的是默认端口可以不设置
        myDb->setUserName("liuyu");	// 数据库用户名
        myDb->setPassword("123456"); // 数据库密码
        myDb->setDatabaseName("chess"); // 数据库名字
        if(myDb->open())
        {
            qDebug() << "数据库打开成功, 可以读写数据了......";
            qDebug() <<  ins(100234, "QGSQQk21RwhogqmM");

        }
        else
        {
            qDebug() << "数据库打开失败";
        }
    }
    else
    {
        qDebug() << "数据库连接错误！！！！";
    }
}

bool db::sel(int user, QString passwd)
{
    QSqlQuery query;
    QString str = "select * from user where id = " + QString::number(user).toUpper();
    query.exec(str);
    if(query.next())
    {
        // 从当前记录中取出各个字段的值
        qDebug() << query.value(1).toString();
        if(query.value(1).toString() == passwd)return true;
    }
    return false;
}

bool db::ins(int user, QString passwd)
{
    QSqlQuery query;
    QString str = "select * from user where id = " + QString::number(user).toUpper();
    query.exec(str);
    if(query.next())
    {
        return false;
    }
    else
    {
        str = "insert into user (id,passwd) value (" + QString::number(user).toUpper() +",'" + passwd + "')";
        qDebug() << str;
        query.exec(str);
        return true;
    }
}
