#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H
#include <QLabel>
#include <QWidget>
#include "enums.h"
class scoreWidget : public QLabel
{
    Q_OBJECT
private:
    QLabel *lbl;
    unsigned long long score;
    QString str;
public:
    scoreWidget(QWidget *parent=0);
public slots:
    void scoreUp(int);
    void resetScore();
    void getText(QString s);
    void clearS();
    void gameOver(mode x);
signals:
    void sendScore(unsigned long long b);
};

#endif // SCOREWIDGET_H
