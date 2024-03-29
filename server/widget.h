#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QTcpServer>
#include <QPushButton>

#include "db.h"
#include "server.h"

#include "db.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    server *a;

private slots:
    void on_setlisten_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
