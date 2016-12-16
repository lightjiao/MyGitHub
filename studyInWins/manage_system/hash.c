#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hash.h"

///////////////////////////////////////////////////// THE HASH PART :INITALL,HASH,COUNT

int initallidhash(struct idhash *idh)
{
    int i;
    for(i=0;i<997;i++)
    {
        idh->stuid[i].next = idh->stuid[i].pre = &idh->stuid[i];
    }
    return 0;
}

int initallnamehash(struct namehash *nhash)
{
    int i;
    for(i=0;i<997;i++)
    {
        nhash->stuname[i].next = nhash->stuname[i].pre = &nhash->stuname[i];
    }
    return 0;
}

int hashid(char *id)
{
    return atoi(id)%997;
}

int hashname(char *name)
{
    int index = 0;
    int i;
    int len = strlen(name);

    for(i=0;i<len;i++)
    {
        index = index*10 + (name[i] - 'a');
    }
    return index%997;
}

int countidhash(struct idhash *idh)
{
    int stunumber = 0;
    int index;
    struct list *pos;
    struct list *phead;

    for(index=0;index<997;index++)
    {
        phead = &idh->stuid[index];
        list_for_each(pos,phead)
        {
            stunumber++;
        }
    }
    return stunumber;
}

//////////////////////////////////////////////////////// HASH OF ID: NEW,FIND,ADD,DEL,SAVE,READ

struct idnode* newidnode(struct idnode *tmpidnode)
{
    struct idnode *stuidnode;
    stuidnode = malloc(sizeof(struct idnode));
    if(NULL == stuidnode)
    {
        printf("new idnode failed!\n");
        return NULL;
    }

    *stuidnode = *tmpidnode;

    return stuidnode;
}

struct list* findidlist(struct list *phead,char *id)
{
    struct list *pos;
    struct idnode *ptmp;
    int rt;

    list_for_each(pos,phead)
    {
        ptmp = container_of(pos,struct idnode,lt);
        rt = strcmp(ptmp->id,id);
        if(rt > 0)
        {
            break;
        }
        if(rt == 0)
        {
            return pos;
        }
    }
    return NULL;
}

struct list* findidhash(struct idhash *idh,char *id)
{
    int index = hashid(id);
    struct list *pos;
    
    pos = findidlist(&idh->stuid[index],id);
    
    return pos;
}

int addidlist(struct list *phead,struct idnode *stuidnode)
{
    struct list *pos;
    struct idnode *ptmp;

    list_for_each(pos,phead)
    {
        ptmp = container_of(pos,struct idnode,lt);
        if(strcmp(ptmp->id,stuidnode->id) > 0)
        {
            break;
        }
    }

    add_list_pre(pos,&stuidnode->lt);

    return 0;
}

int addidhash(struct idhash *idh,struct idnode *stuidnode)
{
    int index = hashid(stuidnode->id);
    
    addidlist(&idh->stuid[index],stuidnode);

    return 0;
}

int delidhash(struct list *pos)
{
    struct idnode *ptmp;

    ptmp = container_of(pos,struct idnode,lt);
    del_list(pos);
    free(ptmp);

    return 0;
}

int saveidhash(struct idhash *idh,FILE *idhdata)
{
    int i;
    struct list *pos;
    struct list *phead;
    struct idnode *ptmp;

    fseek(idhdata,0,SEEK_SET);
    for(i=0;i<997;i++)
    {
        phead = &idh->stuid[i];
        list_for_each(pos,phead)
        {
            ptmp = container_of(pos,struct idnode,lt);
            fwrite(ptmp,sizeof(struct idnode),1,idhdata);
        }
    }

    return 0;
}

int readidhash(struct idhash *idh,FILE *idhdata)
{
    struct idnode tmpidnode;
    struct idnode *stuidnode;
    int readnum = 0;

    fseek(idhdata,0,SEEK_SET);
    while(1)
    {
        readnum = fread(&tmpidnode,sizeof(struct idnode),1,idhdata);
        if(0 == readnum)
        {
            break;
        }
        
        stuidnode = newidnode(&tmpidnode);
        addidhash(idh,stuidnode);
    }
    return 0;
}


/////////////////////////////////////////////////////// HASH OF NAME :NEW,FIND,ADD,DEL,SAVE,READ

struct namenode* newnamenode(struct namenode *tmpnamenode)
{
    struct namenode *stunamenode;
    stunamenode = malloc(sizeof(struct namenode));
    if(NULL == stunamenode)
    {
        printf("new stu namenode failed!\n");
        return NULL;
    }

    *stunamenode = *tmpnamenode;
    return stunamenode;
}

