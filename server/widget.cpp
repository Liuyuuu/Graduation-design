#include "widget.h"
#include "ui_widget.h"






Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    a = new server(this);



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_setlisten_clicked()
{
    a->openLisnt();
}
