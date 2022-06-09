#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

class chat : public QWidget
{
    Q_OBJECT
public:
    explicit chat(QWidget *parent = nullptr);
    void init();
    void addText(QString str);
    void myConnect();
    void offSend();
    void onSend();


    QTextEdit * text1;
    QTextEdit * text2;
    QLabel * lab1;
    QLabel * lab2;
    QLabel * lab3;
    QPushButton * psb1;


signals:
    void msg(QByteArray);

};

#endif // CHAT_H
