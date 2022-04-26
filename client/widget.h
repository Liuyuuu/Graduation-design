#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "statusandmenubar.h"

class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);

signals:

private:

};

#endif // WIDGET_H
