#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class mystring
{
    private:
        char *data;
        unsigned int space;
        unsigned int len;
        void increase(void);
    public:
        mystring(const char *buf = "");
        mystring(mystring &s);
        ~mystring(void);
       
        char* c_str(void);
        int length(void);
        
        //mystring operator+(mystring &s);
        //mystring operator+(char *buf);
        
        mystring& operator=(mystring &s);
        mystring& operator=(const char *buf);
        
        mystring& operator+=(mystring &s);
        mystring& operator+=(char *buf);
};

mystring::mystring(mystring &s)
{
    unsigned int tmplen = s.len;
    data =  new char[tmplen+1];
    strcpy(data,s.data);
    len = tmplen;
    space = len +1;
}

mystring::mystring(const char *buf)
{
    unsigned int tmplen = strlen(buf);
    data =  new char[tmplen+1];
    strcpy(data,buf);
    len = tmplen;
    space = len +1;
}

mystring::~mystring(void)
{
    delete []data;
}

void mystring::increase(void)
{
    char *p = new char [space*2];
    memcpy(p,data,len);
    delete []data;
    data = p;
    space *= 2;
}

char* mystring::c_str(void)
{
    return data;
}

int mystring::length(void)
{
    return len;
}
/*
mystring mystring::operator+(mystring &s)
{
    mystring tmp;
    strcpy(tmp.data,data);
    strcat(tmp.data,s.data);
    return tmp;
}
mystring mystring::operator+(char *buf)
{
    mystring tmp;
    strcpy(tmp.data,data);
    strcat(tmp.data,buf);
    return tmp;
}
*/

mystring& mystring::operator=(mystring &s)
{
    while(space <= s.len)
    {
        increase();
    }
    strcpy(data,s.data);
    len = s.len;
    return *this;
}

mystring& mystring::operator=(const char *buf)
{
    unsigned int llen = strlen(buf);
    while(space <= llen)
    {
        increase();
    }
    strcpy(data,buf);
    len = llen;
    return *this;
}

mystring& mystring::operator+=(mystring &s)
{
    while(space <= len+s.len)
    {
        increase();
    }
    strcat(data,s.data);
    len = s.len;
    return *this;
}

mystring& mystring::operator+=(char *buf)
{
    unsigned int llen = strlen(buf);
    while(space <= len+llen)
    {
        increase();
    }
    strcat(data,buf);
    len += llen;
    return *this;
}

int main(int argc,char *argv[])
{
    mystring s1;
    mystring s2("hello s2");

    s1 = "hello s1";

    cout<<"s1 = "<<s1.c_str()<<endl
        <<"s2 = "<<s2.c_str()<<endl;

    //s1 = s2;
    cout<<s1<<endl;
}




