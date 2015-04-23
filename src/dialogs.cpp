#include "dialogs.h"

dialogs::dialogs()
{}
void dialogs::setSize()
{
    emit setPause(true);
    QVBoxLayout *vblayout=new QVBoxLayout();
    QHBoxLayout *hblayout=new QHBoxLayout();
    dial=new QWidget(0);

    QLabel h(QString::fromUtf8("Высота:"));
    QLabel w(QString::fromUtf8("Ширина:"));


    spbHeight=new QSpinBox();
    spbWidth =new QSpinBox();

    QPushButton *okb=new QPushButton("OK");
    QPushButton *chb=new QPushButton(QString::fromUtf8("Отмена"));

    connect(chb,SIGNAL(clicked()),this,SLOT(quit()));
    connect(okb,SIGNAL(clicked()),this,SLOT(getSize()));

    spbHeight->setRange(10,40);
    spbHeight->setSuffix(QString::fromUtf8(" клеток"));
    spbHeight->setWrapping(true);
    spbHeight->setValue(10);

    spbWidth->setRange(10,40);
    spbWidth ->setSuffix(QString::fromUtf8(" клеток"));
    spbWidth->setWrapping(true);
    spbWidth->setValue(20);

    hblayout->addWidget(okb);
    hblayout->addWidget(chb);
    vblayout->addWidget(&h);
    vblayout->addWidget(spbHeight);
    vblayout->addWidget(&w);
    vblayout->addWidget(spbWidth);
    vblayout->addLayout(hblayout);

    dial->setFixedSize(200,200);
    dial->setWindowTitle(QString::fromUtf8("Настройки"));
    dial->setLayout(vblayout);
    dial->show();
}

void dialogs::help()
{
     emit setPause(true);
     dial=new QWidget(0);
     QVBoxLayout *vblayout=new QVBoxLayout();
     QPushButton *okb=new QPushButton("OK");
     QLabel *lbl=new QLabel(QString::fromUtf8(
                            "<H4><CENTER>Помощь</CENTER></H4>"
                            "<b>Влево,Вправо</b>       Переместить фигуру<br>"
                            "<b>Вниз</b>   Сбросить фигуру<br>"
                            "<b>Pause</b>   Пауза<br>"
                            "<b>CTRL+N</b>  Новая игра<br>"));
     vblayout->addWidget(lbl);
     vblayout->addWidget(okb);
     connect(okb,SIGNAL(clicked()),this,SLOT(quit()));
     dial->setLayout(vblayout);
     dial->show();
}
void dialogs::getSize()
{
    emit changeSize(dialogs::spbWidth->value(),dialogs::spbHeight->value());
    emit setPause(false);
    quit();
}

void dialogs::quit()
{
    emit setPause(false);
    dial->close();
}

dialogs::~dialogs()
{}
