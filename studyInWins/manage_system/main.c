#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "hash.h"
#include "queue.h"
#include "student.h"


char *cmdstring[] = 
{
    "show",
    "quit",
    "add",
    "del",
    "find",
    "rename",
    "save",
    "showallbyname",
    "million",
    "help"
};

enum
{
    CMDSHOW,
    CMDQUIT,
    CMDADD,
    CMDDEL,
    CMDFIND,
    CMDRENAME,
    CMDSAVE,
    CMDSHOWALLBYNAME,
    CMDMILLION,
    CMDHELP,
    CMDNONE,
};

int getcmd(char *cmd)
{
    int i;
    int n = sizeof(cmdstring)/sizeof(char*);
    for(i=0;i<n;i++)
    {
        if(0 == strcmp(cmd,cmdstring[i]))
        {
            return i;
        }
    }
    return CMDNONE;
}

void showhelp(void)
{
    int n = sizeof(cmdstring)/sizeof(char*);
    printf("|--------------- command list --------------|\n");
    printf("|                                           |\n");
    printf("|     show :show all student info           |\n");
    printf("|     add  :add a new student info          |\n");
    printf("|     del  :del a student info by id        |\n");
    printf("|     find :find stu info by id or name     |\n");
    printf("|     rename :change a stu info             |\n");
    printf("|     million : add million stu info        |\n");
    printf("|     save :save all info into file         |\n");
    printf("|     quit :quit program and save           |\n");
    printf("|                                           |\n");
    printf("|-------------------------------------------|\n");
    return ;
}

////////////////////////////////////////////////////////////// FILE OPERATION

int open_file(FILE **studata,FILE **idhdata,struct idhash *ihash,FILE **nhashdata,struct namehash *nhash,FILE **bposdata,struct blankpos *bpos)
{

////////////////////////////////////////////////////////////// OPEN STUDATA
    
    *studata = fopen("data/studata","r+");
    if(NULL == *studata)
    {
        *studata = fopen("data/studata","w+");
        if(NULL == *studata)
        {
            printf("cannot open studata !\n");
            return -1;
        }
    }

///////////////////////////////////////////////////////////// OPEN AND OVER WRITE IDHASHDATA

    *idhdata = fopen("data/idhashdata","r+");
    if(NULL == *idhdata)
    {
        *idhdata = fopen("data/idhashdata","w+");
        if(NULL == *idhdata)
        {
            printf("cannot open idhashdata !\n");
            return -1;
        }
    }    
    readidhash(ihash,*idhdata);
    fclose(*idhdata);

//////////////////////////////////////////////////////////// OPEN AND OVER WRITE NAMEHASHDATA

    *nhashdata = fopen("data/namehashdata","r+");
    if(NULL == *nhashdata)
    {
        *nhashdata = fopen("data/namehashdata","w+");
        if(NULL == *nhashdata)
        {
            printf("cannot open namehashadata !\n");
            return -1;
        }
    }
    readnamehash(nhash,*nhashdata);
    fclose(*nhashdata);
    
//////////////////////////////////////////////////////////// OPEN AND OVER WRITE BPOSDATA

    *bposdata = fopen("data/blankposdata","r+");
    if(NULL == *bposdata)
    {
        *bposdata = fopen("data/blankposdata","w+");
        if(NULL == *bposdata)
        {
            printf("cannot open file !\n");
            return -1;
        }
    }
    readblankpos(bpos,*bposdata);
    fclose(*bposdata);
    
    return 0;
}

int save_file(struct idhash *ihash,struct namehash *nhash,struct blankpos *bpos,FILE **idhdata,FILE **nhashdata,FILE **bposdata)
{    
    *bposdata = fopen("data/blankposdata","w+");
    *nhashdata = fopen("data/namehashdata","w+");
    *idhdata = fopen("data/idhashdata","w+");
    saveidhash(ihash,*idhdata);
    savenamehash(nhash,*nhashdata);
    saveblankpos(bpos,*bposdata);
    fclose(*idhdata);
    fclose(*nhashdata);
    fclose(*bposdata);

    return 0;
}


///////////////////////////////////////////////////////////////////////  THE ADD FUNCTION

