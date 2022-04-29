#include "board.h"


board::board(QWidget *parent, bool mainRed) : QWidget(parent), myRed(mainRed)
{
    this->setGeometry(0, 30, 1400, 920);
    _id = 0;
    d = 82;
    r = d/2;

    saveFirstPoint = QPoint(0,0);
    saveSecondPoint = QPoint(0,0);

    for(int i = 1; i <= 32; i++)
    {
        s[i].init(i, myRed);
        qDebug() << s[i].getText() << center(i) << s[i].red;
    }
}

void board::paintEvent(QPaintEvent *)
{

    QPainter * painter = new QPainter(this);
    QPen pen;
    pen.setWidth(3);    //设置画笔粗细
    painter->setPen(pen);

    //画10条横线
    for (int i = 1; i <= 10; i++)
        painter->drawLine(QPoint(d, d*i), QPoint(d*9, d*i));//9条竖线
    //画两边界竖线
    painter->drawLine(QPoint(d, d), QPoint(d, d*10));
    painter->drawLine(QPoint(d*9, d), QPoint(d*9, d*10));
    //画中间7条竖线
    for (int i = 2; i < 9; i++) {
        painter->drawLine(QPoint(d*i, d), QPoint(d*i, d*5));
        painter->drawLine(QPoint(d*i, d*6), QPoint(d*i, d*10));
    }
    //画九宫斜线
    painter->drawLine(QPoint(d*4, d), QPoint(d*6, d*3));
    painter->drawLine(QPoint(d*4, d*3), QPoint(d*6, d));
    painter->drawLine(QPoint(d*4, d*8), QPoint(d*6, d*10));
    painter->drawLine(QPoint(d*4, d*10), QPoint(d*6, d*8));


    // 绘制棋子
    QPoint p;
    for(int i = 1; i <= 32; i++)
    {
        if(!s[i].dead)
        {

            p = center(s[i].id);
            if (s[i].red)
            {
                if(i == _id)
                {
                    painter->setBrush(QBrush(QColor(255,0,0)));
                    painter->setFont(QFont("宋体", r * 0.9, 3));
                    painter->drawEllipse(p, r, r);
                    painter->drawText(QRect(p.x() - r, p.y() - r, d, d), s[i].getText(), QTextOption(Qt::AlignCenter));
                }
                else
                {
                    painter->setBrush(QBrush("#F10C45"));
                    painter->setFont(QFont("宋体", r * 0.7, 3));
                    painter->drawEllipse(p, r, r);
                    painter->drawText(QRect(p.x() - r, p.y() - r, d, d), s[i].getText(), QTextOption(Qt::AlignCenter));
                }
            }
            else
            {
                if(i == _id)
                {
                    painter->setBrush(QBrush(QColor(205,205,205)));
                    painter->setFont(QFont("宋体", r * 0.9, 3));
                    painter->drawEllipse(center(s[i].id), r, r);
                    painter->drawText(QRect(p.x() - r, p.y() - r, d, d), s[i].getText(), QTextOption(Qt::AlignCenter));
                }
                else
                {
                    painter->setBrush(QBrush(QColor(255,255,255)));
                    painter->setFont(QFont("宋体", r * 0.7, 3));
                    painter->drawEllipse(center(s[i].id), r, r);
                    painter->drawText(QRect(p.x() - r, p.y() - r, d, d), s[i].getText(), QTextOption(Qt::AlignCenter));
                }
            }
        }
    }

    painter->end();
}



void board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();
    moveChess(pt);

}

void board::moveChess(QPoint pt)
{
    int row = 0;
    int col = 0;
    bool bRet = false;

    saveFirstPoint = saveSecondPoint;

    bRet = getRowCol(pt, row, col);
    updateId(row, col);
    if(bRet)
    {
        if(_id)
        {
            saveSecondPoint = QPoint(s[_id].row, s[_id].col);
        }
        else
        {
            saveSecondPoint = center(row, col);
        }
    }
    else
    {
        saveSecondPoint = QPoint(0,0);
    }

    int temp = pointToId(saveFirstPoint);
    int temp2 = pointToId(saveSecondPoint);
    if(temp && s[temp].red == myRed)
    {
        if(temp2 == 0)
        {
            s[temp].row = saveSecondPoint.x();
            s[temp].col = saveSecondPoint.y();
            qDebug() << "移动";
        }else if(temp2 != temp && s[temp2].red != myRed)
        {
            s[temp2].dead = true;
            s[temp].row = saveSecondPoint.x();
            s[temp].col = saveSecondPoint.y();
            qDebug() << "吃棋";
        }


    }



    update();
}

bool board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row = 1; row <= 10; row++)
    {
        for(col = 1; col <= 9; col++)
        {
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx * dx + dy * dy;
            if(dist < r * r)
                return true;
        }
    }
    return false;
}


void board::updateId(int row, int col)
{
    for(int i = 1; i <= 32; i++)
    {
        if(s[i].row == row && s[i].col == col && s[i].dead == false)
        {
            _id = i;
            break;
        }
        else
        {
            _id = 0;
        }
    }
}


int board::pointToId(QPoint p)
{
    int i = 1;
    for(; i <= 32; i++)
    {
        if(s[i].row == p.x() && s[i].col == p.y() && s[i].dead == false)
        {
            break;
        }
    }
    if(i > 32) return 0;
    else return i;
}


QPoint board::center(int row, int col)
{
    return QPoint(col * d, row * d);
}

QPoint board::center(int id)
{
    return center(s[id].row, s[id].col);
}



