#include <Application>
#include "mywidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);
    mywidget *win = new mywidget;
    win->setWindowTitle("My Calculation");

    win->show();
    rt = app.exec();
    delete win;
    return rt;
}
