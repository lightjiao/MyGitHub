#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

struct set
{
    char *data;
    struct set *next;
};

class list
{
    private:
        struct set *phead;
    public:
        list(void);
        void add(char *data);
        struct set* begin(void);
        struct set* end(void);
        void show(void);
};

list::list(void)
{
    struct set ptmp;
    ptmp.data = new char[1];
    ptmp.data[0] = 0;
    ptmp.next = NULL;
    phead = &ptmp;;
}

struct set* list::begin(void)
{
    return phead;
}
struct set* list::end(void)
{
    return NULL;
}

void list::add(char *data)
{
    int len = strlen(data);
    struct set *ptmp = new struct set;
   
    ptmp->data = new char[len+1];
    memcpy(ptmp->data,data,len+1);
    ptmp->data[len] = 0;
    ptmp->next = NULL;
    
    ptmp->next = phead;
    phead = ptmp;
}

void list::show(void)
{
    struct set *ptmp = phead;
    while(NULL != ptmp)
    {
        cout<<ptmp->data<<endl;
        ptmp = ptmp->next;
    }
}

void strsplit(char *s)
{
    int len = strlen(s);
    list slist;
    struct set *ptmp;
    char *start = new char[len];
    for(int i=0;i<len;i++)
    {
        //cout<<i<<endl;
        ptmp = slist.begin();
        while(NULL != ptmp)
        {
            strcpy(start,ptmp->data);
            start[strlen(start)] = s[i];
            start[strlen(start)+1] = 0;
            slist.add(start);
            cout<<start<<endl;
            ptmp = ptmp->next;
            cout<<i<<endl;
        }
    }
}

int main(int argc,char *argv[])
{
    strsplit("abcd");
    return 0;
}








