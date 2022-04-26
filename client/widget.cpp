#include "widget.h"


widget::widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(860, 680);

    myMenuBar* d = new myMenuBar(this);



}


myMenuBar::myMenuBar(QWidget *parent) : QWidget(parent)
{
    const int qMenuBarHeight = 30;
    const int qStatusBarHeight = 30;

    // 设置菜单栏
    mebr = new QMenuBar(this);
    mebr->setFixedSize(parent->width(), qMenuBarHeight);

    m1 = mebr->addMenu("游戏模式");
    m1_1 = m1->addMenu("互联网模式");
    m1_1_act1 = new QAction("连接服务器");
    m1_1->addAction(m1_1_act1);

    m1_2 = m1->addMenu("局域网模式");
    m1_2_act1 = new QAction("连接服务器");
    m1_2_act2 = new QAction("运行服务器");
    m1_2->addAction(m1_2_act1);
    m1_2->addAction(m1_2_act2);

    m1_3 = new QAction("人机对战");
    m1->addAction(m1_3);


    //设置状态栏
    stbr = new QStatusBar(this);
    stbr->setSizeGripEnabled(false);
    stbr->setStyleSheet("background-color: rgb(225, 225, 225);");
    stbr->setGeometry(0,parent->height() - qStatusBarHeight, parent->width(), qStatusBarHeight);

    lab1 = new QLabel("",stbr);
    widt = new QWidget(stbr);
    widt->setWindowFlag(Qt::FramelessWindowHint);
    widt->setFixedSize(stbr->height(),stbr->height()-5);
    setNetworkNotConncet();

    stbr->addWidget(lab1);
    stbr->addWidget(widt);
}

void myMenuBar::setNetworkConnect()
{
    lab1->setText("服务器连接状态：已连接");
    widt->setStyleSheet("background-color: rgb(225, 0, 0);");

}

void myMenuBar::setNetworkNotConncet()
{
    lab1->setText("服务器连接状态：未连接");
    widt->setStyleSheet("background-color: rgb(0, 255, 0);");

}
