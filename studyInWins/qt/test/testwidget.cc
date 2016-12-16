
#include <iostream>
#include "testwidget.h"

using namespace std;

testwidget::testwidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    lay.addWidget(&mbar);
    lay.addWidget(&list);
    setLayout(&lay);
}