struct list* findnamenext(struct list *pos,char *name,struct list *phead)
{
    struct namenode *tmpnamenode;
    for(;pos!=phead;pos=pos->next)
    {
        tmpnamenode = container_of(pos,struct namenode,lt);
        if(0 == strcmp(tmpnamenode->name,name))
        {
            return pos;
        }
    }
    return NULL;
}

struct list* findnamelist(struct list *phead,char *name)
{
    struct list *pos;
    struct namenode *ptmp;
    int rt;

    list_for_each(pos,phead)
    {
        ptmp = container_of(pos,struct namenode,lt);
        rt = strcmp(ptmp->name,name);
        if(rt > 0)
        {
            break;
        }
        if(rt == 0)
        {
            return pos;
        }
    }
    return NULL;
}

struct list* findnamehash(struct namehash *nhash,char *name)
{
    int index = hashname(name);
    struct list *pos;
    
    pos = findnamelist(&nhash->stuname[index],name);
    
    return pos;
}

int addnamelist(struct list *phead,struct namenode *stunamenode)
{
    struct list *pos;
    struct namenode *ptmp;

    list_for_each(pos,phead)
    {
        ptmp = container_of(pos,struct namenode,lt);
        if(strcmp(ptmp->name,stunamenode->name) > 0)
        {
            break;
        }
    }

    add_list_pre(pos,&stunamenode->lt);

    return 0;
}

int addnamehash(struct namehash *nhash,struct namenode *stunamenode)
{
    int index = hashname(stunamenode->name);
    
    addnamelist(&nhash->stuname[index],stunamenode);

    return 0;
}

int delnamehash(struct list *pos)
{
    struct namenode *ptmp;
    ptmp = container_of(pos,struct namenode,lt);
    del_list(pos);
    free(ptmp);

    return 0;
}

int savenamehash(struct namehash *nhash,FILE *nhashdata)
{
    int i;
    struct list *pos;
    struct list *phead;
    struct namenode *ptmp;

    for(i=0;i<997;i++)
    {
        phead = &nhash->stuname[i];
        list_for_each(pos,phead)
        {
            ptmp = container_of(pos,struct namenode,lt);
            fwrite(ptmp,sizeof(struct namenode),1,nhashdata);
        }
    }
    return 0;
}

int readnamehash(struct namehash *nhash,FILE *nhashdata)
{
    struct namenode tmpnamenode;
    struct namenode *stunamenode;
    int readnum = 0;

    fseek(nhashdata,0,SEEK_SET);
    while(1)
    {
        readnum = fread(&tmpnamenode,sizeof(struct namenode),1,nhashdata);
        if(0 == readnum)
        {
            break;
        }
        stunamenode = newnamenode(&tmpnamenode);
        if(NULL == stunamenode)
        {
            continue;
        }
        addnamehash(nhash,stunamenode);
    }
    return 0;
}


/////////////////////////////////////////////////////////// BLANK POS :INITALL,ADD,(INCREASE),DEL,SAVE,READ

int initallblankpos(struct blankpos *bpos,int space)
{
    bpos->pos = malloc(space*sizeof(int));
    if(NULL == bpos->pos)
    {
        printf("blankpos initall malloc failed!\n");
        return -1;
    }
    bpos->space = space;
    bpos->num = 0;

    return 0;
}

int increaseblankpos(struct blankpos *bpos)
{
    int *p;
    p = malloc(bpos->space*2*sizeof(int));
    if(NULL == p)
    {
        printf("increase blankpos failed!\n");
        return -1;
    }
    
    memcpy(p,bpos->pos,bpos->num*sizeof(int));
    free(bpos->pos);
    bpos->pos = p;
    bpos->space *= 2;

    return 0;
}

int addblankpos(struct blankpos *bpos,int pos)
{
    if(bpos->num == bpos->space)
    {
        if(increaseblankpos(bpos))
        {
            return -1;
        }
    }
    bpos->pos[bpos->num] = pos;
    bpos->num++;

    return 0;
}

int saveblankpos(struct blankpos *bpos,FILE *bposdata)
{
    int i;
    fseek(bposdata,0,SEEK_SET);
    fwrite(&bpos->num,sizeof(int),1,bposdata);

    for(i=0;i<bpos->num;i++)
    {
        fwrite(&bpos->pos[i],sizeof(int),1,bposdata);
    }
    return 0;
}

int readblankpos(struct blankpos *bpos,FILE *bposdata)
{
    int readnum;
    int space = 4;

    fseek(bposdata,0,SEEK_SET);
    readnum = fread(&space,sizeof(int),1,bposdata);
    initallblankpos(bpos,space);
    if(0 == readnum)
    {
        return 0;
    }
    fread(bpos->pos,sizeof(int),space,bposdata);
    bpos->num = space;
    return 0;
}





























