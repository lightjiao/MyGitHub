
#ifndef __MYLOGWIDGET_H__
#define __MYLOGWIDGET_H__

#include <QtGui>
#include <string>
#include "msg.h"

class mylogwidget:public QWidget
{
    Q_OBJECT
    public slots:
        void presslogin(void);
        void pressregister(void);
    public:
        mylogwidget(QWidget *parent = 0,Qt::WindowFlags f = 0);
        int clientsocketfd;
        std::string mychatname;
        void keyPressEvent(QKeyEvent *event);

        QVBoxLayout mainlay;
        
        QHBoxLayout forchatname;
        QLabel      thechatname;
        QLineEdit   chatname;

        QHBoxLayout forpassword;
        QLabel      thepassword;
        QLineEdit   password;

        QLabel      infolabel;

        QHBoxLayout forbutton;
        QPushButton buttonlog;
        QPushButton buttonreg;
signals:
        void login(void);
};

#endif
