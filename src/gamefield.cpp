#include "gamefield.h"
#include <QDebug>

gamefield::gamefield(QWidget *parent):
        QWidget (parent),
        size(20,10),
        state(NULL),
        isPauseNow(false),stopGame(false),ColorMode(true),
        f(NULL),t(NULL),
        timerSpeed(300)
{
    QPalette p;
    resize(20*size.width(),20*size.height());
    connect(this,SIGNAL(changeWinSize(int,int)),parent,SLOT(changeSize(int,int)));
    emit changeWinSize((20*size.height()+142),(20*size.width())+40);
    createState(20,10);
    t=new QTimer(this);
    t->setSingleShot(false);
    connect(t,SIGNAL(timeout()),this,SLOT(timeOut()));
    t->start(timerSpeed);
}
void gamefield::startGame()
{
    emit iNeedNewFigure();
}
void gamefield::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(0,0,size.height()*20,0);
    painter.drawLine(size.height()*20,0,size.height()*20,size.width()*20);
    painter.drawLine(size.height()*20,size.width()*20,0,size.width()*20);
    painter.drawLine(0,0,0,size.width()*20);
    for (int i=0;i<size.height();i++)
        for (int j=0;j<size.width();j++)
        {
             if ((state[i][j]!='f'))
             {
               if(ColorMode==true)
                switch(state[i][j])
                {
                  case 'r':
                       painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));  break;
                  case 'b':
                       painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern)); break;
                  case 'g':
                        painter.setBrush(QBrush(Qt::green,Qt::SolidPattern)); break;
                  case 'y':
                       painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern)); break;
                }
               else
                   painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
               painter.drawRoundRect(QRect(20*i,20*j,20,20),15,15);
             }
         }
    if(f!=NULL)
    {
     if(ColorMode==true)
        switch(f->getColor())
         {
             case 'r': painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));break;
             case 'b': painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern)); break;
             case 'g': painter.setBrush(QBrush(Qt::green,Qt::SolidPattern)); break;
             case 'y': painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern)); break;
          }
      else painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
      for(int i=0;i<4;i++)
      {
         int x=f->getWCord(i);
         int y=f->getHCord(i);
         painter.drawRoundRect(QRect(20*y,20*x,20,20),15,15);
      }
  }
}

void gamefield::gameOver()
{
    setPause(true);
    stopGame=true;
    emit setText(QString::fromUtf8("Игра\nокончена\nПауза"));
    if(size==QSize(20,10))
     emit GameOver(default_size);
    else
     emit GameOver(user_size);

    f=NULL;
    update();
}


void gamefield::timeOut()
{
    bool b=false;
    for(int i=0;i<4;i++)
       if(state[f->getHCord(i)][f->getWCord(i)+1]!='f' || f->getWCord(i)+1==size.width())
           b=true;
    if (b==false)
           f->incCord();
    else
    {
        setFigure();
        check();
    }
    emit scoreUp(10);
    update();
}
void gamefield::check()
{
    bool gO=false;
    for(int i=0;i<size.height();i++)
        if (state[i][0]!='f')
            gO=true;
    bool b=false;
    int x=size.height();
    for(int i=0;i<size.width();i++)
    {
        for(int j=0;j<size.height();j++)
            if (state[j][i]=='f')
            { b=true; break; x--; }
        if(b==false)
            lineIsFull(i);
        if(x==0)
            break;
       x=size.height();
       b=false;
    }
    if(gO==true)
        gameOver();
}

// Установить состояние клетки (занята-'r' 'g' 'b' 'y' свободна- 'f');
void gamefield::setState(int x,int y,char set)
{ state[x][y]=set; }
// Изменить размер поля
void gamefield::setSize(int x,int y)
{
    for(int i=0;i<size.height();i++)
        delete [] state[i];
    delete [] state;
    f=NULL;
    emit changeWinSize((20*y+140),(20*x)+40);
    createState(x,y);
    emit resetScore();
    emit iNeedNewFigure();

}

void gamefield::changeSize(int x,int y)
{ setSize(x,y);}

void gamefield::getNewFigure(figure *nf)
{
    f=nf;
}

int gamefield::getHSize() const
{ return(size.height()) ;}

int gamefield::getWSize() const
{ return(size.width()) ;}

void  gamefield::setFigure()
{

    for(int i=0;i<4;i++)
        setState(f->getHCord(i),f->getWCord(i),f->getColor());
    f=NULL;
    t->setInterval(timerSpeed);
    emit iNeedNewFigure();
}

void gamefield::createState(int x, int y)
{
    size=QSize(x,y);
    state = new char *[size.height()];
    for (int i=0;i<size.height();i++)
    {
        state[i]=new char [size.width()];
        for (int j=0;j<size.width();j++)
            state[i][j]='f';
    }
}

void gamefield::figTrans(trans s)
{
    bool b=false;
    if (f!=NULL && isPauseNow==false)
      switch(s)
      {
          case rotate:
              f->figRotate();
              for(int i=0;i<4;i++)
                  if(f->getHCord(i)<0)
                      f->moveRight();
                  else if(f->getHCord(i)>size.height()-1)
                      f->moveLeft();
              break;
          case drop_down:
               t->setInterval(45);
               break;
          case move_left:
              b=false;
              for(int i=0;i<4;i++)
                  if(f->getHCord(i)==0 || state[f->getHCord(i)-1][f->getWCord(i)]!='f')
                      b=true;
             if(b!=true)
                  f->moveLeft();
               break;
          case move_right:
              b=false;
              for(int i=0;i<4;i++)
                  if(f->getHCord(i)==size.height()-1 || state[f->getHCord(i)+1][f->getWCord(i)]!='f')
                      b=true;
              if(b!=true)
                f->moveRight();
           break;
    }
    update();
}

void gamefield::restart()
{
    f=NULL;
    createState(size.width(),size.height());
    stopGame=false;
    setPause(false);
    timerSpeed=300;
    t->start(timerSpeed);
    emit iNeedNewFigure();
    emit setText("");
    emit resetScore();
}


void gamefield::setPause()
{
    if (isPauseNow==false)
    {
        isPauseNow=true;
        t->stop();
        emit setText(QString::fromUtf8("Пауза"));
    }
    else if (stopGame==false)
    {
        isPauseNow=false;
        t->start(timerSpeed);
        emit setText("");
    }
}
void gamefield::setPause(bool b)
{
    if (b==true)
    {
        isPauseNow=b;
        t->stop();
        emit setText(QString::fromUtf8("Пауза"));
    }
    else if (stopGame==false)
    {
        isPauseNow=b;
        t->start(timerSpeed);
        emit setText("");
    }
}
void gamefield::lineIsFull(int x)
{
    for(int i=0;i<size.height();i++)    // Очищаем строку
        setState(i,x,'f');
    for(int j=x;j>1;j--)
        for(int i=0;i<size.height();i++)    // Опускаем все клетки, которые находятся выше строки x
            setState(i,j,(state[i][j-1]));
    check();        // Проверим строки, получившиеся в результате, на заполнение
    if (timerSpeed>60)  // Уменьшим интервал
        timerSpeed-=10;
    emit scoreUp(50); // Увеличим кол-во очков
}

void gamefield::changeColorMode()
{
    ColorMode=(ColorMode==false)? true:false;
    emit setColorMode(ColorMode);
    update();
}

gamefield::~gamefield()
{}
