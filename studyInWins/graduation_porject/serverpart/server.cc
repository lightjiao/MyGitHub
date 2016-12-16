#include <iostream>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <mysql/mysql.h>

#include "msg.h"

using namespace std;


pthread_mutex_t clientdata_opt_mutex;


//////////////////////////////////////////////////////////////////////////////////////////////////////// get client message and transmit

void* transmessage(void *arg)
{
    int acceptsocketfd = (int)arg;
    char message[4096];
    struct msghead *phead = (struct msghead *)message;
    int rt;
    string thischatname;

    struct msghead *logmessage = new struct msghead;

    string sqlcmd;
    string chatnamelist;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    if(mysql_real_connect(conn,"localhost","root","","chatuser",0,NULL,0) == NULL)
    {
        cout<<"error connecting to database"<<mysql_error(conn)<<endl;
        return 0;
    }
    cout<<"mysql connect success"<<endl;

    
    bool quit = false;
    while(!quit)
    {
        rt = recv(acceptsocketfd,phead,HEADLEN,MSG_WAITALL);
        if(rt <= 0)
        {
            break;
        }
        short trstype = ntohs(phead->trstype);
        int   msglen  = ntohl(phead->msglen);
        switch(trstype)
        {
            case CHATNAME_REG:
                phead->trstype = htons(CHATNAME_SUCCESSFUL);
                sqlcmd = "select chatname from chatuser";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    if(0 == strcmp(phead->sourcename,row[0]))
                    {
                        phead->trstype = htons(CHATNAME_REPEAT);
                        break;
                    }
                }
                mysql_free_result(res);
                write(acceptsocketfd,phead,HEADLEN);// tell client reg success or not
                
                if(phead->trstype == htons(CHATNAME_SUCCESSFUL))//if name successful update the isonline sql part
                {
                    thischatname = phead->sourcename;
                    sqlcmd = "insert into chatuser values(";
                    sqlcmd += "'";
                    sqlcmd += phead->sourcename;
                    sqlcmd += "','";
                    sqlcmd += phead->destname;
                    sqlcmd += "',";
                    sqlcmd += acceptsocketfd + '0';
                    sqlcmd += ",1)";
                    rt = mysql_query(conn,sqlcmd.c_str());
                    sqlcmd.clear();

                    //////////////////////////////////////////////////

                    sqlcmd = "select chatname,socketfd from chatuser where isonline = 1";
                    rt = mysql_query(conn,sqlcmd.c_str());
                    sqlcmd.clear();
                    res = mysql_store_result(conn);
                     
                    logmessage->msgtype = htons(USER_LOG_IN); /// the logmessage package
                    strcpy(logmessage->sourcename,thischatname.c_str());
                     
                    chatnamelist.clear(); //////////////////////// make chatname list
                    while(1)
                    {
                        row = mysql_fetch_row(res);
                        if(NULL == row)
                        {
                            break;
                        }
                        chatnamelist += row[0];
                        chatnamelist += ",";
                        if(atoi(row[1]) == acceptsocketfd)
                        {
                            continue;
                        }
                        write(atoi(row[1]),(char *)logmessage,HEADLEN);//// tell other i am loged in 
                    }
                    phead->msglen = htonl(chatnamelist.length());
                    strcpy(message+HEADLEN,chatnamelist.c_str());
                    write(acceptsocketfd,message,HEADLEN+chatnamelist.length());
                }// if chat name successful
                break;
            case LOG_IN:
                cout<<"log_in is occured"<<endl;
                sqlcmd = "select chatname,password from chatuser";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    if(0 == strcmp(phead->sourcename,row[0]))
                    {
                        if(0 == strcmp(row[1],phead->destname))
                        {
                            thischatname = row[0];
                            phead->trstype = htons(CHATNAME_SUCCESSFUL);
                            sqlcmd = "update chatuser set socketfd = "; /////// update socketfd
                            char tmp = acceptsocketfd+'0';
                            sqlcmd += tmp;
                            sqlcmd += " where chatname = ";
                            sqlcmd += "'";
                            sqlcmd += row[0];
                            sqlcmd += "'";
                            rt = mysql_query(conn,sqlcmd.c_str());
                            sqlcmd.clear();
                            
                            sqlcmd = "update chatuser set isonline = 1 where chatname = "; /////// update log statement 
                            sqlcmd += "'";
                            sqlcmd += row[0];
                            sqlcmd += "'";
                            rt = mysql_query(conn,sqlcmd.c_str());
                            sqlcmd.clear();
                        }
                        else
                        {
                            phead->trstype = htons(PASSWORD_WRONG);
                        }
                        break;
                    }
                }
                if(NULL == row)
                {
                    phead->trstype = htons(CHATNAME_NOTEXIST);
                }
                mysql_free_result(res);
                if(phead->trstype != htons(CHATNAME_SUCCESSFUL))
                {
                    write(acceptsocketfd,phead,HEADLEN);  ////////////////////// tell client log failed
                    break;
                }

                //////////////////////////////////////////////////////////////// tell client log successful and who is online 

                sqlcmd = "select chatname,socketfd from chatuser where isonline = 1";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                
                logmessage->msgtype = htons(USER_LOG_IN); /// the logmessage package
                strcpy(logmessage->sourcename,thischatname.c_str());
                
                chatnamelist.clear(); //////////////////////// make chatname list
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    chatnamelist += row[0];
                    chatnamelist += ",";
                    if(atoi(row[1]) == acceptsocketfd)
                    {
                        continue;
                    }
                    write(atoi(row[1]),(char *)logmessage,HEADLEN);//// tell other i am loged in 
                }
                mysql_free_result(res);
               
                /*
                sqlcmd = "select chatname,isonline from chatuser";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    cout<<"the name "<<row[0];
                    printf(" %c\n",row[1]);
                    chatnamelist += row[0];
                    chatnamelist += ',';
                    chatnamelist += row[1];
                    chatnamelist += ',';
                }
                mysql_free_result(res);
                */
                phead->msglen = htonl(chatnamelist.length());
                strcpy(message+HEADLEN,chatnamelist.c_str());
                write(acceptsocketfd,message,HEADLEN);
                write(acceptsocketfd,message,HEADLEN+chatnamelist.length());
                break;
            case LOG_OUT:
                cout<<"log_out is occured"<<endl;
                sqlcmd = "update chatuser set isonline = 0 where chatname = "; /////// update log statement 
                sqlcmd += "'";
                sqlcmd += thischatname;
                sqlcmd += "'";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
               
                
                sqlcmd = "select socketfd from chatuser where isonline = 1"; /////// tell other i am loged out
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                
                logmessage->msgtype = htons(USER_LOG_OUT); /// the logmessage package
                strcpy(logmessage->sourcename,thischatname.c_str());
                
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    write(atoi(row[0]),(char *)logmessage,HEADLEN);//// tell other i am loged out 
                    cout<<"tell other log out happen"<<endl;
                }
                mysql_free_result(res);
                
                quit = true;
                break;
            case BROADCAST:
                cout<<"broad case is occured"<<endl;
                recv(acceptsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                
                sqlcmd = "select socketfd from chatuser where isonline = 1";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                while(1)
                {
                    row = mysql_fetch_row(res);
                    if(NULL == row)
                    {
                        break;
                    }
                    if(atoi(row[0]) == acceptsocketfd)
                    {
                        continue;
                    }
                    write(atoi(row[0]),message,HEADLEN+msglen);
                }
                mysql_free_result(res);
                break;
            case SINGLE:
                cout<<"single case is occured"<<endl;
                recv(acceptsocketfd,message+HEADLEN,msglen,MSG_WAITALL);
                
                sqlcmd = "select socketfd from chatuser where chatname = ";
                sqlcmd += "'";
                sqlcmd += phead->destname;
                sqlcmd += "'";
                rt = mysql_query(conn,sqlcmd.c_str());
                sqlcmd.clear();
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                
                write(atoi(row[0]),message,HEADLEN+msglen);
                
                mysql_free_result(res);
                break;
            default:
                cout<<"wrong trstype"<<endl;
                break;
        }// switch case
    }// while(!quit)
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////// the main

