#ifndef NEXTFIGUREDISPLAY_H
#define NEXTFIGUREDISPLAY_H
#include "gamefield.h"
#include "figure.h"
#include <QtGui/QWidget>
#include <QtGui/QPainter>

class figure;
class nextFigureDisplay : public QWidget
{
    Q_OBJECT
private:
    figure *f;
    bool colorMode;
public:
    nextFigureDisplay(QWidget *parent);
    ~nextFigureDisplay();
    void paintEvent(QPaintEvent *pe);
    void createState();
public slots:
    void getNewFigure(figure *nf);
    void changeColorMode(bool b);
signals:
    void sendFigure(figure *f);

};

#endif // NEXTFIGUREDISPLAY_H
