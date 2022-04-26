#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QLabel>

class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);

signals:

private:

};

class myMenuBar: public QWidget
{
    Q_OBJECT
public:
    explicit myMenuBar(QWidget *parent = nullptr);
    void setNetworkConnect();
    void setNetworkNotConncet();

private:
    QMenuBar *mebr;
    QMenu * m1;
    QMenu * m1_1;
    QMenu * m1_2;
    QAction * m1_3;
    QAction * m1_1_act1;
    QAction * m1_2_act1;
    QAction * m1_2_act2;

    QStatusBar * stbr;
    QLabel *lab1;
    QWidget *widt;

};

#endif // WIDGET_H