int main(int argc,char **argv)
{
    
    char message[4096];
    struct msghead *msgphead = (struct msghead*)message;

    pthread_mutex_init(&clientdata_opt_mutex,NULL); ///////////////// init mutex of netsocket
    
    pthread_t getmessagepid;
    pthread_t thransfilepid;
    
    cout<<"Server Mode Start:"<<endl;
    int serversocketfd = socket(AF_INET,SOCK_STREAM,0);
    if(serversocketfd < 0)
    {
        cout<<"cannot socket serverfd"<<endl;
        return -1;
    }

    struct sockaddr_in serverin;
    serverin.sin_family = AF_INET;
    serverin.sin_port   = htons(TCPPORT);
    serverin.sin_addr.s_addr = INADDR_ANY;
    memset(serverin.sin_zero,0,8);

    int len = sizeof(serverin);

    int rt = bind(serversocketfd,(struct sockaddr *)&serverin,len);
    if(rt < 0)
    {
        cout<<"cannot bind"<<endl;
        close(serversocketfd);
        return -1;
    }
    
    rt = listen(serversocketfd,SOMAXCONN);
    if(rt < 0)
    {
        cout<<"cannot listen"<<endl;
        close(serversocketfd);
        return -1;
    }

    ///////////////////////////////////////// the default chatname & password
    
    while(1)
    {
        int acceptsocketfd = accept(serversocketfd,(struct sockaddr *)&serverin,(socklen_t *)&len);
        if(acceptsocketfd < 0)
        {
            cout<<"cannot accept"<<endl;
            close(serversocketfd);
            return -1;
        }
        cout<<"IP:"<<inet_ntoa(serverin.sin_addr)<<" is accepted!"<<endl;

        pthread_create(&getmessagepid,NULL,transmessage,(void *)acceptsocketfd);
    }
    close(serversocketfd);
    return 0;
}

















