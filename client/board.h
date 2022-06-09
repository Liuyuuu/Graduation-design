#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QPen>
#include <QPaintEvent>
#include <QString>

#include "stone.h"

class board : public QWidget
{
    Q_OBJECT
public:

    explicit board(QWidget *parent = nullptr, bool mainRed = true);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    bool getRowCol(QPoint pt, int& row, int& col);
    void updateId(int row, int col);
    void moveChess(QPoint pt);
    int pointToId(QPoint p);
<<<<<<< HEAD
    void drawingBoard(bool tmp);
    void rivalMobile(QString str); /*** 对手移动 ***/
=======
    void setMainred(bool);

>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9
    bool rule(int FirstPointId);
    bool king();
    bool che();
    bool ma();
    bool xiang();
    bool shi();
    bool pao();
    bool bing();

    //返回像素坐标
    QPoint center(int row, int col);
    QPoint center(int id);


public:
    int d;
    int r;
    int _id;
    bool myRed;
    QPoint saveFirstPoint;
    QPoint saveSecondPoint;
    Stone s[33]; /*** 棋子数组 ***/
    bool tag; /*** 标记是否该自己走棋 ***/

signals:
    void EmitMoveChess(int, int, int);
    void gameOver(QByteArray);
};

#endif // BOARD_H
