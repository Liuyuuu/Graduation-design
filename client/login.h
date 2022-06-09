#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>


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
    void respond00();
    void respond01();
    void mySlots();
    void checkIDPasswd();

<<<<<<< HEAD
=======
    void instruct00();
    void instruct01();


signals:
    void loginSend(QByteArray str);
public:
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
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


signals:
    void loginSend(QByteArray str);


};



#endif // LOGIN_H
