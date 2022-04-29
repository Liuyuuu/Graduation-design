#include "login.h"

#define ZHUCE "zhuce"
#define DENGLU "denglu"

#include <QMessageBox>

login::login(QWidget *parent) : QWidget(parent)
{

    wgt1 = new QWidget(this);

    lab1 = new QLabel(wgt1);
    lab2 = new QLabel(wgt1);
    lab3 = new QLabel(wgt1);
    lab4 = new QLabel(wgt1);

    lied1 = new QLineEdit(wgt1);
    lied2 = new QLineEdit(wgt1);
    lied3 = new QLineEdit(wgt1);

    psb1 = new QPushButton(wgt1);
    psb2 = new QPushButton(wgt1);

    init();
    psbOff();

    connect(psb1, &QPushButton::clicked, this, &login::transform);

}

void login::init()
{
    this->setGeometry(0, 30, 860, 680);

    QFont ft1("宋体", 32);
    QFont ft2("宋体", 18);
    QFont ft3("宋体", 12);

    lab1->setText("中国象棋");
    lab1->setFont(ft1);
    lab1->move(305, 120);
    lab2->setText("账号");
    lab2->setFont(ft2);
    lab2->move(240, 260);
    lab3->setText("密码");
    lab3->setFont(ft2);
    lab3->move(240, 320);
    lab4->setText("确认密码");
    lab4->setFont(ft2);
    lab4->move(180, 380);
    lab4->hide();

    lied1->setFont(ft3);
    lied1->setGeometry(330,260, 280, 36);
    lied2->setFont(ft3);
    lied2->setEchoMode(QLineEdit::Password);
    lied2->setGeometry(330,320, 280, 36);
    lied3->setFont(ft3);
    lied3->setEchoMode(QLineEdit::Password);
    lied3->setGeometry(330,380, 280, 36);
    lied3->hide();

    psb1->setText("注 册");
    psb1->setFont(ft3);
    psb1->setGeometry(240, 480, 140, 60);
    psb2->setText("登 录");
    psb2->setFont(ft3);
    psb2->setGeometry(470, 480, 140, 60);

    connect(psb2, &QPushButton::clicked, this, [=](){
        if(psb1->text() == "返 回")
        {
            if(!isId(lied1->text()))
            {
                QMessageBox::information(NULL, "错误", "账号为6位纯数字！");
            }
            else if(!isPasswd(lied2->text()))
            {
                QMessageBox::information(NULL, "错误", "密码为大小写、数字的组合，长度为6-16位！");
            }else if(lied2->text() != lied3->text())
            {
                QMessageBox::information(NULL, "错误", "密码不一致");
            }else
            {
                emit loginSend(ZHUCE + lied1->text().toUtf8() + lied2->text().toUtf8());
            }

        }else
        {
            if(!isId(lied1->text()))
            {
                QMessageBox::information(NULL, "错误", "账号为6位纯数字！");
            }
            else if(!isPasswd(lied2->text()))
            {
                QMessageBox::information(NULL, "错误", "密码为大小写、数字的组合，长度为6-16位！");
            }else
            {
                emit loginSend(DENGLU + lied1->text().toUtf8() + lied2->text().toUtf8());
            }
        }

        qDebug() << isPasswd(lied2->text());


    });
}

void login::transform()
{
    if(psb1->text() == "注 册")
    {
        lab1->setText("在线注册");
        psb1->setText("返 回");
        psb2->setText("提 交");
        lab4->show();
        lied3->show();
        QMessageBox::information(NULL, "注册说明", "账号为6位纯数字\n密码为大小写、数字的组合，长度为6-16位！");
    }else
    {
        lab1->setText("中国象棋");
        psb1->setText("注 册");
        psb2->setText("登 录");
        lab4->hide();
        lied3->hide();
    }
}

void login::psbOff()
{
    psb1->setEnabled(false);
    psb2->setEnabled(false);
}

bool login::isId(QString str)
{
    return str.contains(QRegExp("^\\d{6}$"));
}

bool login::isPasswd(QString str)
{
    return str.contains(QRegExp("^[a-zA-Z0-9_-]{6,16}$"));
}

void login::psbOn()
{
    psb1->setDisabled(false);
    psb2->setDisabled(false);
}
