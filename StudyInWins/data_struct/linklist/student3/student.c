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

struct list* findstu(struct list *phead,char *id)
{
    int i;
    struct list *pos;
    struct student *ptemp;

    list_for_each(pos,phead)
    {
        ptemp = container_of(pos,struct student,lt);
        i = strcmp(ptemp->id,id);
        if(i > 0)
        {
            break;
        }
        if(0 == i)
        {
            return pos;
        }
    }
    return NULL;
}

int addstu(struct list *phead,struct student *stu)
{
    struct list *pos;
    struct student *ptemp;

    list_for_each(pos,phead)
    {
        ptemp = container_of(pos,struct student,lt);
        if(strcmp(ptemp->id,stu->id) > 0)
        {
            break;
        }
    }

    add_list_pre(pos,&stu->lt);

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

void showallstu(struct list *phead)
{
    struct list *pos;
    struct student *ptemp;

    list_for_each(pos,phead)
    {
        ptemp = container_of(pos,struct student,lt);
        showstu(ptemp);
    }
    return;
}

struct list* findnamenext(struct list *pos,char *name,struct list *phead)
{
    struct student *temp;
    for(;pos!=phead;pos=pos->next)
    {
        temp = container_of(pos,struct student,lt);
        if(strcmp(temp->name,name) == 0)
        {
            return pos;
        }
    }
    return NULL;
}

int delstu(struct list *pos)
{
    struct student *tempstu;
    tempstu = container_of(pos,struct student,lt);
    del_list(pos);
    free(tempstu);

    return;
}

int countlist(struct list *phead)
{
    int num = 0;
    struct list *pos;
    for(pos=phead->next;pos!=phead;pos=pos->next)
    {
        num++;
    }
    return num;
}

int save(struct list *phead,FILE *studata)
{
    int num;
    struct student *stu;
    struct list *pos;
    fseek(studata,0,SEEK_SET);
    num = countlist(phead);
    fwrite(&num,sizeof(int),1,studata);
    for(pos=phead->next;pos!=phead;pos=pos->next)
    {
        stu = (struct student *)pos;
        fwrite(stu,sizeof(struct student),1,studata);
    }
    return num;
}

int readfromfile(struct list *phead,FILE *studata)
{
    int i;
    struct list *pos;
    struct student tempstu;
    struct student *stu;
    int num;
    
    i = fread(&num,sizeof(int),1,studata);
    if(0 == i)
    {
        return i;
    }

    for(i=0;i<num;i++)
    {
        fread(&tempstu,sizeof(struct student),1,studata);
        tempstu.lt.next = NULL;
        tempstu.lt.pre  = NULL;
        stu = newstu(&tempstu);
        addstu(phead,stu);
    }
    return i;
}

int freeall(struct list *phead)
{
    struct list *pos;
    struct list *temp;
    struct student *stu;

    for(pos=phead->next;pos!=phead;pos=temp)
    {
        temp = pos->next;
        stu = (struct student *)pos;
        free(pos);
    }
    return ;
}

