#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

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

struct student* findstu(struct student *phead,char *id)
{
    int i;
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

struct student* addstu(struct student *phead,struct student *stu)
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

void showstu(struct student *stu)
{
    printf(" ID:%s ",stu->id);
    printf(" Name:%s ",stu->name);
    printf(" Age:%d ",(int)stu->age);
    printf(" Sex:%c ",stu->sex);
    printf("\n");
    return;
}

void showallstu(struct student *phead)
{
    while(NULL != phead)
    {
        showstu(phead);
        phead = phead->next;
    }
    return;
}

struct student* findnamenext(struct student *phead,char *name)
{
    while((NULL != phead) && (0 != strcmp(phead->name,name)))
    {
        phead = phead->next;
    }
    return phead;
}

struct student* delstu(struct student *phead,struct student *stu)
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

int save(struct student *phead,FILE *studata)
{
    int num;
    fseek(studata,0,SEEK_SET);
    num = countlist(phead);
    fwrite(&num,sizeof(int),1,studata);
    while(NULL != phead)
    {
        fwrite(phead,sizeof(struct student),1,studata);
        phead = phead->next;
    }
    return num;
}

struct student* readfromfile(FILE *studata)
{
    int i;
    struct student *phead = NULL;
    struct student tempstu;
    struct student *stu;
    int num;
    
    i = fread(&num,sizeof(int),1,studata);
    if(0 == i)
    {
        return phead;
    }

    for(i=0;i<num;i++)
    {
        fread(&tempstu,sizeof(struct student),1,studata);
        tempstu.next = NULL;
        stu = newstu(&tempstu);
        phead = addstu(phead,stu);
    }
    return phead;
}

int freeall(struct student *phead)
{
    struct student *pnext;
    while(NULL != phead)
    {
        pnext = phead->next;
        free(phead);
        phead = pnext;
    }
    return ;
}

struct student* reverse(struct student *phead)
{
    struct student *newhead=NULL;
    struct student *temp=NULL;
    
    while(NULL != phead)
    {
        temp = phead;
        phead = phead->next;
        temp->next = newhead;
        newhead = temp;
    }
    
    return newhead;
}
