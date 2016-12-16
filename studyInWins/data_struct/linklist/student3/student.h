
#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "list.h"

struct student
{
    char id[20];
    char name[20];
    struct list lt;
    char age;
    char sex;
};

extern void showstu(struct student *stu);
extern void showallstu(struct list *phead);
extern int addstu(struct list *phead,struct student *stu);
extern int delstu(struct list *pos);
extern struct list* findstu(struct list *phead,char *id);
extern struct list* findnamenext(struct list *pos,char *name,struct list *phead);
extern struct student* newstu(struct student*);
extern int save(struct list *phead,FILE *studata);
extern int countlist(struct list *phead);
extern int readfromfile(struct list *,FILE *);

#endif
