#include <iostream>
#include <unistd.h>
#include "testwidget.h"

int main(int argc,char *argv[])
{
    int rt = 0;
    QApplication app(argc,argv);

    testwidget test;
    test.show();
    
    rt = app.exec();
    return rt;
}
