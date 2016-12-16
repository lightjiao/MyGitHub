#include <iostream>
#include "mylogwidget.h"

using namespace std;

mylogwidget::mylogwidget(QWidget *parent,Qt::WindowFlags f):QWidget(parent,f)
{
    setWindowTitle("Login in");
    
    thechatname.setText(QString("Chatname:"));
    thepassword.setText(QString("Password: "));
    
    password.setEchoMode(QLineEdit::Password);

    infolabel.clear();

    buttonlog.setText("Login");
    buttonreg.setText("Registe");

    forchatname.addWidget(&thechatname);
    forchatname.addWidget(&chatname);
    
    forpassword.addWidget(&thepassword);
    forpassword.addWidget(&password);
    
    forbutton.addWidget(&buttonlog);
    forbutton.addWidget(&buttonreg);

    mainlay.addLayout(&forchatname);
    mainlay.addLayout(&forpassword);
    mainlay.addWidget(&infolabel);
    mainlay.addLayout(&forbutton);

    setLayout(&mainlay);
    
    connect(&buttonlog,SIGNAL(clicked(bool)),this,SLOT(presslogin(void)));
    connect(&buttonreg,SIGNAL(clicked(bool)),this,SLOT(pressregister(void)));

    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-width())/2,desktop->height()-height());
}

void mylogwidget::presslogin(void)
{
    clientsocketfd = ::socket(AF_INET,SOCK_STREAM,0);
    if(-1 == clientsocketfd)
    {
        cout<<"cannot socket cilent!"<<endl;
        return ;
    }
    
    struct sockaddr_in clientin;

    clientin.sin_family = AF_INET;
    clientin.sin_port   = htons(TCPPORT);
    clientin.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(clientin.sin_zero,0,8);
    
    int rt = ::connect(clientsocketfd,(struct sockaddr *)&clientin,sizeof(clientin));
    if(rt < 0)
    {
        infolabel.setText(QString("Connect failed!"));
        return ;
    }
   
    struct msghead message;
    mychatname = chatname.text().toStdString();
    string spassword = password.text().toStdString();
    message.trstype  = htons(LOG_IN);
    strcpy(message.sourcename,mychatname.c_str());
    strcpy(message.destname,spassword.c_str());             //////////////// dest name part have password inside
    
    ::write(clientsocketfd,(char *)&message,HEADLEN);
    ::recv(clientsocketfd,(char *)&message,HEADLEN,MSG_WAITALL);
   
    cout<<"trstype = "<<ntohs(message.trstype)<<endl;
    if(ntohs(message.trstype) == CHATNAME_NOTEXIST)
    {
        infolabel.setText(QString("Chatname not exist!"));
        return;
    }
    if(ntohs(message.trstype) == PASSWORD_WRONG)
    {
        infolabel.setText(QString("Wtong password!"));
        return ;
    }

    if(ntohs(message.trstype) != CHATNAME_SUCCESSFUL)
    {
        cout<<"fault none reason but chatname not successful"<<endl;
        return ;
    }

    emit login();
}

void mylogwidget::pressregister(void)
{
    clientsocketfd = ::socket(AF_INET,SOCK_STREAM,0);
    if(-1 == clientsocketfd)
    {
        cout<<"cannot socket cilent!"<<endl;
        return ;
    }
    
    struct sockaddr_in clientin;

    clientin.sin_family = AF_INET;
    clientin.sin_port   = htons(TCPPORT);
    clientin.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(clientin.sin_zero,0,8);
    
    int rt = ::connect(clientsocketfd,(struct sockaddr *)&clientin,sizeof(clientin));
    if(rt < 0)
    {
        infolabel.setText(QString("Caonnot failed"));
        return ;
    }
   
    struct msghead message;
    mychatname = chatname.text().toStdString();
    string spassword = password.text().toStdString();
    message.trstype  = htons(CHATNAME_REG);
    message.msglen   = htonl(0);
    strcpy(message.sourcename,mychatname.c_str());
    strcpy(message.destname,spassword.c_str());   /////////////// dest name have the password inside
    
    ::write(clientsocketfd,(char *)&message,HEADLEN);
    ::recv(clientsocketfd,(char *)&message,HEADLEN,MSG_WAITALL);
    
    if(ntohs(message.trstype) == CHATNAME_REPEAT)
    {
        infolabel.setText(QString("Chatname repeat!"));
        return ;
    }

    emit login();
}

void mylogwidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        presslogin();
    }
}
