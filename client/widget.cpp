#include "widget.h"


widget::widget(QWidget *parent) : QWidget(parent)
{
    userIdMe = 0;
    userIdRival = 0;

    setFixedSize(860, 680);
    //setFixedSize(1400, 980);
    tcp = new network(this);
    stme = new statusAndMenuBar(this);
    lgn = new login(this);

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


}

void widget::connectedSlots()
{
    connect(tcp, &network::connected, stme, &statusAndMenuBar::setNetworkConnect);
    connect(tcp, &network::connected, lgn, &login::psbOn);
    connect(tcp, &network::disConnect, stme, &statusAndMenuBar::setNetworkNotConncet);
    connect(tcp, &network::disConnect, lgn, &login::psbOff);
    connect(lgn, &login::loginSend, tcp, &network::send);
    connect(stme->m1_1_act1, &QAction::triggered, tcp, &network::connectServer);

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


