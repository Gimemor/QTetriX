#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>
#include <QKeyEvent>
#include "enums.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT   
public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
public slots:
    void changeSize(int x,int y);
signals:
    void FigTrans(trans s);
};

#endif // MAINWINDOW_H
