#include <iostream>
#include <unistd.h>
#include "msg.h"
#include "mainwidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);

    mainwidget *win = new mainwidget;
    
    rt = app.exec();
    delete win;
    return rt;
}
