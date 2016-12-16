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

struct student* findstu(struct student *root,char *id)
{
    struct student *pos;
    pos = root;
    
    while(NULL != pos)
    {
        if(strcmp(id,pos->id) == 0)
        {
            break;
        }
        else if(strcmp(id,pos->id) > 0)
        {
            pos = pos->r;
        }
        else if(strcmp(id,pos->id) < 0)
        {
            pos = pos->l;
        }
    }
    return pos;
}

struct student* addstu(struct student *root,struct student *stu)
{
    struct student *pos;
    pos = root;

    if(NULL == root)
    {
        return stu;
    }
    while(1)
    {
        if(strcmp(stu->id,pos->id) > 0)
        {
            if(NULL == pos->r)
            {
                pos->r = stu;
                stu->p = pos;
                break;
            }
            pos = pos->r;
        }
        else
        {
            if(NULL == pos->l)
            {
                pos->l = stu;
                stu->p = pos;
                break;
            }
            pos = pos->l;
        }
    }
    return root;
}

void showone(struct student *stu)
{
    printf(" ID:%s ",stu->id);
    printf(" Name:%s ",stu->name);
    printf(" Age:%d ",(int)stu->age);
    printf(" Sex:%c ",stu->sex);
    printf("\n");
    return;
}

void showall(struct student *root)
{
    struct mystack s;
    struct myqueue q;
    initallqueue(&q);
    initallstack(&s);
    
    while(NULL != root)
    {
        pushstack(&s,root);
        root = root->l;
    }
    while(!stackisempty(&s))
    {
        root = popstack(&s);
        putqueue(&q,root);
        if(NULL != root->r)
        {
            root = root->r;
            while(NULL != root)
            {
                pushstack(&s,root);
                root = root->l;
            }
        }
    }
    while(!queueisempty(&q))
    {
        root = getqueue(&q);
        showone(root);
    }
}

void showallpre(struct student *root)
{
    struct mystack s;
    struct myqueue q;
    initallqueue(&q);
    initallstack(&s);
    
    pushstack(&s,root);
    while(!stackisempty(&s))
    {
        root = popstack(&s);
        if(NULL != root->r)
        {
            pushstack(&s,root->r);
        }
        if(NULL != root->l)
        {
            pushstack(&s,root->l);
        }
        putqueue(&q,root);
    }
    while(!queueisempty(&q))
    {
        root = getqueue(&q);
        showone(root);
    }
    return ;
}

void showallback(struct student *root)
{
    struct mystack s;
    struct myqueue q;
    struct student *tmp = root;
    initallstack(&s);
    initallqueue(&q);

    pushstack(&s,root);
    while(!stackisempty(&s))
    {
        root = popstack(&s);
        if((tmp == root->l) || (tmp == root->r) )
        {
            putqueue(&q,root);
            tmp = root;
            continue;
        }
        tmp = root;
        if((NULL == root->l) && (NULL == root->r))
        {
            putqueue(&q,root);
            continue;
        }
        pushstack(&s,root);
        if(NULL != root->r)
        {
            pushstack(&s,root->r);
        }
        if(NULL != root->l)
        {
            pushstack(&s,root->l);
        }
    }
    while(!queueisempty(&q))
    {
        root = getqueue(&q);
        showone(root);
    }
}

int findname(struct student *root,char *name,struct myqueue *q)
{
    if(NULL == root)
    {
        return 0;
    }
    findname(root->l,name,q);
    if(0 == strcmp(root->name,name))
    {
        putqueue(q,root);
    }
    findname(root->r,name,q);
    
    return 0;
}

void printname(struct student *root,char *name)
{
    if(NULL == root)
    {
        return ;
    }
    printname(root->l,name);
    if(0 == strcmp(root->name,name))
    {
        showone(root);
    }
    printname(root->r,name);
    return ;
}

struct student* findparent(struct student *root,struct student *stu)
{
    struct student *parent;
    int rt;
    parent = root;
    if(NULL == root)
    {
        return NULL;
    }
    while(NULL != parent)
    {
        rt = strcmp(stu->id,parent->id);
        if(rt > 0)
        {
            if(parent->r == stu)
            {
                break;
            }
            parent = parent->r;
        }
        if(rt < 0)
        {
            if(parent->l == stu)
            {
                break;
            }
            parent = parent->l;
        }
    }
    return parent;
}

struct student* findmin(struct student *root)
{
    if(NULL == root)
    {
        return NULL;
    }
    while(NULL != root->l)
    {
        root = root->l;
    }
    return root;
}

struct student* findmax(struct student *root)
{
    if(NULL == root)
    {
        return NULL;
    }
    while(NULL != root->r)
    {
        root = root->r;
    }
    return root;
}

