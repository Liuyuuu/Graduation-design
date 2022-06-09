#include "statusandmenubar.h"

statusAndMenuBar::statusAndMenuBar(QWidget *parent) : QWidget(parent)
{

    // 设置菜单栏
    mebr = new QMenuBar(this);
    mebr->setFixedSize(parent->width(), 30);

    m1 = new QMenu("游戏模式", this);
    m1_1_act1 = new QAction("连接服务器",this);
    m1_2_act1 = new QAction("断开服务器",this);
    m1->addAction(m1_1_act1);
    m1->addAction(m1_2_act1);

    m2 = new QMenu("游戏设置", this);
    m2_act1 = new QAction("开始匹配",this);
    m2_act2 = new QAction("停止匹配",this);
    m2_act3 = new QAction("认输",this);
    m2_act4 = new QAction("悔棋",this);

    m2->addAction(m2_act1);
    m2->addAction(m2_act2);
    m2->addAction(m2_act3);
    m2->addAction(m2_act4);

    m3 = new QMenu("游戏信息", this);
    m3_act1 = new QAction("游戏信息",this);
    m3->addAction(m3_act1);

    mebr->addMenu(m1);
    mebr->addMenu(m2);
    mebr->addMenu(m3);



    //设置状态栏
    stbr = new QStatusBar(this);
    stbr->setSizeGripEnabled(false);
    stbr->setStyleSheet("background-color: rgb(225, 225, 225);");
    stbr->setGeometry(0,650, 860, 30);

    lab1 = new QLabel("",stbr);
    widt = new QWidget(stbr);
    widt->setWindowFlag(Qt::FramelessWindowHint);
    widt->setFixedSize(stbr->height(),stbr->height()-5);
    setNetworkNotConncet();

    stbr->addWidget(lab1);
    stbr->addWidget(widt);

<<<<<<< HEAD
    m2_act1->setEnabled(false);
    m2_act2->setEnabled(false);
    m2_act3->setEnabled(false);
    m2_act4->setEnabled(false);
=======
    //setM2(1,false);
    setM2(2,false);
    setM2(3,false);
    setM2(4,false);

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
}

//设置状态栏 联网
void statusAndMenuBar::setNetworkConnect()
{
    lab1->setText("服务器连接状态：已连接");
    widt->setStyleSheet("background-color: #20C073;");
    m1_1_act1->setEnabled(false);
}

//设置状态栏 断开网络连接
void statusAndMenuBar::setNetworkNotConncet()
{
    lab1->setText("服务器连接状态：未连接");
    widt->setStyleSheet("background-color: #F10C45;");
    m1_1_act1->setDisabled(false);

}

void statusAndMenuBar::setM2(int num, bool b)
{

    switch (num) {
        case 4:if(b) m2_act4->setDisabled(false); else m2_act4->setEnabled(false);break;
        case 3:if(b) m2_act3->setDisabled(false); else m2_act3->setEnabled(false);break;
        case 2:if(b) m2_act2->setDisabled(false); else m2_act2->setEnabled(false);break;
        case 1:if(b) m2_act1->setDisabled(false); else m2_act1->setEnabled(false);break;
    }

}


