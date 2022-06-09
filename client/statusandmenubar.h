#ifndef STATUSANDMENUBAR_H
#define STATUSANDMENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QLabel>

class statusAndMenuBar : public QWidget
{
    Q_OBJECT
public:
    explicit statusAndMenuBar(QWidget *parent = nullptr);
    void setNetworkConnect();
    void setNetworkNotConncet();

    QMenuBar *mebr;
    QMenu * m1;
    QMenu * m2;
    QMenu * m3;
    QMenu * m1_1;
    QMenu * m1_2;
    QAction * m1_3;
    QAction * m1_1_act1;
    QAction * m1_2_act1;
    QAction * m1_2_act2;
    QAction * m2_act1;
    QAction * m2_act2;
    QAction * m2_act3;
    QAction * m2_act4;
    QAction * m3_act1;
    QStatusBar * stbr;
    QLabel *lab1;
    QWidget *widt;

signals:




private:

};

#endif // STATUSANDMENUBAR_H
