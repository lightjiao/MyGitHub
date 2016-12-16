#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "mainwidget.h"
#include "mychatwidget.h"
//#include "myselectfacewidget.h"

using namespace std;

void *getmessage(void *arg)
{
    mainwidget *pthis = (mainwidget *)arg;
    int clientsocketfd = pthis->clientsocketfd;
    int savefilefd;
    string savefilename;

    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    short trstype;
    short msgtype;
    int   msglen;
    QString tmp = "";
    QString facetmp;
    
    srand(time(NULL));
    string imagname = "imags/";
    int seed;
    char ttmp;
    
    QList<QListWidgetItem *> allitems;// = pthis->chatnamelist.selectedItems();
    QList<QListWidgetItem *>::iterator it;// = allitems.begin();

    struct chatwidgetinfo *tmpchatwidgetinfo;
    vector<struct chatwidgetinfo *>::iterator it2;

    while(1)
    {
        memset(message,0,4096);
        recv(clientsocketfd,phead,HEADLEN,MSG_WAITALL);
        trstype = ntohs(phead->trstype);
        msgtype = ntohs(phead->msgtype);
        msglen  = ntohl(phead->msglen);
        
        switch(msgtype)
        {
            case THE_FACE:
                recv(clientsocketfd,&seed,msglen,MSG_WAITALL);
                
                tmp.clear();
                facetmp.clear();

                tmp += phead->sourcename;
                tmp += ' ';
                tmp += phead->msgtime;
                
                facetmp += "<img src= \"./face/";
                facetmp += seed + '0';
                facetmp += ".jpg\"/>";
                
                if(trstype == BROADCAST) //////////////////////////////////////////////////////////// broadcast face
                {
                    pthis->readtext.append(tmp);
                    pthis->readtext.append(facetmp);
                    pthis->readtext.moveCursor(QTextCursor::End);
                }
                else if(trstype == SINGLE) ////////////////////////////////////////////////////////// single face
                {
                    it2 = pthis->allchatwidgetinfo.begin();
                    while(it2 != pthis->allchatwidgetinfo.end())
                    {
                        if((*it2)->chatname.compare(phead->sourcename) == 0)
                        {
                            (*it2)->chatwidget->readtext.append(tmp);
                            (*it2)->chatwidget->readtext.append(facetmp);
                            (*it2)->chatwidget->readtext.moveCursor(QTextCursor::End);
                            break;
                        }
                        else
                        {
                            it2++;
                        }
                    }
                }
                break;
            case TALK_MSG:
                recv(clientsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                tmp.clear();
                tmp += phead->sourcename;
                tmp += ' ';
                tmp += phead->msgtime;
                tmp += '\n';
                tmp += message+HEADLEN;
                tmp += '\n';

                if(trstype == BROADCAST) //////////////////////////////////////////////////////////// broadcast
                {
                    pthis->readtext.append(tmp);
                    pthis->readtext.moveCursor(QTextCursor::End);
                }
                else if(trstype == SINGLE) ////////////////////////////////////////////////////////// single
                {
                    it2 = pthis->allchatwidgetinfo.begin();
                    while(it2 != pthis->allchatwidgetinfo.end())
                    {
                        if((*it2)->chatname.compare(phead->sourcename) == 0)
                        {
                            (*it2)->chatwidget->readtext.append(tmp);
                            (*it2)->chatwidget->readtext.moveCursor(QTextCursor::End);
                            break;
                        }
                        else
                        {
                            it2++;
                        }
                    }
                    if(it2 == pthis->allchatwidgetinfo.end()) // tips there is message single (and record)
                    {
                        allitems = pthis->chatnamelist.findItems(QString(phead->sourcename),0);
                        it = allitems.begin();
                        //if((*it)->text().toStdString().find("[Message]") <= 0)
                        
                        (*it)->setText((*it)->text()+"[Message]"); // make tips
                        tmpchatwidgetinfo = new struct chatwidgetinfo;
                        tmpchatwidgetinfo->chatname = phead->sourcename;
                        tmpchatwidgetinfo->chatwidget = NULL;
                        pthis->allchatwidgetinfo.push_back(tmpchatwidgetinfo);// record the chatwidget info
                        tmpchatwidgetinfo->Message += tmp.toStdString();
                    }
                }// else if SINGLE
                break;
            case USER_LOG_IN:
                seed = rand();
                seed = seed%8;
                ttmp = seed + '1';
                imagname += ttmp;
                pthis->chatnamelist.addItem(new QListWidgetItem(QIcon(QObject::tr(imagname.c_str())), QObject::tr(phead->sourcename)));///// make chat name list
                break;
            case USER_LOG_OUT:
                allitems = pthis->chatnamelist.findItems(QString(phead->sourcename),0);
                it = allitems.begin();
                pthis->chatnamelist.removeItemWidget(*it); // delete from chatname list
                delete *it;
                /*
                it2 = pthis->allchatwidgetinfo.begin();
                while(it2 != pthis->allchatwidgetinfo.end())
                {
                    if((*it2)->chatname.compare(phead->sourcename) == 0)
                    {
                        it2 = pthis->allchatwidgetinfo.erase(it2);  // delete from chatwidget info
                        break;
                    }
                    else
                    {
                        it2++;
                    }
                }
                */
                break;
            case FILE_START:
                cout<<"file start"<<endl;
                it2 = pthis->allchatwidgetinfo.begin();
                while(it2 != pthis->allchatwidgetinfo.end())
                {
                    if((*it2)->chatname.compare(phead->sourcename) == 0)
                    {
                        (*it2)->chatwidget->readtext.append("------- Start trans file -------");
                        (*it2)->chatwidget->readtext.moveCursor(QTextCursor::End);
                        break;
                    }
                    else
                    {
                        it2++;
                    }
                }
                savefilefd = ::open("./Savefile",O_WRONLY|O_CREAT|O_APPEND,0666);
                if(savefilefd < 0)
                {
                    //(*it2)->chatwidget->readtext.append(QString("------- Save file failed --------"));
                    pthis->readtext.append(QString("------- Save file failed --------"));
                    break;
                }
                recv(clientsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                write(savefilefd,message+HEADLEN,msglen);
                break;
            case FILE_TRANS:
                cout<<"file trs"<<endl;
                recv(clientsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                write(savefilefd,message+HEADLEN,msglen);
                break;
            case FILE_END:
                cout<<"file end"<<endl;
                recv(clientsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                it2 = pthis->allchatwidgetinfo.begin();
                while(it2 != pthis->allchatwidgetinfo.end())
                {
                    if((*it2)->chatname.compare(phead->sourcename) == 0)
                    {
                        (*it2)->chatwidget->readtext.append("------- File trans end -------");
                        (*it2)->chatwidget->readtext.moveCursor(QTextCursor::End);
                        break;
                    }
                    else
                    {
                        it2++;
                    }
                }
                cout<<"end after end"<<endl;
                close(savefilefd);
                break;
            default:
                cout<<"wrong msgtype"<<endl;
                break;
        } // switch(msgtype) 
    }// while(1)
    return 0;
}

void mainwidget::createchatwidget(QListWidgetItem *item)
{
    string itemname(item->text().toStdString());
    
    if(itemname.compare(mychatname) == 0)
    {
        return ;
    }
   
    int Messagetippos = itemname.find("[Message]");
    if(Messagetippos > 0)
    {
        itemname.erase(Messagetippos,9);
        item->setText(QString(itemname.c_str()));
    }
    cout<<"the item name:"<<itemname<<endl;
    
    std::vector<struct chatwidgetinfo*>::iterator it;
    for(it = allchatwidgetinfo.begin();it != allchatwidgetinfo.end();it++)
    {
        if((*it)->chatname.compare(itemname) == 0)
        {
            if(Messagetippos > 0)
            {
                (*it)->chatwidget = new mychatwidget((void *)this,itemname);
                (*it)->chatwidget->readtext.append(QString((*it)->Message.c_str()));
                (*it)->chatwidget->show();
                (*it)->Message.clear();
            }
            else //if((*it)->chatwidget->isVisible())
            {
                (*it)->chatwidget->show();/// show top
            }
            break;
        }
    }
    if(it == allchatwidgetinfo.end())
    {
        struct chatwidgetinfo *tmpchatwidgetinfo = new struct chatwidgetinfo;
        tmpchatwidgetinfo->chatname = itemname;
        tmpchatwidgetinfo->chatwidget = new mychatwidget((void *)this,itemname);
        tmpchatwidgetinfo->chatwidget->show();
        allchatwidgetinfo.push_back(tmpchatwidgetinfo);
    }
}

mainwidget::mainwidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    facewidget = new myselectfacewidget(this);

    readtext.setReadOnly(true);
    readtext.setFixedWidth(350);
    readtext.setFixedHeight(250);
    readtext.setAcceptRichText(true);
    
    writetext.setFixedHeight(150);
    writetext.setAcceptRichText(true);
    
    chatnamelist.setFixedWidth(150);

    buttonsend.setText("Send");
    buttoncancel.setText("Cancel");

    face = toolbar.addAction(QIcon("./face/1.png"),QString("Face img"));

    forbutton.addWidget(&buttoncancel,0,2);
    forbutton.addWidget(&buttonsend,0,3);

    talkpart.addWidget(&readtext);
    talkpart.addWidget(&toolbar);
    talkpart.addWidget(&writetext);
    talkpart.addLayout(&forbutton);

    mainlay.addLayout(&talkpart);
    mainlay.addWidget(&chatnamelist);

    setLayout(&mainlay);

    connect(&buttonsend,SIGNAL(clicked(bool)),this,SLOT(presssend(void)));
    connect(&buttoncancel,SIGNAL(clicked(bool)),this,SLOT(presscancel(void)));
    connect(&logwidget,SIGNAL(login(void)),this,SLOT(preparegetmessage(void)));
    connect(&chatnamelist,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(createchatwidget(QListWidgetItem *)));///////
    connect(face,SIGNAL(triggered(bool)),this,SLOT(writeface(void)));
    
    ///////////////////////// the show part

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    logwidget.show();
}

mainwidget::~mainwidget(void)
{
    struct msghead message;
    message.trstype = htons(LOG_OUT);
    message.msglen  = htonl(0);
    strcpy(message.sourcename,mychatname.c_str());
    ::write(clientsocketfd,(char *)&message,HEADLEN);
}

void mainwidget::writeface(void)
{
    //writetext.append("<img src=\"./face/1.jpg\"/>");
    QPoint point = this->pos();
    point.ry() += 210;
    facewidget->move(point);
    facewidget->show();
    facewidget->pmainwidget = this;
}

void mainwidget::sendface(int facenum)
{
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    
    phead->trstype = htons(BROADCAST);
    phead->msgtype = htons(THE_FACE);
    phead->msglen  = htonl(4);
    strcpy(phead->sourcename,mychatname.c_str());
    
    QTime time = QTime::currentTime();
    strcpy(phead->msgtime,time.toString().toStdString().c_str());
    
    strcpy(message+HEADLEN,(char *)&facenum);

    QString tmp = mychatname.c_str();
    tmp += ' ';
    tmp += time.toString();
    readtext.append(tmp);
    
    QString tmp2 = "<img src= \"./face/";
    tmp2 += facenum + '0';
    tmp2 += ".jpg\"/>";
    readtext.append(tmp2);
    
    readtext.moveCursor(QTextCursor::End);
    ::write(clientsocketfd,message,HEADLEN+4);
}

void mainwidget::presssend(void)
{
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    
    QString qmessage = writetext.toPlainText();
    string  smessage = qmessage.toStdString();
    //string  smessage = thefacestring;
    
    if(smessage.empty())
    {
        return ;
    }
    ///////////////////////////////////////////////// the message packages
    phead->trstype = htons(BROADCAST);
    phead->msgtype = htons(TALK_MSG);
    phead->msglen  = htonl(smessage.length());
    strcpy(phead->sourcename,mychatname.c_str());
    
    QTime time = QTime::currentTime();
    strcpy(phead->msgtime,time.toString().toStdString().c_str());

    strcpy(message+HEADLEN,smessage.c_str());
    
    writetext.setPlainText("");
    QString tmp = mychatname.c_str();
    tmp += ' ';
    tmp += time.toString();
    tmp += '\n';
    tmp += qmessage;
    tmp += '\n';
    readtext.append(tmp);
    tmp.clear();
    thefacestring.clear();
    readtext.moveCursor(QTextCursor::End);
    ::write(clientsocketfd,message,HEADLEN+smessage.length());
}

void mainwidget::presscancel(void)
{
    ////////////////////////// close all the chat widget before logout
    /*
    std::vector<struct chatwidgetinfo *>::iterator it;
    for(it = allchatwidgetinfo.begin();it != allchatwidgetinfo.end();)
    {
        delete (*it)->chatwidget;
        it = allchatwidget.erase(it);
    }
    */
    close();
}

void mainwidget::preparegetmessage(void)
{
    clientsocketfd = logwidget.clientsocketfd;
    mychatname = logwidget.mychatname;
    setWindowTitle(mychatname.c_str());
    logwidget.close();
    //writetext.setCursor(); ////////// put cursor into writetext
    
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    recv(clientsocketfd,phead,HEADLEN,MSG_WAITALL);
    int msglen = ntohl(phead->msglen);
    recv(clientsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
    message[HEADLEN+msglen] = 0;
    char* tmpname = strtok (message+HEADLEN,",");
    while (tmpname != 0)
    {
        int seed = rand();
        seed = seed%8;
        char tmp = seed + '1';
        string imagname = "imags/";
        imagname += tmp;
        chatnamelist.addItem(new QListWidgetItem(QIcon(QObject::tr(imagname.c_str())), QObject::tr(tmpname)));///// make chat name list

        tmpname = strtok(NULL,",");
        /*
        if(tmpname[0])
        {
            int seed = rand();
            seed = seed%8;
            char tmp = seed + '1';
            string imagname = "imags/";
            imagname += tmp;
            chatnamelist.addItem(new QListWidgetItem(QIcon(QObject::tr(imagname.c_str())), QObject::tr(thename)));///// make chat name list
        }
        else
        {
            chatnamelist.addItem(new QListWidgetItem(QIcon(QObject::tr("")), QObject::tr(thename)));///// make chat name list
        }
        */
    }
    show();
    pthread_t gmsgpid;
    pthread_create(&gmsgpid,NULL,getmessage,(void *)this);
}

void mainwidget::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            presssend();
        }
    }   
}

