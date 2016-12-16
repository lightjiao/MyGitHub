
#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *pre;
    struct student *next;
};


extern void showstu(struct student *stu);
extern void showallstu(struct student *phead);
extern struct student* addstu(struct student *phead,struct student *stu);
extern struct student* findstu(struct student *phead,char *id);
extern struct student* delstu(struct student *phead,struct student *stu);
extern struct student* eadfromfile(FILE *studata);
extern struct student* findnamenext(struct student *pead,char *name);
extern struct student* newstu(struct student*);
extern int save(struct student *phead,FILE *studata);
extern int countlist(struct student *phead);
extern struct student* reverse(struct student*);
extern struct student* readfromfile(FILE *);
#endif