int add(struct student *tmpstu,struct idhash *idh,struct namehash *nhash,struct blankpos *bpos,FILE *studata)
{
    struct idnode tmpidnode;
    struct idnode *stuidnode;

    struct namenode tmpnamenode;
    struct namenode *stunamenode;
    
    if(0 != bpos->num)
    {
        tmpidnode.pos = tmpnamenode.pos = bpos->pos[bpos->num-1];
        bpos->num --;
    }
    else
    {
        fseek(studata,0,SEEK_END);
        tmpidnode.pos = tmpnamenode.pos = (unsigned int)(ftell(studata)/sizeof(struct student));
    }
    strcpy(tmpidnode.id,tmpstu->id);
    strcpy(tmpnamenode.name,tmpstu->name);

    stuidnode = newidnode(&tmpidnode);
    addidhash(idh,stuidnode);
    
    stunamenode = newnamenode(&tmpnamenode);
    addnamehash(nhash,stunamenode);

    savestudata(tmpstu,tmpidnode.pos,studata);

    return 0;
}


//////////////////////////////////////////////////////////////////////// THE DEL FUNCTION

int del(char *id,struct idhash *idh,struct namehash *nhash,struct blankpos *bpos,FILE *studata)
{
    int namehashindex;
    struct list *pos;
    struct list *phead;
    struct list *pstu;
    struct idnode *stuidnode;
    struct namenode *ptmp;
    struct student tmpstu;

    pstu = findidhash(idh,id);
    if(NULL == pstu)
    {
        printf("not found this id!\n");
        return -1;
    }
    stuidnode = container_of(pstu,struct idnode,lt);
    
    readstudata(&tmpstu,stuidnode->pos,studata);
    
    namehashindex = hashname(tmpstu.name);
    phead = &nhash->stuname[namehashindex];
    list_for_each(pos,phead)
    {
        ptmp = container_of(pos,struct namenode,lt);
        if(stuidnode->pos == ptmp->pos)
        {
            break;
        }
    }
    
    delidhash(pstu);
    delnamehash(pos);
    addblankpos(bpos,stuidnode->pos);
   
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////                                     /////////////////////////////////////
/////////////////////////////////            THE MAIN START           /////////////////////////////////////
/////////////////////////////////                                     /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    
    struct idhash ihash;
    struct namehash nhash;
    struct blankpos bpos;
    
    struct student tempstu;
    struct student renamestu;
    struct list *pstu;
    struct list *pos;
    struct list *phead;
    struct namenode *ptmp;
    struct idnode *stuidnode;
    struct namenode *stunamenode;
    int index;

    struct myqueue namenodequeue;
    struct myqueue namenodequeuefordel;

    int tempage;
    char cmd[1024];
    int cmdnum;
    int quit = 0;
    int seed;
    int i;
    int datanumber;

    FILE *studata;
    FILE *idhdata;
    FILE *nhashdata;
    FILE *bposdata;

    initallidhash(&ihash);
    initallnamehash(&nhash);

    initallqueue(&namenodequeue);
    initallqueue(&namenodequeuefordel);
    
    open_file(&studata,&idhdata,&ihash,&nhashdata,&nhash,&bposdata,&bpos);
    
    while(0 == quit)
    {
        datanumber = countidhash(&ihash);
        system("clear");
        printf("|*******************************************|\n");
        printf("|    Welcome to Student Database System     |\n");
        printf("|*******************************************|\n\n");
        printf("           %d student have!\n\n",datanumber);
        printf("|-------------------------------------------|\n");
        printf("|       Please Input \"help\" For Help        |\n");
        printf("|-------------------------------------------|\n");
        printf("Input Your Command:");
        
        fgets(cmd,1024,stdin);
        cmd[strlen(cmd)-1] = 0;
        cmdnum = getcmd(cmd);
        switch(cmdnum)
        {
            case CMDSHOW:
                showallbyid(&ihash,studata);
                break;
            
            case CMDSHOWALLBYNAME:
                showallbyname(&nhash,studata);
                break;
            case CMDQUIT:
                printf("Are You Sure To Quit(Y/N):");
                fgets(cmd,1024,stdin);
                cmd[strlen(cmd)-1] = 0;
                if(0 == strcmp(cmd,"y"))
                {
                    save_file(&ihash,&nhash,&bpos,&idhdata,&nhashdata,&bposdata);
                    printf("|-------------------------------------------|\n");
                    printf("|        File Auto Save Successful!         |\n");
                    printf("|        Quit Program  Successful!          |\n");
                    printf("|-------------------------------------------|\n");
                    quit = 1;
                }
                break;
            
            case CMDADD:
                printf("Please Input A New Student:\nStudent's ID:");
                scanf("%s",tempstu.id);
                printf("Student's Name:");
                scanf("%s",tempstu.name);
                printf("Student's Age:");
                scanf("%d",&tempage);
                tempstu.age = (char)tempage;
                fgets(cmd,1024,stdin);
                printf("Student's Sex:");
                scanf("%c",&tempstu.sex);
                fgets(cmd,1024,stdin);
                pstu = findidhash(&ihash,tempstu.id);
                if(NULL != pstu)
                {
                    printf("This Id Is Already Exist!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                    break;
                }
                
                add(&tempstu,&ihash,&nhash,&bpos,studata);

                break;
            
            case CMDDEL:
                printf("Please Input The Id You Wante To Delete:");
                scanf("%s",tempstu.id);
                fgets(cmd,1024,stdin);
                
                del(tempstu.id,&ihash,&nhash,&bpos,studata);
                
                break;
            
            case CMDFIND:
                printf("What Do You Want Find(ID,Name):");
                fgets(cmd,1024,stdin);
                cmd[strlen(cmd)-1] = 0;
               
                if(0 == strcmp(cmd,"id"))
                {
                    printf("Please Input The Id You Want To Find:");
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    pstu = findidhash(&ihash,tempstu.id);
                    if(NULL == pstu)
                    {
                        printf("This Id Is Not Exist!(Press Any Key To Continue...)");
                        fgets(cmd,1024,stdin);
                        break;
                    }
                    printf("\n");
                    showonestu(container_of(pstu,struct idnode,lt)->pos,studata);
                    printf("\n(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                }

                else if(0 == strcmp(cmd,"name"))
                {
                    printf("Please Input The Name You Want To Find:");
                    scanf("%s",tempstu.name);
                    fgets(cmd,1024,stdin);
                    phead = &nhash.stuname[hashname(tempstu.name)];
                    pstu = phead->next;
                    do
                    {
                        pstu = findnamenext(pstu,tempstu.name,phead);
                        if(NULL != pstu)
                        {
                            putqueue(&namenodequeue,pstu);
                            putqueue(&namenodequeuefordel,pstu);
                            pstu = pstu->next;
                        }
                    }while(NULL != pstu);

                    if(queueisempty(&namenodequeue))
                    {
                        printf("This Name Is Not Exist!(Press Any Key To Continue...)");
                        fgets(cmd,1024,stdin);
                        break;
                    }
                    printf("\n");
                    while(!queueisempty(&namenodequeue))
                    {
                        pos = getqueue(&namenodequeue);
                        ptmp = container_of(pos,struct namenode,lt);
                        showonestu(ptmp->pos,studata);
                    }
                    printf("\nInput 'del' To Delete All This Name If You Want:");
                    fgets(cmd,1024,stdin);
                    cmd[strlen(cmd)-1] = 0;

                    if(0 == strcmp(cmd,"del"))
                    {
                        while(!queueisempty(&namenodequeuefordel))
                        {
                            pos = getqueue(&namenodequeuefordel);
                            ptmp = container_of(pos,struct namenode,lt);
                            readstudata(&tempstu,ptmp->pos,studata);
                            del(tempstu.id,&ihash,&nhash,&bpos,studata);
                        }
                    }
                    initallqueue(&namenodequeuefordel);
                }
                
                else
                {
                    printf("Command Error!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                }
                
                break;

            case CMDRENAME:
                printf("Please Input The ID You Want Rename:");
                scanf("%s",tempstu.id);
                fgets(cmd,1024,stdin);
                
                pstu = findidhash(&ihash,tempstu.id);
                if(pstu == NULL)
                {
                    printf("This ID Is Not Exist!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                    break;
                }
                
                index = hashid(tempstu.id);
                phead = &ihash.stuid[index];
                list_for_each(pos,phead)
                {
                    stuidnode = container_of(pos,struct idnode,lt);
                    if(0 == strcmp(stuidnode->id,tempstu.id))
                    {
                        printf("The Student Info Is:\n");
                        readstudata(&tempstu,stuidnode->pos,studata);
                        showonestu(stuidnode->pos,studata);
                        printf("\n");
                        del(tempstu.id,&ihash,&nhash,&bpos,studata);
                        break;
                    }
                }
                
                printf("Please Input The Info You Want Change(ID,Name,Age,Sex):");
                fgets(cmd,1024,stdin);
                cmd[strlen(cmd)-1] = 0;
                
                if(0 == strcmp(cmd,"id"))
                {
                    printf("Please Input The New ID:");
                    
                    while(1)
                    {
                        scanf("%s",renamestu.id);
                        fgets(cmd,1024,stdin);
                        
                        pstu = findidhash(&ihash,renamestu.id);
                        if(NULL == pstu)
                        {
                            break;
                        }
                        else
                        {
                            printf("This ID Is Already Exist,Please Input Another One:");
                        }
                    }
                    strcpy(tempstu.id,renamestu.id);
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                }
                
                if(0 == strcmp(cmd,"name"))
                {
                    printf("Please Input The New Name:");
                    scanf("%s",renamestu.name);
                    fgets(cmd,1024,stdin);
                    strcpy(tempstu.name,renamestu.name);
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                }
                
                if(0 == strcmp(cmd,"age"))
                {
                    printf("Please Input The New Age:");
                    scanf("%d",&tempage);
                    tempstu.age = (char)tempage;
                    fgets(cmd,1024,stdin);
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                }
                
                if(0 == strcmp(cmd,"sex"))
                {
                    printf("Please Input The New Sex:");
                    scanf("%c",renamestu.sex);
                    fgets(cmd,1024,stdin);
                    tempstu.sex = renamestu.sex;
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                }
                
                else
                {
                    printf("Commaned Error!!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                }

                break;

            case CMDSAVE:
                save_file(&ihash,&nhash,&bpos,&idhdata,&nhashdata,&bposdata);
                
                printf("|-------------------------------------------|\n");
                printf("|        Save Idhash   Successful!          |\n");
                printf("|        Save Namehash Successful!          |\n");
                printf("|        Save Blankpos Successful!          |\n");
                printf("|-------------------------------------------|\n");
                printf("(Press Any Key To Continue...)");
                fgets(cmd,1024,stdin);
                break;
            
            case CMDMILLION:
                srand(time(NULL));
                datanumber = 0;
                
                while(datanumber < 900000)
                {
                    for(i=0;i<6;i++)
                    {
                        seed = rand();
                        tempstu.name[i] = (seed%26) +'a';
                    }
                    seed = datanumber;
                    for(i=5;i>=0;i--)
                    {
                        tempstu.id[i] = seed%10 + '0';
                        seed = seed/10;
                    }
                    tempstu.age = (char)(20 + seed%5);
                    tempstu.sex = (seed%2 == 1)?'f':'m';

                    pstu = findidhash(&ihash,tempstu.id);
                    if(NULL != pstu)
                    {
                        continue;
                    }
                    
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                    
                    datanumber ++;
                }
                while(datanumber < 1000000)
                {
                    seed = datanumber;
                    for(i=5;i>=0;i--)
                    {
                        tempstu.id[i] = seed%10 + '0';
                        seed = seed/10;
                    }
                    strcpy(tempstu.name,"jack");
                    tempstu.age = (char)(20 + seed%5);
                    tempstu.sex = (seed%2 == 1)?'f':'m';
                    
                    pstu = findidhash(&ihash,tempstu.id);
                    if(NULL != pstu)
                    {
                        continue;
                    }
                    
                    add(&tempstu,&ihash,&nhash,&bpos,studata);
                    
                    datanumber ++;
                    
                }
                break;
            
            case CMDHELP:
                showhelp();
                printf("(Press Any Key To Continue...)");
                fgets(cmd,1024,stdin);
                break;
            
            default:
                showhelp();
                printf("Commaned Error!!(Press Any Key To Continue...)");
                fgets(cmd,1024,stdin);
                break;
        }
    }
    fclose(studata);
}
