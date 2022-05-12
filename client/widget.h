#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "network.h"
#include "statusandmenubar.h"
#include "login.h"
#include "board.h"

class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);
    void connectedSlots();
    void GameAction();

    int userIdMe;
    int userIdRival;

    void instruct02(QString);
    void instruct03(QString);

signals:


public:
    statusAndMenuBar* stme;
    network* tcp;
    login * lgn;
    board * boardChess;

private:
};

#endif // WIDGET_H
