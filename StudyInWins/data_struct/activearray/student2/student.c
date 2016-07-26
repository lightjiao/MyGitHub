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

static void spacerise(struct allstu *all)
{
    struct student **p;
    p = malloc(2 * all->space * sizeof(struct student *));
    if(NULL == p)
    {
        printf("spacerise fail!\n");
        return ;
    }
    
    memcpy(p,all->pstu,all->num*sizeof(struct student *));
    free(all->pstu);
    all->pstu = p;
    all->space *= 2;
    return;
}

struct student** findstu(struct allstu *all,char *id)
{
    int i;
    int rt;

    for(i=0;i<all->num;i++)
    {
        rt = strcmp(all->pstu[i]->id,id);
        if(0 == rt)
        {
            return &all->pstu[i];
        }
        if(0 < rt)
        {
            break;
        }
    }

    return NULL;
}

static struct student** findpose(struct allstu *all,char *id)
{
    int i;
    
    for(i=0;i<all->num;i++)
    {
        if(0 < strcmp(all->pstu[i]->id,id))
        {
            break;
        }
    }

    return &all->pstu[i];
}

void addstu(struct allstu *all,struct student *stu)
{
    struct student **p;
    int i;
    int n;

    if(all->num == all->space)
    {
        spacerise(all);
    }
    
    p = findpose(all,stu->id);
    
    n = p - all->pstu;
    for(i=all->num;i>n;i--)
    {
        all->pstu[i] = all->pstu[i-1];
    }
    all->pstu[i] = stu;
    
    all->num++;

    return ;
}

int initall(struct allstu *all)
{
    all->space = 8;
    all->pstu == NULL;
    all->pstu = malloc(all->space*sizeof(struct student *));
    if(NULL == all->pstu)
    {
        printf("initall fail!\n");
        return -1;
    }
    memset(all->pstu,0,all->space*sizeof(struct student *));
    all->num = 0;

    return 0;
}

void showstu(struct student *stu)
{
    printf("  ID:%s\n",stu->id);
    printf("Name:%s\n",stu->name);
    printf(" Age:%d\n",(int)stu->age);
    printf(" Sex:%c\n",stu->sex);
    printf("\n");
    return;
}

void showallstu(struct allstu *all)
{
    int i;
    for(i=0;i<all->num;i++)
    {
        showstu(all->pstu[i]);
    }
    return;
}

struct student** findnamenext(struct allstu *all,char *name,struct student **pre)
{
    pre = (NULL == pre)?all->pstu:pre+1;
    for(pre;pre<all->pstu+all->num;pre++)
    {
        if(0 == strcmp((*pre)->name,name))
        {
            return pre;
        }
    }
    return NULL;
}

int delstu(struct allstu *all,struct student **stu)
{
    int i;

    i = stu - all->pstu;
    for(;i<all->num-1;i++)
    {
         all->pstu[i] = all->pstu[i+1];
    }
    free(*stu);
    stu = NULL;
    all->num --;
    return ;
}


int save(struct allstu *all,FILE *studata)
{
    int i;
    fseek(studata,0,SEEK_SET);
    fwrite(&all->num,sizeof(int),1,studata);
    for(i=0;i<all->num;i++)
    {
        fwrite(all->pstu[i],sizeof(struct student),1,studata);
    }
    return all->num;
}

int readfromfile(struct allstu *all,FILE *studata)
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
        stu = newstu(&tempstu);
        addstu(all,stu);
    }
    return num;
}
