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
    struct list head;
    struct list *pos;
    struct student tempstu;
    struct student *stu;
    int tempage;
    char cmd[1024];
    int cmdnum;
    int quit = 0;
    int select;
    FILE *studata;
    
    head.next = head.pre = &head;
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

    readfromfile(&head,studata);
    printf("|-------------------------------------------|\n");
    printf("|----Welcome to Student Database System-----|\n");
    printf("|-------------------------------------------|\n\n");
    printf("%d student have!\n",countlist(&head));

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
                showallstu(&head);
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
                tempstu.lt.pre = tempstu.lt.next = NULL;
                pos = findstu(&head,tempstu.id);
                if(NULL != pos)
                {
                    printf("This id is already exist!\n");
                    break;
                }
                stu = newstu(&tempstu);
                addstu(&head,stu);
                break;
            case CMDDEL:
                printf("please input the id you wante to delete:");
                scanf("%s",tempstu.id);
                fgets(cmd,1024,stdin);
                pos = findstu(&head,tempstu.id);
                if(NULL == pos)
                {
                    printf("not found the id!\n");
                    break;
                }
                delstu(pos);
                break;
            case CMDFIND:
                printf("please input 1 for id,2 for name:");
                scanf("%d",&select);
                fgets(cmd,1024,stdin);
                if(1 == select)
                {
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    pos = findstu(&head,tempstu.id);
                    if(NULL == pos)
                    {
                        printf("not found the id!\n");
                        break;
                    }
                    showstu((struct student *)pos);
                }
                else if(2 == select)
                {
                    printf("please input the name you want to find:");
                    scanf("%s",tempstu.name);
                    fgets(cmd,1024,stdin);
                    pos = head.next;
                    do
                    {
                        pos = findnamenext(pos,tempstu.name,&head);
                        if(NULL != pos)
                        {
                            showstu((struct student *)pos);
                            pos = pos->next;
                        }
                    }while(NULL != pos);
                    break;
                }
            case CMDSAVE:
                save(&head,studata);
                break;
            case CMDREVERSE:
               // reverse(&head);
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
