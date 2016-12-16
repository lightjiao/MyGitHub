
#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"

struct idnode
{
    char id[20];
    unsigned int pos;
    struct list lt;
};

struct idhash
{
    struct list stuid[997];
};


struct namenode
{
    char name[20];
    unsigned int pos;
    struct list lt;
};

struct namehash
{
    struct list stuname[997];
};

struct blankpos
{
    int *pos;
    unsigned int space;
    unsigned int num;
};


///////////////////////////////////////////////////////// THE HASH PART :INITALL,HASH,COUNT

extern int initallidhash(struct idhash *idh);
extern int initallnamehash(struct namehash *nhash);
extern int hashid(char *id);
extern int hashname(char *name);
extern int countidhash(struct idhash *idh);


///////////////////////////////////////////////////////// HASH OF ID :NEW,FIND,ADD,DEL,SAVE,READ

extern struct idnode* newidnode(struct idnode *tmpidnode);
extern struct list* findidlist(struct list *phead,char *id);
extern struct list* findidhash(struct idhash *idh,char *id);
extern int addidlist(struct list *phead,struct idnode *stuidnode);
extern int addidhash(struct idhash *idh,struct idnode *stuidnode);
extern int delidhash(struct list *pos);
extern int saveidhash(struct idhash *idh,FILE *idhdata);
extern int readidhash(struct idhash *idh,FILE *idhdata);


///////////////////////////////////////////////////////// HASH OF NAME : NEW,FIND,ADD,DEL,SAVE,READ

extern struct namenode* newnamenode(struct namenode *tmpnamenode);
extern struct list* findnamenext(struct list *pos,char *name,struct list *phead);
extern struct list* findnamelist(struct list *phead,char *name);
extern struct list* findnamehash(struct namehash *nhash,char *name);
extern int addnamelist(struct list *phead,struct namenode *stu);
extern int addnamehash(struct namehash *nhash,struct namenode *stu);
extern int delnamehash(struct list *pos);
extern int savenamehash(struct namehash *nhash,FILE *nhashdata);
extern int readnamehash(struct namehash *nhash,FILE *nhashdata);


///////////////////////////////////////////////////////// BLANKPOS :INITALL,ADD,(INCREASE),DEL,SAVE,READ

extern int initallblankpos(struct blankpos *bpos,int space);
extern int addblankpos(struct blankpos *bpos,int pos);
extern int delblankpos(struct blankpos *bpos,int pos);
extern int saveblankpos(struct blankpos *bpos,FILE *bposdata);
extern int readblankpos(struct blankpos *bpos,FILE *bposdata);


////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
