#include "scoreboard.h"
using namespace std;
scoreBoard::scoreBoard()
{
    file.open("record.dat", ios::in);
    if (!file.good())
        createFile();
    file.close();
}
void scoreBoard::createFile()
{
    file.open("record.dat", ios::out | ios::trunc);
    for(int i=0;i<10;i++)
    {
        file << "0" << endl;
        file <<" Игрок " << endl;
    }
    file.close();
}
void scoreBoard::readFile()
{
    file.open("record.dat", ios::in);
    for(int i=0;i<10;i++)
    {
        file >> score[i];
        char tmp[20];
        file >> tmp;
        name[i]=QString::fromUtf8(tmp);
    }
    file.close();
}
void scoreBoard::showBoard()
{
    readFile();
    wg=new QWidget(0);
    QVBoxLayout *layout=new QVBoxLayout;
    emit setPause(true);
    wg->resize(320,240);
    QLabel *lbl=new QLabel(QString::fromUtf8("<CENTER><H2>Рекорды</H2></CENTER>")+
               QString::fromUtf8("<OL><LI>")+name[0]+QString::fromUtf8(" - ")+QString::number(score[0])+ QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[1]+  QString::fromUtf8(" - ")+ QString::number(score[1])+  QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[2]+  QString::fromUtf8(" - ")+   QString::number(score[2])+    QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[3]+  QString::fromUtf8(" - ")+QString::number(score[3])+    QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[4]+  QString::fromUtf8(" - ")+QString::number(score[4])+    QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[5]+  QString::fromUtf8(" - ")+QString::number(score[5])+    QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[6]+  QString::fromUtf8(" - ")+QString::number(score[6])+  QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[7]+  QString::fromUtf8(" - ")+QString::number(score[7])+  QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[8]+  QString::fromUtf8(" - ")+QString::number(score[8])+  QString::fromUtf8("</LI>")+
               QString::fromUtf8("<LI>")+name[9]+  QString::fromUtf8(" - ")+QString::number(score[9])+  QString::fromUtf8(" </LI>"));
    QPushButton *okb=new QPushButton("OK");
    QObject::connect(okb,SIGNAL(clicked()),this,SLOT(closeBoard()));
    layout->addWidget(lbl);
    layout->addWidget(okb);
    wg->setLayout(layout);
    wg->show();
}

void scoreBoard::closeBoard()
{
    wg->close();
    emit setPause(false);
}
void scoreBoard::update()
{
    file.open("record.dat",ios::out | ios::trunc);
    for(int i=0;i<10;i++)
    {
        file << score[i] << endl;
        file << name[i].toUtf8().data() << endl;
    }
    file.close();
}

void scoreBoard::getNewRecord(unsigned long long x)
{
    readFile();x+=10;
    for(int i=0;i<10;i++)
    {
        if(x>score[i])
        {
            score[9]=x; bool b=true;
            name[9]=(QInputDialog::getText(0,QString::fromUtf8("Новый рекорд!!"),QString::fromUtf8("Введите ваше имя:"),QLineEdit::Normal,QString::fromUtf8("Игрок"),&b));
            for(int i=10;i>0;i--)
                for(int j=9;j>10-i;j--)
                {
                    if(score[j]>score[j-1])
                    {
                        unsigned long long tmp=score[j];
                        score[j]=score[j-1];
                        score[j-1]=tmp;
                        QString stmp=name[j];
                        name[j]=name[j-1];
                        name[j-1]=stmp;
                    }
                }
              update();
              break;
        }
    }
}
