#include "figure.h"
figure::figure(int x,char c,gamefield *z):
        gf(z)
{
    pos=false;
    place=new pplace();
    place->set(gf->getHSize()/2,1);
    create(x);
    color=c;
}
char figure::getColor()
{return color;}
void figure::create(int x)
{
    cord[0]=QPoint(0,0);
    num=0;              // запомнить номер фигуры
    switch(x)
    {
        case 1:
            cord[1]=QPoint(-1,0);
            cord[2]=QPoint(0,-1);
            cord[3]=QPoint(0,1);
            break;
        case 2:
            cord[1]=QPoint(-1,0);
            cord[2]=QPoint(0,1);
            cord[3]=QPoint(-1,-1);
            break;
        case 3:
            cord[1]=QPoint(-1,0);
            cord[2]=QPoint(0,-1);
            cord[3]=QPoint(-1,-1);
            break;
        case 4:
            cord[1]=QPoint(-1,0);
            cord[2]=QPoint(1,0);
            cord[3]=QPoint(2,0);
            break;
        case 5:
            cord[1]=QPoint(-1,0);
            cord[2]=QPoint(1,0);
            cord[3]=QPoint(1,1);
            break;
        case 6:
            create(1);
            figRotate();
            figRotate();
            break;
        case 7:
            create(2);
            figRotate();
            figRotate();
            break;
        case 8:
            create(3);
            figRotate();
            figRotate();
            break;
        case 9:
            create(4);
            figRotate();
            figRotate();
            break;
        case 10:
            create(5);
            figRotate();
            figRotate();
            break;

    }
}
int figure::getWCord(int y) const
{ return cord[y].x()+place->y(); }

int figure::getHCord(int y) const
{ return cord[y].y()+place->x(); }

int figure::getX(int x) const
{return cord[x].x();}


int figure::getY(int y) const
{return cord[y].y();}

void figure::figRotate()
{
    switch(num)
    {
            case 0:
                for(int i=1;i<4;i++)
                {
                    int x=cord[i].x();
                    cord[i].setX(cord[i].y());
                    cord[i].setY(x);
                }
                num++;
                break;
            case 1:
                for(int i=1;i<4;i++)
                {
                    int x=cord[i].x();
                    cord[i].setX(-1*cord[i].y());
                    cord[i].setY(x);
                }
                num++;
                break;
             case 2:
                for(int i=1;i<4;i++)
                {
                    int x=cord[i].x()+cord[0].x();
                    cord[i].setY(-1*cord[i].y());
                    cord[i].setX(x);
                }
                num=0;
                break;

            }
}

void figure::moveLeft()
{ place->decX(); }


void figure::moveRight()
{ place->incX(); }


figure::~figure()
{delete place;}

void figure::incCord()
{ place->incY(); }
