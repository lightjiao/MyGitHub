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
    struct student *root = NULL;
    struct student *pos;
    struct student tempstu;
    struct student *stu;
    struct mystack s;
    struct myqueue q;

    int tempage;
    char cmd[1024];
    int cmdnum;
    int quit = 0;
    int select;
    FILE *studata;

    initallstack(&s);
    initallqueue(&q);
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
    
    root = readfromfile(root,studata);
    printf("|-------------------------------------------|\n");
    printf("|----Welcome to Student Database System-----|\n");
    printf("|-------------------------------------------|\n\n");
    printf("%d student have!\n",count(root));

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
                showall(root);
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
                tempstu.p = tempstu.l = tempstu.r = NULL;
                pos = findstu(root,tempstu.id);
                if(NULL != pos)
                {
                    printf("This id is already exist!\n");
                    break;
                }
                stu = newstu(&tempstu);
                root = addstu(root,stu);
                break;
            case CMDDEL:
                printf("please input the id you wante to delete:");
                scanf("%s",tempstu.id);
                fgets(cmd,1024,stdin);
                pos = findstu(root,tempstu.id);
                if(NULL == pos)
                {
                    printf("not found the id!\n");
                    break;
                }
                root = treedel(root,pos);
                break;
            case CMDFIND:
                printf("please input \n1 for id;\n2 for name;\n3 for next;\n4 for pre;\n");
                scanf("%d",&select);
                fgets(cmd,1024,stdin);
                if(1 == select)
                {
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    pos = findstu(root,tempstu.id);
                    if(NULL == pos)
                    {
                        printf("not found the id!\n");
                        break;
                    }
                    showone(pos);
                }
                else if(2 == select)
                {
                    printf("please input the name you want to find:");
                    scanf("%s",tempstu.name);
                    fgets(cmd,1024,stdin);
                    findname(root,tempstu.name,&q);
                    while(!queueisempty(&q))
                    {
                        pos = getqueue(&q);
                        showone(pos);
                    }
                    break;
                }
                else if(3 == select)
                {
                    printf("please input the id who you want to find the next:");
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    pos = findstu(root,tempstu.id);
                    if(NULL == pos)
                    {
                        printf("not found the id!\n");
                        break;
                    }
                    showone(pos);
                    pos = findnext(pos);
                    if(NULL == pos)
                    {
                        printf("not found the next!\n");
                        break;
                    }
                    showone(pos);
                }
                else if(4 == select)
                {
                    printf("please input the id who you want to find the pre:");
                    scanf("%s",tempstu.id);
                    fgets(cmd,1024,stdin);
                    pos = findstu(root,tempstu.id);
                    if(NULL == pos)
                    {
                        printf("not found the id!\n");
                        break;
                    }
                    showone(pos);
                    pos = findpre(pos);
                    if(NULL == pos)
                    {
                        printf("not found the pre!\n");
                        break;
                    }
                    showone(pos);
                }
                break;
            case CMDSAVE:
                save(root,studata);
                break;
            case CMDREVERSE:
                root = reverse(root);
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
    freeall(root);
    root = NULL;
    return ;
}
