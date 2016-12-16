
#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
};



extern int savestudata(struct student *stu,int pos,FILE *studata);
extern int readstudata(struct student *stu,int pos,FILE *studata);
extern int showonestu(int pos,FILE *studata);
extern int showallbyid(struct idhash *idh,FILE *studata);
extern int showallbyname(struct namehash *nhash,FILE *studata);


#endif 