struct student* findnext(struct student *stu)
{
    struct student *next;
    if(NULL != stu->r)
    {
        return findmin(stu->r);
    }
    else
    {
        next = stu;
        while(NULL != next->p)
        {
            if(stu == next->p->l)
            {
                break;
            }
            next = next->p;
        }
    }
    return next->p;
}

struct student* findpre(struct student *stu)
{
    struct student *pre;
    if(NULL != stu->l)
    {
        pre = findmax(stu->l);
    }
    else if(NULL == stu->l)
    {
        pre = stu;
        while(NULL != pre)
        {
            if(strcmp(pre->p->id,stu->id) < 0)
            {
                break;
            }
            pre = pre->p;
        }
        pre = pre->p;
    }
    return pre;
}

static struct student* _delstu(struct student *root,struct student *stu)
{
    struct student *parent = root;
    struct student *stuchild = (NULL == stu->l?stu->r:stu->l);
    if(NULL == root)
    {
        return NULL;
    }
    if(root == stu)
    {
        root = stuchild;
    }
    
    parent = findparent(root,stu);
    
    if(NULL != parent)
    {
        (stu == parent->l)?(parent->l = stuchild):(parent->r = stuchild);
    }
    return root;
}

struct student* delstu(struct student *root,struct student *stu)
{
    struct student *parent;
    struct student *ptmp;

    if(NULL == root)
    {
        return NULL;
    }
    if((NULL == stu->l)||(NULL == stu->r))
    {
        root = _delstu(root,stu);
        free(stu);
        stu = NULL;
    }
    else
    {
        ptmp = findmin(stu->r);
        stu->r = _delstu(stu->r,ptmp);
        strcmp(stu->id,ptmp->id);
        strcmp(stu->name,ptmp->name);
        stu->age = ptmp->age;
        stu->sex = ptmp->sex;
        free(ptmp);
        ptmp = NULL;
    }
    return root;
}

int transplant(struct student *root,struct student *d,struct student *s)
{
    if(NULL == d->p)
    {
        root = s;
    }
    else if(d == d->p->l)
    {
        d->p->l = s;
    }
    else
    {
        d->p->r = s;
    }
    if(NULL != s)
    {
        s->p = d->p;
    }
    return ;
}

struct student* treedel(struct student *root,struct student *stu)
{
    struct student *ptmp;

    if(NULL == stu->l)
    {
        transplant(root,stu,stu->r);
    }
    else if(NULL == stu->r)
    {
        transplant(root,stu,stu->l);
    }
    else
    {
        ptmp = findmin(stu->r);
        if(stu != ptmp->p)
        {
            transplant(root,ptmp,ptmp->r);
            ptmp->r = stu->r;
            ptmp->r->p = ptmp;
        }
        transplant(root,stu,ptmp);
        ptmp->l = stu->l;
        ptmp->l->p = ptmp;
    }
    return root;
}

int count(struct student *root)
{
    if(NULL == root)
    {
        return 0;
    }
    else
    {
        return count(root->l)+count(root->r)+1;
    }
}

int writeone(struct student *root,FILE *studata)
{
    fwrite(root,sizeof(struct student),1,studata);
    return 0;
}

int writeall(struct student *root,FILE *studata)
{
    if(NULL == root)
    {
        return 0;
    }
    writeone(root,studata);
    writeall(root->l,studata);
    writeall(root->r,studata);
    return 0;
}

int save(struct student *root,FILE *studata)
{
    int num;
    fseek(studata,0,SEEK_SET);
    num = count(root);
    fwrite(&num,sizeof(int),1,studata);
    writeall(root,studata);
    return num;
}

struct student* readfromfile(struct student *root,FILE *studata)
{
    int i;
    struct student tempstu;
    struct student *stu;
    int num;
    
    i = fread(&num,sizeof(int),1,studata);
    if(0 == i)
    {
        return root;
    }

    for(i=0;i<num;i++)
    {
        fread(&tempstu,sizeof(struct student),1,studata);
        tempstu.p = tempstu.l = tempstu.r = NULL;
        stu = newstu(&tempstu);
        root = addstu(root,stu);
    }
    return root;
}

int freeall(struct student *root)
{
    if(NULL == root)
    {
        return;
    }
    free(root->l);
    free(root->r);
    free(root);
    return ;
}

struct student* reverse(struct student *root)
{
    struct student *ptmp=NULL;
    
    if(NULL == root)
    {
        return NULL;
    }
    ptmp = root->l;
    root->l = reverse(root->r);
    root->r = reverse(ptmp);

    return root;
}
