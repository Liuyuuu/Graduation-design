#include "widget.h"


widget::widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(860, 680);

    statusAndMenuBar* d = new statusAndMenuBar(this);

}


