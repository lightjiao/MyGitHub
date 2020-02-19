#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

char *cmdstring[] = 
{
    "show",
    "quit",
    "add",
    "del",
    "find",
    "findname",
    "save",
    "reverse",
    "help"
};

enum
{
    CMDSHOW,
    CMDQUIT,
    CMDADD,
    CMDDEL,
    CMDFIND,
    CMDFINDNAME,
    CMDSAVE,
    CMDREVERSE,
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
    int i;
    int n = sizeof(cmdstring)/sizeof(char*);
    printf("|-------------------------------------------|\n");
    for(i=0;i<n;i++)
    {
        printf("%s\n",cmdstring[i]);
    }
    printf("|-------------------------------------------|\n");
    return ;
}

int main()
{
    struct student *phead = NULL;
    struct student *p;
    struct student tempstu;
    struct student *stu;
    int tempage;
    char cmd[1024];
    int cmdnum;
    int quit = 0;
    int select;
    FILE *studata;

    studata = fopen("studata","r+");
    if(NULL == studata)
    {
        studata = fopen("studata","w+");
        if(NULL == studata)
        {
            printf("cannot open file !\n");
            return -1;
        }
    }

    phead = readfromfile(studata);
    printf("|-------------------------------------------|\n");
    printf("|----Welcome to Student Database System-----|\n");
    printf("|-------------------------------------------|\n\n");
    printf("%d student have!\n",countlist(phead));

    while(0 == quit)
    {
        printf("|-------------------------------------------|\n");
        printf("|-------Please Input \"help\" for Help--------|\n");
        printf("|-------------------------------------------|\n");
        
        fgets(cmd,1024,stdin);
        cmd[strlen(cmd)-1] = 0;
        cmdnum = getcmd(cmd);
        switch(cmdnum)
        {
            case CMDSHOW:
                showallstu(phead);
                break;
            case CMDQUIT:
                printf("quit successful!\n");
                quit = 1;
                break;
            case CMDADD:
                printf("please input a new student:\nstudent's ID:");
                scanf("%s",tempstu.id);
                printf("please input student's Name:");
                scanf("%s",tempstu.name);
                printf("please input student's age:");
                scanf("%d",&tempage);
                tempstu.age = (char)tempage;
                fgets(cmd,1024,stdin);
                printf("please input student's sex:");
                scanf("%c",&tempstu.sex);
                fgets(cmd,1024,stdin);
                tempstu.next = NULL;
                p = findstu(phead,tempstu.id);
                if(NULL != p)
                {
                    printf("This id is already exist!\n");
                    break;
                }
                stu = newstu(&tempstu);
                phead = addstu(phead,stu);
                break;
            case CMDDEL:
                printf("please input the id you wante to delete:");
                scanf("%s",tempstu.id);
                fgets(cmd,1024,stdin);
                p = findstu(phead,tempstu.id);
                if(NULL == p)
                {
                    printf("not found the id!\n");
                    break;
                }
                phead = delstu(phead,p);
                break;
            case CMDFIND:
                printf("please input 1 for id,2 for name:");
                scanf("%d",&select);
                fgets(cmd,1024,stdin);
                if(1 == select)
                {
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    p = findstu(phead,tempstu.id);
                    if(NULL == p)
                    {
                        printf("not found the id!\n");
                        break;
                    }
                    showstu(p);
                }
                else if(2 == select)
                {
                    printf("please input the name you want to find:");
                    scanf("%s",tempstu.name);
                    fgets(cmd,1024,stdin);
                    p = phead;
                    do
                    {
                        p = findnamenext(p,tempstu.name);
                        if(NULL != p)
                        {
                            showstu(p);
                            p = p->next;
                        }
                    }while(NULL != p);
                    break;
                }
            case CMDSAVE:
                save(phead,studata);
                break;
            case CMDREVERSE:
                phead = reverse(phead);
                break;
            case CMDHELP:
                showhelp();
                break;
            default:
                printf("not this cmd\n");
                break;
        }
    }
    fclose(studata);
}
