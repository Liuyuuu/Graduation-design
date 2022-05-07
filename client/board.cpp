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

    bRet = getRowCol(pt, row, col); // 返回point
    updateId(row, col);
    if(bRet)
    {
        if(_id)
        {
            saveSecondPoint = QPoint(s[_id].row, s[_id].col);
        }
        else
        {
            saveSecondPoint = QPoint(row, col);
        }
    }
    else
    {
        saveSecondPoint = QPoint(0,0);
    }

    int temp = pointToId(saveFirstPoint);
    int temp2 = pointToId(saveSecondPoint);
    if(temp && s[temp].red == myRed && temp != -1)
    {
        if(temp2 == 0)
        {
            if(rule(temp))
            {
                s[temp].row = saveSecondPoint.x();
                s[temp].col = saveSecondPoint.y();
                saveSecondPoint = QPoint(0,0);
                qDebug() << "移动" << temp << temp2;
            }

        }else if(temp2 != temp && s[temp2].red != myRed && temp2 != -1)
        {
            if(rule(temp))
            {
                s[temp2].dead = true;
                s[temp].row = saveSecondPoint.x();
                s[temp].col = saveSecondPoint.y();
                saveSecondPoint = QPoint(0,0);
                qDebug() << "吃棋" << temp << temp2;
            }
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
    if(p == QPoint(0,0)) return -1;
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

bool board::rule(int FirstPointId)
{
    switch(s[FirstPointId].type)
    {
    case Stone::KING: return king();
    case Stone::CHE:return che();
    case Stone::MA:return ma();
    case Stone::PAO:return pao();
    case Stone::XIANG:return xiang();
    case Stone::SHI:return shi();
    case Stone::BING:return bing();
    default:
        return false;
    }
}

bool board::king()
{
    int num = 1;
    if(! ((saveSecondPoint.x() == saveFirstPoint.x()+num && saveSecondPoint.y() == saveFirstPoint.y()) ||
       (saveSecondPoint.x() == saveFirstPoint.x()-num && saveSecondPoint.y() == saveFirstPoint.y()) ||
       (saveSecondPoint.y() == saveFirstPoint.y()+num && saveSecondPoint.x() == saveFirstPoint.x()) ||
       (saveSecondPoint.y() == saveFirstPoint.y()-num && saveSecondPoint.x() == saveFirstPoint.x())
      ))
    {
        qDebug() << "不在四周！(" << saveFirstPoint.x() << saveFirstPoint.y() << ")(" << saveSecondPoint.x() << saveSecondPoint.y() << ")";
        return false;
    }

    if((saveSecondPoint.x() < 8 || saveSecondPoint.x() > 10) || (saveSecondPoint.y() < 4 || saveSecondPoint.y() > 6))
    {
        qDebug() << "不在圈内！";
        qDebug() << saveSecondPoint.x() << saveSecondPoint.y();
        return false;
    }
    return true;
}

bool board::che()
{
    if(saveSecondPoint.x() != saveFirstPoint.x() && saveSecondPoint.y() == saveFirstPoint.y())
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if((saveSecondPoint.x() - saveFirstPoint.x()) < 0)
            {

                if(s[i].col == saveFirstPoint.y() && s[i].row < saveFirstPoint.x() && s[i].row > saveSecondPoint.x())
                {
                    qDebug() << "上下的中间有棋1";
                    break;
                }
            }else
            {
                if(s[i].col == saveFirstPoint.y() && s[i].row > saveFirstPoint.x() && s[i].row < saveSecondPoint.x())
                {
                    qDebug() << "上下的中间有棋1";
                    break;
                }
            }
        }
        if(i > 32) return true;
        else return false;

    }
    else if(saveSecondPoint.x() == saveFirstPoint.x() && saveSecondPoint.y() != saveFirstPoint.y())
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if((saveSecondPoint.y() - saveFirstPoint.y()) < 0)
            {
                qDebug() << "saveSecondPoint.y() = " << saveSecondPoint.y() << "s[i].col = " << s[i].col << "saveFirstPoint.y()=" << saveFirstPoint.y();
                if(s[i].row == saveFirstPoint.x() && s[i].col < saveFirstPoint.y() && s[i].col > saveSecondPoint.y())
                {
                    qDebug() << "左右中间有棋1";
                    break;
                }

            }else
            {
                qDebug()<< "saveFirstPoint.y()=" << saveFirstPoint.y()<< "s[i].col = " << s[i].col  << "saveSecondPoint.y() = " << saveSecondPoint.y() ;
                if(s[i].row == saveFirstPoint.x() && s[i].col > saveFirstPoint.y() && s[i].col < saveSecondPoint.y())
                {
                    qDebug() << "左右中间有棋2";
                    break;
                }
            }
        }
        if(i > 32) return true;
        else return false;

    }else
    {
        return false;
    }
}

