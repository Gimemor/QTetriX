#include <QtGui/QApplication>
#include <QtGui/QGridLayout>
#include <QMenuBar>
#include <QFrame>
#include <QDockWidget>
#include <QDebug>
#include "enums.h"
#include "mainwindow.h"
#include "gamefield.h"
#include "dialogs.h"
#include "figure.h"
#include "nextfiguredisplay.h"
#include "generator.h"
#include "scorewidget.h"
#include "scoreboard.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    dialogs dialog;
    QFrame * central=new QFrame();


    QMenuBar mbar;
    QMenu * mgame=new QMenu(QString::fromUtf8("&Игра"));

    nextFigureDisplay nfd(&w);

    gamefield display(&w);
    figure * f=new figure (2,'r',&display);
    nfd.getNewFigure(f);
    generator gen(&display);
    scoreWidget score(&w);
    scoreBoard scb;

    QGridLayout *Layout=new QGridLayout();
    QLabel lbl(QString::fromUtf8("Информация:"));
   // Layout->setMargin(5);
    Layout->setSpacing(1);
    Layout->addWidget(&display,1,1,10,20);
    Layout->addWidget(&lbl,1,20,1,6);
    Layout->addWidget(&nfd,2,20,4,4);
    Layout->addWidget(&score,4,20,4,4);
    central->setLayout(Layout);
    w.setCentralWidget(central);

    mgame->addAction(QString::fromUtf8("Новая Игра"),&display,SLOT(restart()),Qt::CTRL+Qt::Key_N);
    mgame->addAction(QString::fromUtf8("Пауза"),&display,SLOT(setPause()),Qt::Key_Pause);
    mgame->addSeparator();
    QAction *qa=mgame->addAction(QString::fromUtf8("Использовать цвета"),&display,SLOT(changeColorMode()),Qt::Key_B);
    qa->setCheckable(true);
    qa->setChecked(true);
    mgame->addAction(QString::fromUtf8("Размер поля"),&dialog,SLOT(setSize()),Qt::CTRL+Qt::Key_S);
    mgame->addSeparator();
    mgame->addAction(QString::fromUtf8("Рекорды"),&scb,SLOT(showBoard()),Qt::Key_F2);
    mgame->addAction(QString::fromUtf8("Помощь"),&dialog,SLOT(help()),Qt::Key_F1);
    mgame->addAction(QString::fromUtf8("О Qt"),&a,SLOT(aboutQt()),Qt::CTRL+Qt::Key_Q);
    mgame->addSeparator();
    mgame->addAction(QString::fromUtf8("Выход"),&a,SLOT(quit()),Qt::SHIFT+Qt::Key_Q);
    mbar.addMenu(mgame);
    w.setMenuBar(&mbar);

    QObject::connect(&dialog,SIGNAL(setPause(bool )),&display,SLOT(setPause(bool )));
    QObject::connect(&display,SIGNAL(iNeedNewFigure()),&gen,SLOT(generate()));
    QObject::connect(&gen,SIGNAL(sendFigure(figure *)),&nfd,SLOT(getNewFigure(figure *)));
    QObject::connect(&nfd,SIGNAL(sendFigure(figure *)),&display,SLOT(getNewFigure(figure *)));
    QObject::connect(&display,SIGNAL(setColorMode(bool )),&nfd,SLOT(changeColorMode(bool)));
    QObject::connect(&dialog,SIGNAL(changeSize(int,int)),&display,SLOT(changeSize(int , int )));
    QObject::connect(&display,SIGNAL(GameOver(mode)),&score,SLOT(gameOver(mode)));
    QObject::connect(&score,SIGNAL(sendScore(unsigned long long)),&scb,SLOT(getNewRecord(unsigned long long)));
    QObject::connect(&w,SIGNAL(FigTrans(trans )),&display,SLOT(figTrans(trans )));
    QObject::connect(&display,SIGNAL(scoreUp(int )),&score,SLOT(scoreUp(int )));
    QObject::connect(&display,SIGNAL(resetScore()),&score,SLOT(resetScore()));
    QObject::connect(&display,SIGNAL(setText(QString)),&score,SLOT(getText(QString)));

    display.startGame();
    w.show();

    return a.exec();
}
