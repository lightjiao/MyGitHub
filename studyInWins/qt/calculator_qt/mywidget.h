
#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QLineEdit>


class mywidget:public QWidget
{
    Q_OBJECT
    public:
        mywidget(QWidget *parent=0,Qt::WindowFlags f=0);
    signals:
        void bclicked(int);
    public slots:
        void pressbutton(int witch);
        void pressbutton0(bool check = false);
        void pressbutton1(bool check = false);
        void pressbutton2(bool check = false);
        void pressbutton3(bool check = false);
        void pressbutton4(bool check = false);
        void pressbutton5(bool check = false);
        void pressbutton6(bool check = false);
        void pressbutton7(bool check = false);
        void pressbutton8(bool check = false);
        void pressbutton9(bool check = false);
        void pressbuttonac(bool check = false);
        void pressbuttoneq(bool check = false);
        void pressbuttonadd(bool check = false);
        void pressbuttonsub(bool check = false);
        void pressbuttonmul(bool check = false);
        void pressbuttondiv(bool check = false);
    private:
        QPushButton *pbutton[16];
        QVBoxLayout *pmlay;
        
        QHBoxLayout *ptoplay;
        QLineEdit   *pdisplay;
        
        QHBoxLayout *pbottomlay;
        QGridLayout *pllay;
        QVBoxLayout *prlay;
};


#endif
