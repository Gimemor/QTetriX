#ifndef FIGURE_H
#define FIGURE_H
#include <QPoint>
#include <QTimerEvent>
#include "gamefield.h"
#include "pplace.h"
class pplace;
class gamefield;
class figure
{
private:
    bool pos;
    int num;
    QPoint cord[4];
    pplace *place;
    gamefield * gf;
    char color;
public:
    figure(int x,char c,gamefield * z);
    ~figure();
    int getHCord(int x) const;
    int getWCord(int y) const;
    int getX(int x) const;
    int getY(int y) const;
    void incCord();
    void figRotate();
    void moveLeft();
    void moveRight();
    void create(int x);
    char getColor();
};

#endif // FIGURE_H
