#ifndef DIALOGS_H
#define DIALOGS_H
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>

class dialogs : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *spbWidth;
    QSpinBox *spbHeight;
    QWidget * dial;
public:
    dialogs();
    ~dialogs();
public slots:
    void setSize();
    void getSize();
    void help();
    void quit();
signals:
    void changeSize(int x,int y);
    void setPause(bool b);

};

#endif // DIALOGS_H
