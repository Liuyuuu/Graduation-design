#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QTcpServer>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //db db;
    //db.sel(1231,"sadfsadf");

    server a(this);






}

Widget::~Widget()
{
    delete ui;
}

