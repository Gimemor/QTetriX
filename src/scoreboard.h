#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <fstream>
#include <QString>
#include <QtGui>

class scoreBoard : public QWidget
{
    Q_OBJECT
private:
    unsigned long long score[10];
    QString name[10];
    std::fstream file;
    QWidget *wg;
public:
    scoreBoard();
    void readFile();
    void update();
    void createFile();
public slots:
    void getNewRecord(unsigned long long x);
    void showBoard();
    void closeBoard();
signals:
    void setPause(bool b);
};

#endif // SCOREBOARD_H
