#include <iostream>
#include <fcntl.h>
#include "mychatwidget.h"
#include "mainwidget.h"

using namespace std;

mychatwidget::mychatwidget(void *arg,string &destname,QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    facewidget = new myselectfacewidget(this);

    readtext.setReadOnly(true);
    readtext.setFixedWidth(300);
    readtext.setFixedHeight(200);
    writetext.setFixedHeight(100);
    
    face = toolbar.addAction(QIcon("./face/1.png"),QString("Face img"));
    QAction *sendfile = toolbar.addAction(QIcon("./face/trsfile.png"),QString("Send file"));
    
    buttonsend.setText("Send");
    buttoncancel.setText("Cancel");
  
    forbutton.addWidget(&buttoncancel);
    forbutton.addWidget(&buttonsend);

    mainlay.addWidget(&readtext);
    mainlay.addWidget(&toolbar);
    mainlay.addWidget(&writetext);
    mainlay.addLayout(&forbutton);

    setLayout(&mainlay);

    pmainwidget = (mainwidget *)arg;
    this->destname = destname;
    this->mychatname = pmainwidget->mychatname;
    this->clientsocketfd = pmainwidget->clientsocketfd;

    string widgetname = "single talk to ";
    widgetname += this->destname;
    setWindowTitle(widgetname.c_str());
    
    connect(&buttonsend,SIGNAL(clicked(bool)),this,SLOT(presssend(void)));
    connect(&buttoncancel,SIGNAL(clicked(bool)),this,SLOT(presscancel(void)));
    connect(this,SIGNAL(close(bool)),this,SLOT(chatwidgetclose(void)));
    
    connect(face,SIGNAL(triggered(bool)),this,SLOT(writeface(void)));
    connect(sendfile,SIGNAL(triggered(bool)),this,SLOT(sendfile(void)));

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
}

void mychatwidget::sendfile(void) /////////////////// the send file
{

    QString filename = QFileDialog::getOpenFileName(this,tr("Choose a file to send")," ",tr("Allfile(*.*)"));
    int sendfilefd = open(filename.toStdString().c_str(),O_RDONLY);
    if(sendfilefd <= 0)
    {
        readtext.append(QString("-------- Open file failed! --------"));
        return ;
    }
    
    char message[4096];
    struct msghead *phead = (struct msghead *)message;

    ///////////////////////////////////////////////// the message packages
    
    int rt = ::read(sendfilefd,message+HEADLEN,4096-HEADLEN);
    
    phead->trstype = htons(SINGLE);
    phead->msgtype = htons(FILE_START);
    phead->msglen  = htonl(rt);
    strcpy(phead->sourcename,mychatname.c_str());
    strcpy(phead->destname,destname.c_str());
    //strcpy(phead->msgtime,);  the file name write into msgtime
    rt = ::write(clientsocketfd,message,HEADLEN+rt);
    readtext.append(QString("-------- File Trans Start! --------"));
    
    phead->msgtype = htons(FILE_TRANS);
    while(1)
    {
        rt = ::read(sendfilefd,message+HEADLEN,4096-HEADLEN);
        if(0 == rt)
        {
            cout<<"the read rt = 0 and break happen"<<endl;
            break;
        }
        cout<<"file trans ing"<<endl;
        phead->msglen = htonl(rt);
        rt = ::write(clientsocketfd,message,HEADLEN+rt);
    }
    phead->msgtype = htons(FILE_END);
    phead->msglen  = htonl(3000);
    write(clientsocketfd,message,HEADLEN+3000);
    readtext.append(QString("-------- File Trans Over! --------"));
    cout<<"send file end"<<endl;
}

void mychatwidget::writeface(void)
{
    QPoint point = this->pos();
    point.ry() += 150;
    facewidget->move(point);
    facewidget->show();
    facewidget->pchatwidget = this;
}

void mychatwidget::sendface(int facenum)
{
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
     
    phead->trstype = htons(SINGLE);
    phead->msgtype = htons(THE_FACE);
    phead->msglen  = htonl(4);
    strcpy(phead->sourcename,mychatname.c_str());
    strcpy(phead->destname,destname.c_str());
     
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

//mychatwidget::~mychatwidget(void)
/*
void mychatwidget::chatwidgetclose(void)
{
    cout<<"the chatwidget closed"<<endl;
    std::vector<struct chatwidgetinfo *>::iterator it = pmainwidget->allchatwidgetinfo.begin();
    while(it != pmainwidget->allchatwidgetinfo.end())
    {
        if(0 == mychatname.compare((*it)->chatname))
        {
            delete (*it)->chatwidget;
            it = pmainwidget->allchatwidgetinfo.erase(it);
            break;
        }
        else
        {
            it++;
        }
    }
}
*/
void mychatwidget::presssend(void)
{
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    
    QString qmessage = writetext.toPlainText();
    string  smessage = qmessage.toStdString();
  
    if(smessage.empty())
    {
        return ;
    }
    ///////////////////////////////////////////////// the message packages
    phead->trstype = htons(SINGLE);
    phead->msgtype = htons(TALK_MSG);
    phead->msglen  = htonl(smessage.length());
    strcpy(phead->sourcename,mychatname.c_str());
    strcpy(phead->destname,destname.c_str());
    
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
    tmp = "";
    ::write(clientsocketfd,message,HEADLEN+smessage.length());
}

void mychatwidget::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            presssend();
        }
    }
}

void mychatwidget::presscancel(void)
{
    close();
}
