#include "widget.h"
#include "ui_widget.h"

<<<<<<< HEAD

=======
#include <QSqlDatabase>
#include <QDebug>
#include <QTcpServer>
#include <QPushButton>
>>>>>>> da6ad27a8e86736717b61087ca6698836ff847d9




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
