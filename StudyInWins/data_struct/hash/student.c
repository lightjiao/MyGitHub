#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


int initallidhash(struct idhash *allstu)
{
    int i;
    for(i=0;i<10;i++)
    {
        allstu->allstu[i] = NULL;
    }
    return 0;
}

int hash(char *id)
{
    return id[strlen(id)-1] - '0';
}

struct student* newstu(struct student *tempstu)
{
    struct student *stu;
    stu = malloc(sizeof(struct student));
    if(NULL == stu)
    {
        printf("new student malloc fail!\n");
        return NULL;
    }
    *stu = *tempstu;
    return stu;
}

struct student* findstu(struct idhash *allstu,char *id)
{
    int i;
    int index = hash(id);
    struct student *phead = allstu->allstu[index];

    for(;NULL != phead;phead = phead->next)
    {
        i = strcmp(phead->id,id);
        if(i > 0)
        {
            break;
        }
        if(0 == i)
        {
            return phead;
        }
    }
    return NULL;
}


struct student* add2hash(struct student *phead,struct student *stu)
{
    struct student *pre = NULL;
    struct student *pnext = NULL;

    if(NULL == phead)
    {
        phead = stu;
    }
    else if(strcmp(phead->id,stu->id) > 0)
    {
        stu->next = phead;
        phead = stu;
    }
    else
    {
        pre = phead;
        pnext = phead->next;
        while(NULL != pnext)
        {
            if(strcmp(pnext->id,stu->id) > 0)
            {
                break;
            }
            pre = pnext;
            pnext = pnext->next;
        }
        pre->next = stu;
        stu->next = pnext;
    }
    return phead;
}

int addstu(struct idhash *allstu,struct student *stu)
{
    int i = hash(stu->id);
    allstu->allstu[i] = add2hash(allstu->allstu[i],stu);
    return 0;
}


void showstu(struct student *stu)
{
    printf(" ID:%s ",stu->id);
    printf(" Name:%s ",stu->name);
    printf(" Age:%d ",(int)stu->age);
    printf(" Sex:%c ",stu->sex);
    printf("\n");
    return;
}

void showallstu(struct idhash *allstu)
{
    int i;
    struct student *phead;
    for(i=0;i<10;i++)
    {
        phead = allstu->allstu[i];
        while(NULL != phead)
        {
            showstu(phead);
            phead = phead->next;
        }
    }
    return;
}
/*
struct student* findnamenext(struct student *phead,char *name)
{
    while((NULL != phead) && (0 != strcmp(phead->name,name)))
    {
        phead = phead->next;
    }
    return phead;
}
*/
struct student* del2hash(struct student *phead,struct student *stu)
{
    struct student *pre;
    struct student *pnext;
    
    if(NULL == phead)
    {
        return NULL;
    }
    else if(phead == stu)
    {
        phead = phead->next;
    }
    else
    {
        pre = phead;
        pnext = phead->next;
        while(NULL != pnext)
        {
            if(pnext == stu)
            {
                break;
            }
            pre = pnext;
            pnext = pnext->next;
        }
        pre->next = pnext;
    }
    free(stu);
    return phead;
}

int delstu(struct idhash *allstu,struct student *stu)
{
    int i = hash(stu->id);
    allstu->allstu[i] = del2hash(allstu->allstu[i],stu);
    return ;
}

int countlist(struct student *phead)
{
    int num = 0;
    while(NULL != phead)
    {
        num++;
        phead = phead->next;
    }
    return num;
}

int count(struct idhash *allstu)
{
    int num = 0;
    int i;
    for(i=0;i<10;i++)
    {
        num = num + countlist(allstu->allstu[i]);
    }
    return num;
}

int save(struct idhash *allstu,FILE *studata)
{
    int num;
    int i;
    struct student *phead;
    
    fseek(studata,0,SEEK_SET);

    num = count(allstu);
    fwrite(&num,sizeof(int),1,studata);
    
    for(i=0;i<10;i++)
    {
        phead = allstu->allstu[i];
        while(NULL != phead)
        {
            fwrite(phead,sizeof(struct student),1,studata);
            phead = phead->next;
        }
    }
    return num;
}

int readfromfile(struct idhash *allstu,FILE *studata)
{
    int i;
    struct student tempstu;
    struct student *stu;
    int num;
    
    i = fread(&num,sizeof(int),1,studata);
    if(0 == i)
    {
        return 0;
    }

    for(i=0;i<num;i++)
    {
        fread(&tempstu,sizeof(struct student),1,studata);
        tempstu.next = NULL;
        stu = newstu(&tempstu);
        addstu(allstu,stu);
    }
    return num;
}


