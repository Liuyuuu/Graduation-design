#include "widget.h"



widget::widget(QWidget *parent) : QWidget(parent)
{
<<<<<<< HEAD
    rivalId = 0;
    id = 0;
=======
    userIdMe = 0;
    userIdRival = 0;

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
    setFixedSize(860, 680);


    tcp = new network(this);
    stme = new statusAndMenuBar(this);
    lgn = new login(this);

<<<<<<< HEAD
    //successfulLogin();
    myConnect();

=======
    connectedSlots();

    //GameAction();
    if(false)
    {
        lgn->close();
        setFixedSize(1400, 980);
        stme->mebr->setFixedSize(1400,30);
        stme->stbr->setGeometry(0,950, 1400, 30);
        boardChess = new board(this, true);
    }
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9


}

void widget::myConnect()
{
    // 与服务器连接成功初始化操作
    connect(tcp, &network::connected, stme, &statusAndMenuBar::setNetworkConnect);
    connect(tcp, &network::connected, lgn, &login::psbOn);

    // 与服务器断开连接操作
    connect(tcp, &network::disConnect, stme, &statusAndMenuBar::setNetworkNotConncet);
    connect(tcp, &network::disConnect, lgn, &login::psbOff);
    connect(tcp, &network::disConnect, this, &widget::startWindow);
    connect(tcp, &network::disConnect, tcp, &network::clearTcp);


    // 用户操作
    connect(lgn, &login::loginSend, tcp, &network::send); // 登录
    connect(stme->m1_1_act1, &QAction::triggered, tcp, &network::connectServer); //连接服务器
    connect(stme->m1_2_act1, &QAction::triggered, tcp, &network::disConnect); //断开连接
    connect(stme->m2_act1, &QAction::triggered, this, [=]{
        tcp->beginToMatch(id);
        stme->m2_act1->setEnabled(false);
        stme->m2_act2->setDisabled(false);
    });
    connect(stme->m2_act2, &QAction::triggered, this, [=]{
        tcp->beginToMatch(id);
        stme->m2_act1->setDisabled(false);
        stme->m2_act2->setEnabled(false);
    });



    // 通过tcp发送内部命令
    connect(tcp, &network::instruct00, lgn, &login::respond00);
    connect(tcp, &network::instruct01, lgn, &login::respond01);
    connect(tcp, &network::instruct02, this, &widget::respond02);
    connect(tcp, &network::instruct03, this, &widget::respond03);
    connect(tcp, &network::instruct06, this, &widget::respond06);
    connect(tcp, &network::instruct11, this, &widget::respond11);


    connect(tcp, &network::send00, lgn, &login::instruct00);
    connect(tcp, &network::send01, lgn, &login::instruct01);
    connect(tcp, &network::send02, this, &widget::instruct02);
    connect(tcp, &network::send03, this, &widget::instruct03);

}

void widget::instruct02(QString tmp)
{
    userIdMe = tmp.toInt();
    GameAction();

}
void widget::instruct03(QString tmp)
{
    userIdMe = tmp.toInt();
    GameAction();
}

void widget::GameAction()
{
    lgn->close();
    setFixedSize(1400, 980);
    stme->setFixedSize(1400, 980);
    stme->mebr->setFixedSize(1400,30);
    stme->stbr->setGeometry(0,950, 1400, 30);
    boardChess = new board(this, true);

}

// 登陆成功响应函数
void widget::respond02(int myid)
{
    QMessageBox::information(NULL, "成功", "登录成功");
    id = myid;
    successfulLogin();
}

// 注册成功响应函数
void widget::respond03(int myid)
{
    QMessageBox::information(NULL, "成功", "成功注册");
    id = myid;
    successfulLogin();
}

// 开始游戏响应函数
void widget::respond06(QString str)
{
    qDebug() << "respond06  " << str.mid(0,1) << "  " << str.mid(1);
    boardChess->drawingBoard(str.mid(0,1).toUInt());
    boardChess->tag = str.mid(0,1).toUInt();
    ct->lab1->setText("对手ID："+str.mid(1));
    ct->onSend();
}

// 发送棋子移动信息
void widget::send07(int id, int x, int y)
{
    QString str = "10";
    if(id < 10) str = str + "0" + QString::number(id, 10);
    else str += QString::number(id, 10);
    if(x < 10) str = str + "0" + QString::number(x, 10);
    else str += QString::number(x, 10);
    if(y < 10) str = str + "0" + QString::number(y, 10);
    else str += QString::number(y, 10);

    qDebug() << "发送到服务器的走棋消息" << str;
    tcp->send(str.toUtf8());

    boardChess->tag = !boardChess->tag;
}


// 接收对局结果
void widget::respond11()
{
    QMessageBox::information(NULL, "对局结果", "获胜");
    ct->offSend();
    ct->text1->setText("");
    ct->lab1->setText("对局未开始");

    for(int i = 1; i <= 32; i++)
    {
        boardChess->s[i].init(i, false);
    }
}

// 游戏结束，处理本地环境
void widget::gameOver()
{
    QMessageBox::information(NULL, "对局结果", "失败");
    ct->offSend();
    ct->text1->setText("");
    ct->lab1->setText("对局未开始");

    for(int i = 1; i <= 32; i++)
    {
        boardChess->s[i].init(i, false);
    }
    update();
}

// 登录成功
void widget::successfulLogin()
{
    this->lgn->hide();
    this->setFixedSize(1400, 980);
    this->stme->mebr->setFixedSize(1400,30);
    this->stme->stbr->setGeometry(0,950, 1400, 30);
    this->boardChess = new board(this, false);
    stme->m2_act1->setDisabled(false);
    ct = new chat(this);
    boardChess->show();
    stme->mebr->show();
    stme->stbr->show();
    ct->show();
    update();

    connect(tcp, &network::instruct06, this, [=]{
         ct->addText("游戏开始");
     });
    connect(boardChess,&board::EmitMoveChess, this, &widget::send07);
    connect(tcp, &network::instruct12, boardChess, &board::rivalMobile);
    connect(ct,&chat::msg,tcp,&network::send);
    connect(tcp, &network::instruct14, ct, &chat::addText);
    connect(boardChess,&board::gameOver, tcp, &network::send);
    connect(boardChess,&board::gameOver, this, &widget::gameOver);

}

// 断开连接时，恢窗口
void widget::startWindow()
{
    boardChess->close();
    ct->close();
    this->setFixedSize(860, 680);
    this->stme->mebr->setFixedSize(860,30);
    this->stme->stbr->setGeometry(0,650, 860, 30);
    stme->m2_act1->setEnabled(false);
    stme->m2_act2->setEnabled(false);
    stme->m2_act3->setEnabled(false);
    stme->m2_act4->setEnabled(false);

    lgn->show();
}



