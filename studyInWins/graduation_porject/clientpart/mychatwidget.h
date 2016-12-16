
#ifndef __MYCHATWIDGET_H__
#define __MYCHATWIDGET_H__

#include <QtGui>
#include <string>
//#include "mainwidget.h"
#include "msg.h"
#include "myselectfacewidget.h"

class mainwidget;

class mychatwidget:public QWidget
{
    Q_OBJECT
    public slots:
        void presssend(void);
        void presscancel(void);
        //void chatwidgetclose(void);
        void writeface(void);
        void sendface(int facenum);
        void sendfile(void);
    public:
        mychatwidget(void *arg,std::string &destname,QWidget *parent = 0,Qt::WindowFlags f = 0);
        //~mychatwidget(void);

        mainwidget *pmainwidget;
        int clientsocketfd;
        std::string mychatname;
        std::string destname;
       
        QAction *face;
        myselectfacewidget *facewidget;
        std::string thefacestring;

        void keyPressEvent(QKeyEvent *event);
        
        QVBoxLayout mainlay;
        QTextEdit   readtext;
        QToolBar    toolbar;
        QTextEdit   writetext;
        QHBoxLayout forbutton;
        QPushButton buttonsend;
        QPushButton buttoncancel;
//signals:
  //      void chatwid_close(void);
};

#endif
