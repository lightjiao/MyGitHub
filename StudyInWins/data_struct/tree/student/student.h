
#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "stack.h"
#include "queue.h"

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *p;
    struct student *l,*r;
};


extern void showone(struct student *stu);
extern void showall(struct student *root);
extern struct student* addstu(struct student *root,struct student *stu);
extern struct student* findstu(struct student *root,char *id);
extern struct student* delstu(struct student *root,struct student *stu);
extern struct student* readfromfile(struct student *root,FILE *studata);
extern struct student* newstu(struct student*);
extern struct student* reverse(struct student*);
extern int save(struct student *root,FILE *studata);
extern int count(struct student *root);
extern int freeall(struct student*);
extern struct student* findpre(struct student *stu);
extern struct student* findnext(struct student *stu);
extern struct student* treedel(struct student *root,struct student *stu);
extern int findname(struct student *root,char *name,struct myqueue *s);
extern void showallpre(struct student *root);

#endif
