#include "login.h"

#define ZHUCE "01"
#define DENGLU "00"


login::login(QWidget *parent) : QWidget(parent)
{

    init(); /*** 初始化窗口 ***/

    mySlots();

}

// 槽函数
void login::mySlots()
{
    connect(psb1, &QPushButton::clicked, this, &login::transform);
    connect(psb2, &QPushButton::clicked, this, &login::checkIDPasswd);
}

// 初始化界面
void login::init()
{
    this->setGeometry(0, 30, 860, 680);

    wgt1 = new QWidget(this);

    lab1 = new QLabel(wgt1);
    lab2 = new QLabel(wgt1);
    lab3 = new QLabel(wgt1);
    lab4 = new QLabel(wgt1);

    lied1 = new QLineEdit(wgt1);
    lied2 = new QLineEdit(wgt1);
    lied3 = new QLineEdit(wgt1);

    psb1 = new QPushButton(wgt1); /*** 左按钮 ***/
    psb2 = new QPushButton(wgt1); /*** 右按钮 ***/

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
    lab4->move(200, 380);


    lied1->setFont(ft3);
    lied1->setGeometry(330,260, 280, 36);
    lied2->setFont(ft3);
    lied2->setEchoMode(QLineEdit::Password);
    lied2->setGeometry(330,320, 280, 36);
    lied3->setFont(ft3);
    lied3->setEchoMode(QLineEdit::Password);
    lied3->setGeometry(330,380, 280, 36);


    psb1->setText("注 册");
    psb1->setFont(ft3);
    psb1->setGeometry(240, 480, 140, 60);
    psb2->setText("登 录");
    psb2->setFont(ft3);
    psb2->setGeometry(470, 480, 140, 60);

    psbOff();

    //lab4->setText("验证码");
    //lied3->setGeometry(330,380, 140, 36);
    lab4->hide();
    lied3->hide();
}


// 切换登录与注册界面
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
        lied3->setEchoMode(QLineEdit::Password);
        lied1->setText("");
        lied2->setText("");
        lied3->setText("");
    }else
    {
        lab1->setText("中国象棋");
        psb1->setText("注 册");
        psb2->setText("登 录");
        //lab4->setText("验证码");
        lab4->hide();
        lied3->hide();
//        lied3->setGeometry(330,380, 160, 36);
//        lied3->setEchoMode(QLineEdit::Normal);
        lied1->setText("");
        lied2->setText("");
        lied3->setText("");
    }
}


// 按钮状态切换
void login::psbOff()
{
    psb1->setEnabled(false);
    psb2->setEnabled(false);
}
<<<<<<< HEAD
=======

bool login::isId(QString str)
{
    return str.contains(QRegExp("^\\d{6}$"));
}

bool login::isPasswd(QString str)
{
    return str.contains(QRegExp("^[a-zA-Z0-9_-]{6,16}$"));
}

void login::instruct00()
{
    QMessageBox::information(NULL, "错误", "登录错误");
}
void login::instruct01()
{
    QMessageBox::information(NULL, "错误", "注册错误");
}

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
void login::psbOn()
{
    psb1->setDisabled(false);
    psb2->setDisabled(false);
}


// 判断的正则表达式
bool login::isId(QString str)
{
    return str.contains(QRegExp("^\\d{6}$"));
}
bool login::isPasswd(QString str)
{
    return str.contains(QRegExp("^[a-zA-Z0-9_-]{6,16}$"));
}


// 账号密码检查函数
void login::checkIDPasswd()
{
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
}


// 弹窗提示密码错误
void login::respond00()
{
    QMessageBox::information(NULL, "错误", "密码错误");
}
void login::respond01()
{
    QMessageBox::information(NULL, "错误", "注册失败");
}





