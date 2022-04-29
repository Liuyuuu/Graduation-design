#ifndef STONE_H
#define STONE_H

#include <QObject>
#include <QDebug>

class Stone : public QObject
{
    Q_OBJECT
public:
    explicit Stone(QObject *parent = nullptr);


    enum TYPE{KING, CHE, MA, PAO, XIANG, SHI, BING};
    int row, col, id;
    bool dead, red;
    TYPE type;

    QString getText();
    void init(int id, bool mainRed = false);

signals:


};

#endif // STONE_H
