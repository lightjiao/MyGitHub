
#ifndef __MYWIDGET_H__
#define __MYWIDGET_H__
#include <QtGui>
#include <vector>

using namespace std;

class mywidget:public QWidget
{
    protected:
        void mouseDoubleClickEvent(Qmousevent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void painEvent(QPainEvent *event);
    private:
        vector<QPoint> vpos;
};


#endif
