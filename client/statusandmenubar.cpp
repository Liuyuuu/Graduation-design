#include "statusandmenubar.h"

statusAndMenuBar::statusAndMenuBar(QWidget *parent) : QWidget(parent)
{
    const int qMenuBarHeight = 30;
    const int qStatusBarHeight = 30;

    // 设置菜单栏
    mebr = new QMenuBar(this);
    mebr->setFixedSize(parent->width(), qMenuBarHeight);

    m1 = new QMenu("游戏模式", mebr);

    m1_1 = new QMenu("互联网模式", mebr);
    m1_2 = new QMenu("局域网模式", mebr);
    m1_3 = new QAction("人机对战", mebr);

    m1_1_act1 = new QAction("连接服务器",mebr);
    m1_1->addAction(m1_1_act1);

    m1_2_act1 = new QAction("连接服务器",mebr);
    m1_2_act2 = new QAction("运行服务器",mebr);
    m1_2->addAction(m1_2_act1);
    m1_2->addAction(m1_2_act2);

    m1->addMenu(m1_1);
    m1->addMenu(m1_2);
    m1->addAction(m1_3);

    m2 = new QMenu("游戏设置", mebr);
    m2_act1 = new QAction("开始匹配",mebr);
    m2_act2 = new QAction("停止匹配",mebr);
    m2_act3 = new QAction("认输",mebr);
    m2_act4 = new QAction("悔棋",mebr);

    m2->addAction(m2_act1);
    m2->addAction(m2_act2);
    m2->addAction(m2_act3);
    m2->addAction(m2_act4);

    m3 = new QMenu("游戏信息", mebr);
    m3_act1 = new QAction("游戏信息",mebr);
    m3->addAction(m3_act1);

    mebr->addMenu(m1);
    mebr->addMenu(m2);
    mebr->addMenu(m3);



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

void statusAndMenuBar::setNetworkConnect()
{
    lab1->setText("服务器连接状态：已连接");
    widt->setStyleSheet("background-color: #20C073;");
    m1_1_act1->setEnabled(false);

}

void statusAndMenuBar::setNetworkNotConncet()
{
    lab1->setText("服务器连接状态：未连接");
    widt->setStyleSheet("background-color: #F10C45;");
    m1_1_act1->setDisabled(false);

}