bool board::ma()
{
    int tepm1 = saveSecondPoint.x() - saveFirstPoint.x();
    int tepm2 = saveSecondPoint.y() - saveFirstPoint.y();

    if((tepm1 == -2 && tepm2 == -1) || (tepm1 == -2 && tepm2 == 1))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() - 1 && s[i].col == saveFirstPoint.y())
            {
                qDebug() << "上";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }

    if((tepm1 == -1 && tepm2 == 2) || (tepm1 == 1 && tepm2 == 2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y() + 1)
            {
                qDebug() << "右";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }
    if((tepm1 == 2 && tepm2 == -1) || (tepm1 == 2 && tepm2 == 1))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() + 1 && s[i].col == saveFirstPoint.y())
            {
                qDebug() << "下";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }
    if((tepm1 == -1 && tepm2 == -2) || (tepm1 == 1 && tepm2 == -2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y() - 1)
            {
                qDebug() << "左";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }

    return false;
}

bool board::xiang()
{
    if(saveSecondPoint.x() < 6) return false;

    int tepm1 = saveSecondPoint.x() - saveFirstPoint.x();
    int tepm2 = saveSecondPoint.y() - saveFirstPoint.y();

    if((tepm1 == -2 && tepm2 == -2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() - 1 && s[i].col == saveFirstPoint.y() - 1)
            {
                qDebug() << "左上";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }
    if((tepm1 == -2 && tepm2 == 2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() - 1 && s[i].col == saveFirstPoint.y() + 1)
            {
                qDebug() << "右上";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }
    if((tepm1 == 2 && tepm2 == -2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() + 1 && s[i].col == saveFirstPoint.y() - 1)
            {
                qDebug() << "左下";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }
    if((tepm1 == 2 && tepm2 == 2))
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if(s[i].row == saveFirstPoint.x() + 1 && s[i].col == saveFirstPoint.y() + 1)
            {
                qDebug() << "右下";
                break;
            }
        }
        if(i > 32) return true;
        else return false;
    }

    return false;
}

bool board::shi()
{
    if((saveSecondPoint.x() < 8 || saveSecondPoint.x() > 10) || (saveSecondPoint.y() < 4 || saveSecondPoint.y() > 6))
    {
        return false;
    }

    int tepm1 = saveSecondPoint.x() - saveFirstPoint.x();
    int tepm2 = saveSecondPoint.y() - saveFirstPoint.y();

    if(tepm1 == -1 && tepm2 == -1)return true;

    if(tepm1 == -1 && tepm2 == 1)return true;

    if(tepm1 == 1 && tepm2 == -1)return true;

    if(tepm1 == 1 && tepm2 == 1)return true;

    return false;

}

bool board::pao()
{
    int num = 0;
    if(saveSecondPoint.x() != saveFirstPoint.x() && saveSecondPoint.y() == saveFirstPoint.y())
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if((saveSecondPoint.x() - saveFirstPoint.x()) < 0)
            {

                if(s[i].col == saveFirstPoint.y() && s[i].row < saveFirstPoint.x() && s[i].row > saveSecondPoint.x())
                {
                    qDebug() << "num++";
                    num++;
                }
            }else
            {
                if(s[i].col == saveFirstPoint.y() && s[i].row > saveFirstPoint.x() && s[i].row < saveSecondPoint.x())
                {
                    qDebug() << "num++";
                    num++;
                }
            }
        }
        qDebug() << "num = " << num;
        if(num >= 2) return false;
        if(num == 1)
        {
            for(int j = 1; j <= 32; j++)
            {
                if(s[j].dead == true || (s[j].row == saveFirstPoint.x() && s[j].col == saveFirstPoint.y()))
                {
                    continue;
                }
                if(s[j].row == saveSecondPoint.x() && s[j].col == saveSecondPoint.y()) return true;
            }
        }
        if(num == 0)
        {
            int j = 1;
            for(; j <= 32; j++)
            {
                if(s[j].dead == true || (s[j].row == saveFirstPoint.x() && s[j].col == saveFirstPoint.y()))
                {
                    continue;
                }
                if(s[j].row == saveSecondPoint.x() && s[j].col == saveSecondPoint.y()) break;
            }
            if(j > 32) return true;
            else return false;
        }

    }
    else if(saveSecondPoint.x() == saveFirstPoint.x() && saveSecondPoint.y() != saveFirstPoint.y())
    {
        int i = 1;
        for(; i <= 32; i++)
        {
            if(s[i].dead == true || (s[i].row == saveFirstPoint.x() && s[i].col == saveFirstPoint.y()))
            {
                continue;
            }
            if((saveSecondPoint.y() - saveFirstPoint.y()) < 0)
            {
                if(s[i].row == saveFirstPoint.x() && s[i].col < saveFirstPoint.y() && s[i].col > saveSecondPoint.y())
                {
                    num++;
                }

            }else
            {
                //qDebug()<< "saveFirstPoint.y()=" << saveFirstPoint.y()<< "s[i].col = " << s[i].col  << "saveSecondPoint.y() = " << saveSecondPoint.y() ;
                if(s[i].row == saveFirstPoint.x() && s[i].col > saveFirstPoint.y() && s[i].col < saveSecondPoint.y())
                {
                    num++;
                }
            }
        }
        qDebug() << "num = " << num;
        if(num >= 2) return false;
        if(num == 1)
        {
            for(int j = 1; j <= 32; j++)
            {
                if(s[j].dead == true || (s[j].row == saveFirstPoint.x() && s[j].col == saveFirstPoint.y()))
                {
                    continue;
                }
                if(s[j].row == saveSecondPoint.x() && s[j].col == saveSecondPoint.y()) return true;
            }
        }
        if(num == 0)
        {
            int j = 1;
            for(; j <= 32; j++)
            {
                if(s[j].dead == true || (s[j].row == saveFirstPoint.x() && s[j].col == saveFirstPoint.y()))
                {
                    continue;
                }
                if(s[j].row == saveSecondPoint.x() && s[j].col == saveSecondPoint.y()) break;
            }
            if(j > 32) return true;
            else return false;
        }


    }else
    {
        return false;
    }
}

bool board::bing()
{
    if(saveFirstPoint.x() < 6)
    {
        if(((saveSecondPoint.x() == saveFirstPoint.x() - 1) && (saveSecondPoint.y() == saveFirstPoint.y())) ||
           ((saveSecondPoint.x() == saveFirstPoint.x()) && (saveSecondPoint.y() == saveFirstPoint.y() - 1)) ||
           ((saveSecondPoint.x() == saveFirstPoint.x()) && (saveSecondPoint.y() == saveFirstPoint.y() + 1))
          ) return true;
        else return false;
    }
    else
    {
        if((saveSecondPoint.x() == saveFirstPoint.x() - 1) && (saveSecondPoint.y() == saveFirstPoint.y())) return true;
        else return false;
    }
}







