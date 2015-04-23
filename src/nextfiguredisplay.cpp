#include "nextfiguredisplay.h"

nextFigureDisplay::nextFigureDisplay(QWidget *parent):
        QWidget(parent),colorMode(true)
{ }


void nextFigureDisplay::getNewFigure(figure *nf)
{
    emit sendFigure(f);
    f=nf;
    update();
}
void nextFigureDisplay::changeColorMode(bool b)
{
    colorMode=b; update();
}

void nextFigureDisplay::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    if(colorMode==true)
        switch(f->getColor())
        {
            case 'r': paint.setBrush(QBrush(Qt::red,Qt::SolidPattern));break;
            case 'b': paint.setBrush(QBrush(Qt::blue,Qt::SolidPattern)); break;
            case 'g': paint.setBrush(QBrush(Qt::green,Qt::SolidPattern)); break;
            case 'y': paint.setBrush(QBrush(Qt::yellow,Qt::SolidPattern)); break;
        }
    else paint.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    for(int i=0;i<4;i++)
    {
       int x=f->getX(i);
       int y=f->getY(i);
       paint.drawRoundRect(QRect(15*(y)+15,15*(x)+30,15,15),7,7);
    }
}

nextFigureDisplay::~nextFigureDisplay()
{}

