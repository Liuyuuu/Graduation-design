#include "stone.h"

Stone::Stone(QObject *parent) : QObject(parent)
{

}

// 获取棋子类型
QString Stone::getText()
{
    switch(this->type)
    {
    case KING:
        if (red)
            return "帅";
        else
            return "将";
    case CHE:
        return "车";
    case MA:
        return "马";
    case PAO:
        return "炮";
    case XIANG:
        if (red)
            return "相";
        else if (!red)
            return "象";
    case SHI:
        if (red)
            return "仕";
        else
            return "士";
    case BING:
        if (red)
            return "兵";
        else if (!red)
            return "卒";
    default:
        return "错误";
    }
}

// 初始化棋子
void Stone::init(int sid, bool mainRed)
{
    this->id = sid;
    dead = false;
    red = id <= 16;
    if(mainRed) red = !red;

    struct{
        int col;
        int row;
        Stone::TYPE type;
    }pos[17] = {{},
    {1, 1, Stone::CHE},
    {2, 1, Stone::MA},
    {3, 1, Stone::XIANG},
    {4, 1, Stone::SHI},
    {5, 1, Stone::KING},
    {6, 1, Stone::SHI},
    {7, 1, Stone::XIANG},
    {8, 1, Stone::MA},
    {9, 1, Stone::CHE},
    {2, 3, Stone::PAO},
    {8, 3, Stone::PAO},
    {1, 4, Stone::BING},
    {7, 4, Stone::BING},
    {5, 4, Stone::BING},
    {3, 4, Stone::BING},
    {9, 4, Stone::BING}};

    if(id <= 16) {
        this->row = pos[id].row;
        this->col = pos[id].col;
        this->type = pos[id].type;
    } else {
        this->row = 11-pos[id-16].row; //行对称：1+10=2+8……
        this->col = 10-pos[id-16].col; //列对称：1+9=2+7……
        this->type = pos[id-16].type;
    }

}
