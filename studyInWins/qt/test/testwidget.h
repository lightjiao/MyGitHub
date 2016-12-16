

#ifndef __TEST_H__
#define __TEST_H__

#include <QtGui>

class testwidget:public QWidget
{
    public:
        testwidget(QWidget *parent = 0,Qt::WindowFlags f = 0);
        QVBoxLayout lay;
        QMenuBar    mbar;
        QListWidget list;
};

#endif
