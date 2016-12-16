#ifndef __MYSELECTFACEWIDGET_H__
#define __MYSELECTFACEWIDGET_H__

#include <QtGui>
#include <iostream>
#include <string>
#include <vector>

class mychatwidget;
class mainwidget;

class myselectfacewidget:public QWidget
{
    Q_OBJECT
    public slots:
        void selectface1(void);
        void selectface2(void);
        void selectface3(void);
        void selectface4(void);
        void selectface5(void);
        void selectface6(void);
    public:
        myselectfacewidget(QWidget *parent = 0,Qt::WindowFlags f = 0);
        //~myselectfacewidget(void);

        mainwidget *pmainwidget;
        mychatwidget *pchatwidget;

        int facenum;

        QVBoxLayout fortoolbar;
        QToolBar    faceselecttoolbar[2];
signals:
        //void facenum();
};

#endif
