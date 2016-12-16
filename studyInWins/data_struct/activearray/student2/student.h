
#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
};

struct allstu
{
    struct student **pstu;
    unsigned int space;
    unsigned int num;
};

extern struct student* newstu(struct student *tempstu);
extern void addstu(struct allstu *all,struct student *stu);
extern int initall(struct allstu *all);
extern void showstu(struct student *stu);
extern void showallstu(struct allstu *all);
extern struct student** findstu(struct allstu *all,char *id);
extern int delstu(struct allstu *all,struct student **stu);
extern int save(struct allstu *all,FILE *studata);
extern int readfromfile(struct allstu *all,FILE *studata);
extern struct student** findnamenext(struct allstu *all,char *name,struct student **pre);


#endif
