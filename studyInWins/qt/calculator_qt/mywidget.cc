#include <iostream>
#include <stdio.h>
#include "mywidget.h"
#include "calculator.h"

using namespace std;

mywidget::mywidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    int i;
    int j;
    
    pmlay      = new QVBoxLayout;
    
    ptoplay    = new QHBoxLayout;
    pdisplay   = new QLineEdit;
    pdisplay->setReadOnly(true);

    pbottomlay = new QHBoxLayout;
    pllay      = new QGridLayout;
    prlay      = new QVBoxLayout;
    
    for(i=0;i<16;i++)
    {
        pbutton[i] = new QPushButton;
    }
    
    QString s("%1");
    QString s1;
    for(i=1;i<10;i++)
    {
        s1 = s.arg(i);
        pbutton[i-1]->setText(s1);
    }
    pbutton[9]->setText("0");
    pbutton[10]->setText("AC");
    pbutton[11]->setText("=");
    pbutton[12]->setText("+");
    pbutton[13]->setText("-");
    pbutton[14]->setText("*");
    pbutton[15]->setText("/");

    for(i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            pllay->addWidget(pbutton[i*3+j],i,j);
        }
    }
    for(i=12;i<16;i++)
    {
        prlay->addWidget(pbutton[i]);
    }
    pmlay->addLayout(ptoplay);
    ptoplay->addWidget(pdisplay);
    
    pmlay->addLayout(pbottomlay);
    pbottomlay->addLayout(pllay);
    pbottomlay->addLayout(prlay);
    
    setLayout(pmlay);
    connect(pbutton[0],SIGNAL(clicked(bool)),this,SLOT(pressbutton0(bool)));  // ::connect for networck connect
    connect(pbutton[1],SIGNAL(clicked(bool)),this,SLOT(pressbutton1(bool)));
    connect(pbutton[2],SIGNAL(clicked(bool)),this,SLOT(pressbutton2(bool)));
    connect(pbutton[3],SIGNAL(clicked(bool)),this,SLOT(pressbutton3(bool)));
    connect(pbutton[4],SIGNAL(clicked(bool)),this,SLOT(pressbutton4(bool)));
    connect(pbutton[5],SIGNAL(clicked(bool)),this,SLOT(pressbutton5(bool)));
    connect(pbutton[6],SIGNAL(clicked(bool)),this,SLOT(pressbutton6(bool)));
    connect(pbutton[7],SIGNAL(clicked(bool)),this,SLOT(pressbutton7(bool)));
    connect(pbutton[8],SIGNAL(clicked(bool)),this,SLOT(pressbutton8(bool)));
    connect(pbutton[9],SIGNAL(clicked(bool)),this,SLOT(pressbutton9(bool)));

    connect(pbutton[10],SIGNAL(clicked(bool)),this,SLOT(pressbuttonac(bool)));
    connect(pbutton[11],SIGNAL(clicked(bool)),this,SLOT(pressbuttoneq(bool)));
    connect(pbutton[12],SIGNAL(clicked(bool)),this,SLOT(pressbuttonadd(bool)));
    connect(pbutton[13],SIGNAL(clicked(bool)),this,SLOT(pressbuttonsub(bool)));
    connect(pbutton[14],SIGNAL(clicked(bool)),this,SLOT(pressbuttonmul(bool)));
    connect(pbutton[15],SIGNAL(clicked(bool)),this,SLOT(pressbuttondiv(bool)));

    connect(this,SIGNAL(bclicked(int)),this,SLOT(pressbutton(int))); // the emit ,the signals
}

void mywidget::pressbutton(int witch)
{
    if(10 == witch)
    {
        pdisplay->setText("0");
    }
    else if(11 == witch)
    {
        calcu calcu1;
        QString s = pdisplay->text();
        string s1 = s.toStdString();
        double num = calcu1.compute(s1);
        s.setNum(num);
        pdisplay->setText(s);
    }
    else
    {
        QString s = pdisplay->text();
        if(s == QString("0"))
        {
            s = pbutton[witch]->text();
        }
        else
        {
            s += pbutton[witch]->text();
        }
        pdisplay->setText(s);
    }
}

void mywidget::pressbutton0(bool check)
{
    emit bclicked(0);
}

void mywidget::pressbutton1(bool check)
{
    emit bclicked(1);
}

void mywidget::pressbutton2(bool check)
{
    emit bclicked(2);
}

void mywidget::pressbutton3(bool check)
{
    emit bclicked(3);
}

void mywidget::pressbutton4(bool check)
{
    emit bclicked(4);
}

void mywidget::pressbutton5(bool check)
{
    emit bclicked(5);
}

void mywidget::pressbutton6(bool check)
{
    emit bclicked(6);
}

void mywidget::pressbutton7(bool check)
{
    emit bclicked(7);
}

void mywidget::pressbutton8(bool check)
{
    emit bclicked(8);
}

void mywidget::pressbutton9(bool check)
{
    emit bclicked(9);
}

void mywidget::pressbuttonac(bool check)
{
    emit bclicked(10);
}

void mywidget::pressbuttoneq(bool check)
{
    emit bclicked(11);
}

void mywidget::pressbuttonadd(bool check)
{
    emit bclicked(12);
}
void mywidget::pressbuttonsub(bool check)
{
    emit bclicked(13);
}
void mywidget::pressbuttonmul(bool check)
{
    emit bclicked(14);
}
void mywidget::pressbuttondiv(bool check)
{
    emit bclicked(15);
}
