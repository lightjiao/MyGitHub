#include <iostream>
#include "mywidget.h"


void mywidget::mouseMoveEvent(QMouseEvent *event)
{
    
}

void mywidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    bool ok;
    if(event->button() == Qt::RightButton)
    {
        vpos.clear();
    }
    else if(event->button() == QtLeftButton)
    {
        
    }
}

void mywidget::paintEvent(QPaintEvent *event)
{
    
}
