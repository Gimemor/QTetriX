#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include "figure.h"
#include "gamefield.h"
#include <ctime>
#include <cstdlib>
class generator : public QObject
{
    Q_OBJECT
private:
    gamefield *gf;
    int oldColor;
    int  oldNumber;
public:
    generator(gamefield *z);
    ~generator();
public slots:
    void generate();
signals:
    void sendFigure(figure *f);

};

#endif // GENERATOR_H
