
#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include <QtGui>
#include <iostream>
#include <string>
#include <vector>
#include "mylogwidget.h"
//#include "mychatwidget.h"
#include "myselectfacewidget.h"
#include "msg.h"

class mychatwidget;
//class myselectfacewidget;

struct chatwidgetinfo
{
    std::string chatname;
    mychatwidget *chatwidget;
    std::string Message;
};

class mainwidget:public QWidget
{
    Q_OBJECT
    public slots:
        void presssend(void);
        void presscancel(void);
        void preparegetmessage(void);
        void createchatwidget(QListWidgetItem *item);
        void writeface(void);
        void sendface(int facenum);
        //void sendfile(void);
    public:
        mainwidget(QWidget *parent = 0,Qt::WindowFlags f = 0);
        ~mainwidget(void);
        
        int clientsocketfd;
        std::string mychatname;
       
        std::vector<struct chatwidgetinfo*> allchatwidgetinfo;
        mylogwidget logwidget;
        
        QAction *face;
        myselectfacewidget *facewidget;
        std::string thefacestring;

        void keyPressEvent(QKeyEvent *event);

        //////////////////////////// the lay part
        
        QHBoxLayout mainlay;

        QListWidget chatnamelist; ///////chat name list
        QVBoxLayout talkpart;

        QTextEdit   readtext;

        QToolBar    toolbar;

        QTextEdit   writetext;
        
        QGridLayout forbutton;
        QPushButton buttonsend;
        QPushButton buttoncancel;
signals:
        void logout(void);
};

#endif
