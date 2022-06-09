#include "chat.h"


chat::chat(QWidget *parent) : QWidget(parent)
{
    init();
    myConnect();

}

// 初始化聊天窗口
void chat::init()
{
    this->setGeometry(840,80,520, 800);

    lab1 = new QLabel(this);
    lab1->setFont(QFont("宋体", 18));
    lab1->setText("对局未开始");

    lab2 = new QLabel(this);
    lab2->move(0, 70);
    lab2->setFont(QFont("宋体", 14));
    lab2->setText("聊天窗口");

    lab3 = new QLabel(this);
    lab3->move(0, 570);
    lab3->setFont(QFont("宋体", 14));
    lab3->setText("发送消息");

    text1 = new QTextEdit(this);
    text1->setGeometry(0,100,520, 400);
    text1->setFont(QFont("宋体", 14));

    text2 = new QTextEdit(this);
    text2->setGeometry(0,600,520, 100);
    text2->setFont(QFont("宋体", 14));

    psb1 = new QPushButton(this);
    psb1->setFont(QFont("宋体", 16));
    psb1->setGeometry(0,710,520, 80);
    psb1->setText("发   送");

    offSend();

}

void chat::myConnect()
{
    connect(psb1,&QPushButton::clicked,this,[=]{
        QString  str = text2->toPlainText();
        text2->setText("");
        emit msg(("12" + str).toUtf8());
    });
}

// 关机发送按钮
void chat::offSend()
{
    psb1->setEnabled(false);
}

void chat::onSend()
{
    psb1->setDisabled(false);
}

void chat::addText(QString str)
{
    text1->append(str);
}


