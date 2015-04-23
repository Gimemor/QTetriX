#include "generator.h"

generator::generator(gamefield *z):gf(z)
{
    srand((time(NULL)));
    oldColor=-1;
    oldNumber=-1;
}

void generator::generate()
{
    char c;
    int i,j;

    do
    { i=rand()%4+1 ; }
    while(i==oldColor);
    oldColor=i;

    do
    { j=rand()%10+1 ; }
    while(j==oldNumber);
    oldNumber=j;

    switch(i)
    {
        case 1:c='r'; break;
        case 2:c='b'; break;
        case 3:c='g'; break;
        case 4:c='y'; break;
    }
    emit sendFigure(new figure(j,c,gf));
}
generator::~generator()
{/**delete gf;**/}
