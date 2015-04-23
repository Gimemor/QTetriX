#include "scorewidget.h"

scoreWidget::scoreWidget(QWidget *parent):QLabel(parent),score(0)
{
    resize(100,100);
    clearS();
    setText(QString::fromUtf8("Счет:\n")+QString::number(score)+QString::fromUtf8(" очков\n")+str);
}
void scoreWidget::clearS()
{
    str="";
}
void scoreWidget::scoreUp(int x)
{ score+=x; setText(QString::fromUtf8("Счет:\n")+QString::number(score)+QString::fromUtf8(" очков\n")+str); }
void scoreWidget::resetScore()
{
    score=0; clearS();
    setText(QString::fromUtf8("Счет:\n")+QString::number(score)+QString::fromUtf8(" очков\n"));
}

void scoreWidget::getText(QString s)
{
    clearS();
    str=s;
    setText(QString::fromUtf8("Счет:\n")+QString::number(score)+QString::fromUtf8(" очков\n")+str);
}
void scoreWidget::gameOver(mode x)
{
    if(x==default_size)
        emit sendScore(score);
}
