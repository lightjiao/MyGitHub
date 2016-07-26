
#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *next;
};

struct idhash
{
    struct student* allstu[10];
};

extern int initallidhash(struct idhash *allstu);
extern void showstu(struct student *stu);
extern void showallstu(struct idhash *allstu);
extern int addstu(struct idhash *allstu,struct student *stu);
extern struct student* findstu(struct idhash *allstu,char *id);
extern int delstu(struct idhash *allstu,struct student *stu);
extern int readfromfile(struct idhash *allstu,FILE *studata);
extern struct student* findnamenext(struct student *pead,char *name);
extern struct student* newstu(struct student*);
extern int save(struct idhash *allstu,FILE *studata);
extern int count(struct idhash *allstu);

#endif
