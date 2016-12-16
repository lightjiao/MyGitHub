#include <stdio.h>
#include "mywidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    mywidget *win = new mywidget;
    win->setWindowTitle("My Calculation");

    printf("win->show()\n");
    win->show();

    printf("rt = app.exec()\n");
    rt = app.exec();
    
    printf("delete win\n");
    delete win;
    return rt;
}
