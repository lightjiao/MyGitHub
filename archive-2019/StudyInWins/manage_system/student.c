#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "student.h"


int savestudata(struct student *stu,int pos,FILE *studata)
{
    fseek(studata,pos*sizeof(struct student),SEEK_SET);
    fwrite(stu,sizeof(struct student),1,studata);

    return 0;
}

int readstudata(struct student *stu,int pos,FILE *studata)
{
    fseek(studata,pos*sizeof(struct student),SEEK_SET);
    fread(stu,sizeof(struct student),1,studata);

    return 0;
}

int showonestu(int pos,FILE *studata)
{
    struct student tmpstu;
    readstudata(&tmpstu,pos,studata);
    printf("     ID:%s ",tmpstu.id);
    printf("Name:%s ",tmpstu.name);
    printf("Age:%d ",tmpstu.age);
    printf("Sex:%c ",tmpstu.sex);
    printf("\n");

    return 0;
}

int showallbyname(struct namehash *nhash,FILE *studata)
{
    int index;
    struct list *pos;
    struct list *phead;
    struct namenode *ptmp;

    for(index=0;index<997;index++)
    {
        phead = &nhash->stuname[index];
        list_for_each(pos,phead)
        {
            ptmp = container_of(pos,struct namenode,lt);
            showonestu(ptmp->pos,studata);
        }
    }
}


////////////////////////////////////////////////////////////////////////////// the showall


static char *cmdstring[] =
{
    "n",
    "p",
    "page",
    "q",
};
 
enum
{
    CMDNEXT,
    CMDPRE,
    CMDPAGE,
    CMDQUIT,
    CMDNONE,
};

static int getcmd(char *cmd)
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


static int showpage(struct list *page[],int pagenow,struct idhash *idh,FILE *studata)
{
    int numperpage = 0;
    int index;

    struct list *pos;
    struct list *phead;
    struct idnode *ptmp;

    ptmp = container_of(page[pagenow],struct idnode,lt);
    index = hashid(ptmp->id);
    phead = &idh->stuid[index];
    
    for(pos=page[pagenow];pos!=phead;pos=pos->next)
    {
        ptmp = container_of(pos,struct idnode,lt);
        showonestu(ptmp->pos,studata);
        numperpage++;
        if(numperpage >= 20)
        {
            break;
        }
    }

    while(numperpage < 20)
    {
        index++;
        if(index >= 997)
        {
            break;
        }
        
        phead = &idh->stuid[index];
        list_for_each(pos,phead)
        {
            ptmp = container_of(pos,struct idnode,lt);
            showonestu(ptmp->pos,studata);
            numperpage++;
            if(numperpage >= 20)
            {
                break;
            }
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////  THE MAIN PART OF SHOWALL  //////////////////////////////////////////////////

static int showmenue()
{
    system("clear");
    printf("|*******************************************|\n");
    printf("|    Welcome to Student Database System     |\n");
    printf("|*******************************************|\n\n");
    return 0;
}


int showallbyid(struct idhash *idh,FILE *studata)
{
    int i,j;
    struct list *pos;
    struct list *phead;
    struct idnode *ptmp;

    int stunumber;
    int pagenumber;
    int numperpage = 0;
    int pagenow = 0;
    int jumppage = 0;

    int quit = 0;
    char cmd[1024];
    int cmdnum;

////////////////////////////////////////////////////// CREAT THE PAGE 

    stunumber = countidhash(idh);
    
    if(0 != (stunumber%20))
    {
        pagenumber = (stunumber/20) + 1;
    }
    else
    {
        pagenumber = (stunumber/20);
    }
    
    //struct list* page[pagenumber];
    struct list* page = (struct list*)malloc(pagenumber * sizeof(struct list));

    for(i=0,j=0;i<997;i++)
    {
        phead = &idh->stuid[i];
        list_for_each(pos,phead)
        {
            if(0 == (numperpage%20))
            {
                page[j] = pos;
                j++;
            }
            numperpage++;
        }
    }
 
    showmenue();
    showpage(page,pagenow,idh,studata);       //////////// SHOW PAGE 0
    printf("\n            ----- %d/%d -----\n",pagenow +1,pagenumber);


//////////////////////////////////////////////////// THE OPERATION OF SHOW

    while(0 == quit)
    {
        printf("\n     Change Page Command:");
        fgets(cmd,1024,stdin);
        cmd[strlen(cmd)-1] = 0;
        cmdnum = getcmd(cmd);
        
        switch(cmdnum)
        {
            case CMDNEXT:
                pagenow++;
                if((pagenow +1 < 1) || (pagenow +1 > pagenumber) )
                {
                    printf("     No More Next!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                    pagenow--;
                }
                showmenue();
                showpage(page,pagenow,idh,studata);
                printf("\n            ----- %d/%d -----\n",pagenow +1,pagenumber);
                break;

            case CMDPRE:
                pagenow--;
                if((pagenow +1 < 1) || (pagenow +1 > pagenumber) )
                {
                    printf("     No More Preview!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                    pagenow++;
                }
                showmenue();
                showpage(page,pagenow,idh,studata);       
                printf("\n            ----- %d/%d -----\n",pagenow +1,pagenumber);
                break;

            case CMDPAGE:
                printf("     Please Input The Page You Want Show:");
                scanf("%d",&jumppage);
                fgets(cmd,1024,stdin);
                jumppage--;
                if((jumppage +1 < 1) || (jumppage +1 > pagenumber) )
                {
                    printf("     Not Right Page Num!(Press Any Key To Continue...)");
                    fgets(cmd,1024,stdin);
                }
                else
                {
                    pagenow = jumppage;
                }
                showmenue();
                showpage(page,pagenow,idh,studata);       
                printf("\n            ----- %d/%d -----\n",pagenow +1 ,pagenumber);
                break;

            case CMDQUIT:
                quit = 1;
                printf("     Quit Show Part Successful!\n");
                break;

            default:
                showmenue();
                showpage(page,pagenow,idh,studata);       
                printf("\n            ----- %d/%d -----\n",pagenow +1 ,pagenumber);
                printf("|-------------- command list ---------------|\n");
                printf("|                                           |\n");
                printf("|        n:for next page!                   |\n");
                printf("|        p:for front page!                  |\n");
                printf("|        page:jump to the page you want!    |\n");
                printf("|        q:for quit!                        |\n");
                printf("|                                           |\n");
                printf("|-------------------------------------------|\n");
                break;
        }

    }

    return 0;
}











