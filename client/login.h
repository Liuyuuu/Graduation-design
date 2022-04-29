#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = nullptr);
    void init();
    void transform();
    void psbOn();
    void psbOff();
    bool isId(QString str);
    bool isPasswd(QString str);


signals:
    void loginSend(QByteArray str);
public:
    QWidget * wgt1;

    QLabel * lab1;
    QLabel * lab2;
    QLabel * lab3;
    QLabel * lab4;

    QLineEdit * lied1;
    QLineEdit * lied2;
    QLineEdit * lied3;

    QPushButton * psb1;
    QPushButton * psb2;

};



#endif // LOGIN_H
