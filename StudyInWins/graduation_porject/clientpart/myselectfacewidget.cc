#include <iostream>
#include "myselectfacewidget.h"
#include "mainwidget.h"
#include "mychatwidget.h"

using namespace std;

myselectfacewidget::myselectfacewidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    setWindowFlags(Qt::WindowFlags(Qt::Popup));// no top lay

    QAction *face1 = faceselecttoolbar[0].addAction(QIcon("./face/1.png"),QString("/smile"));
    QAction *face2 = faceselecttoolbar[0].addAction(QIcon("./face/2.png"),QString("/laugh"));
    QAction *face3 = faceselecttoolbar[0].addAction(QIcon("./face/3.png"),QString("/embarrass"));
    QAction *face4 = faceselecttoolbar[1].addAction(QIcon("./face/4.png"),QString("/giggle"));
    QAction *face5 = faceselecttoolbar[1].addAction(QIcon("./face/5.png"),QString("/sigh"));
    QAction *face6 = faceselecttoolbar[1].addAction(QIcon("./face/6.png"),QString("/bad smile"));

    fortoolbar.addWidget(&faceselecttoolbar[0]);
    fortoolbar.addWidget(&faceselecttoolbar[1]);
    setLayout(&fortoolbar);

    pmainwidget = NULL;
    pchatwidget = NULL;

    connect(face1,SIGNAL(triggered(bool)),this,SLOT(selectface1(void)));
    connect(face2,SIGNAL(triggered(bool)),this,SLOT(selectface2(void)));
    connect(face3,SIGNAL(triggered(bool)),this,SLOT(selectface3(void)));
    connect(face4,SIGNAL(triggered(bool)),this,SLOT(selectface4(void)));
    connect(face5,SIGNAL(triggered(bool)),this,SLOT(selectface5(void)));
    connect(face6,SIGNAL(triggered(bool)),this,SLOT(selectface6(void)));
}

void myselectfacewidget::selectface1(void)
{ 
    //pmainwidget->writetext.append("<img src=\"./face/1.jpg\"/>?");
    //pmainwidget->thefacestring += "<img src=\"./face/1.jpg\"/>";
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(1);
    }
    else
    {
        pchatwidget->sendface(1);
    }
    hide();
}
void myselectfacewidget::selectface2(void)
{ 
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(2);
    }
    else
    {
        pchatwidget->sendface(2);
    }
    hide();
}
void myselectfacewidget::selectface3(void)
{ 
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(3);
    }
    else
    {
        pchatwidget->sendface(3);
    }
    hide();
}
void myselectfacewidget::selectface4(void)
{ 
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(4);
    }
    else
    {
        pchatwidget->sendface(4);
    }
    hide();
}
void myselectfacewidget::selectface5(void)
{ 
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(5);
    }
    else
    {
        pchatwidget->sendface(5);
    }
    hide();
}
void myselectfacewidget::selectface6(void)
{ 
    if(pchatwidget == NULL)
    {
        pmainwidget->sendface(6);
    }
    else
    {
        pchatwidget->sendface(6);
    }
    hide();
}
