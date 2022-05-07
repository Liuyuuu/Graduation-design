#include "widget.h"


widget::widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(860, 680);
    //setFixedSize(1400, 980);
    tcp = new network(this);
    stme = new statusAndMenuBar(this);
    lgn = new login(this);

    connectedSlots();

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

}


