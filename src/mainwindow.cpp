#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent):
         QMainWindow(parent)
{
    setWindowTitle("Tetris");
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeSize(int x, int y)
{  setFixedSize(x,y); }
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {

        case Qt::Key_Space:
            emit FigTrans(rotate);
            break;
        case Qt::Key_Left:
            emit FigTrans(move_left);
            break;
        case Qt::Key_Right:
            emit FigTrans(move_right);
            break;
        case Qt::Key_Down:
            emit FigTrans(drop_down);
            break;

    }
}
