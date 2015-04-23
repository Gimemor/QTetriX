#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QPalette>
#include <QSize>
#include <QTimer>
#include "mainwindow.h"
#include "figure.h"
#include "enums.h"
class figure;
class QTimer;
class gamefield : public QWidget
{
    Q_OBJECT
    friend class figure;
    protected:
        QSize size;
        char **state;
        bool isPauseNow; bool stopGame; bool ColorMode;
        figure *f;
        QTimer *t;
        int timerSpeed;
    public:
        gamefield(QWidget *parent=0);
        ~gamefield();
        void paintEvent(QPaintEvent *pe);
        void setState(int x,int y,char stateSet); //stateSet - true если клетка занята,
                                                  //            иначе false
        void setSize(int x,int y);
        void startGame();
        int getHSize() const;
        int getWSize() const;

        void setFigure();
        void createState(int x,int y);
        void check();
        void lineIsFull(int x);
        void gameOver();
    public slots:
        void changeSize(int x, int y);
        void getNewFigure(figure *h);
        void figTrans(trans s);
        void timeOut();
        void restart();
        void setPause();
        void setPause(bool b);
        void changeColorMode();
    signals:
        void setColorMode(bool );
        void changeWinSize(int,int);
        void iNeedNewFigure();
        void GameOver(mode x);
        void scoreUp(int);
        void resetScore();
        void setText(QString s);
};

#endif
