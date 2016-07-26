
#include <iostream>
#include <vector>

using namespace std;

struct student
{
    string id;
    string name;
    unsigned int age;
    char sex;
};

const char *cmdstr[] = 
{
    "show",
    "add",
    "del",
    "find",
    "quit",
    NULL
};
enum cmdtype
{
    cmdshow,
    cmdadd,
    cmddel,
    cmdfind,
    cmdquit
};

int getcmd(string &s)
{
    int i = 0;
    for(i=0;cmdstr[i]!=NULL;i++)
    {
        if(s == string(cmdstr[i]))
        {
            return i;
        }
    }
    return i;
}

void showone(struct student *pstu)
{
    cout<<"id:"<<pstu->id
        <<" name:"<<pstu->name
        <<" sex:"<<pstu->sex
        <<" age:"<<pstu->age<<endl;
}

void showall(vector<struct student *> &allstu)
{
    vector<struct student *>::iterator it;

    for(it = allstu.begin();it!=allstu.end();it++)
    {
        showone(*it);
    }
    return;
}

void insert(vector<struct student *> &allstu,struct student *pstu)
{
    
}

int main()
{
    bool quit = false;
    string cmd;
    int cmdno;
    struct student *pstu = NULL;
    vector<struct student *> allstu;
    while(!quit)
    {
        cin>>cmd;
        cmdno = getcmd(cmd);
        switch(cmdno)
        {
            case cmdshow:
                showall(allstu);
                break;
            case cmdadd:
                pstu = new struct student;
                cout<<"please input id:";
                cin>>pstu->id;
                cout<<"please input name:";
                cin>>pstu->name;
                cout<<"please input sex:";
                cin>>pstu->sex;
                cout<<"please input age:";
                cin>>pstu->age;
                insert(allstu,pstu);
                break;
            case cmddel:
                cout<<"del"<<endl;
                break;
            case cmdfind:
                cout<<"find"<<endl;
                break;
            case cmdquit:
                quit = true;
                break;
            default:
                cout<<"wrong cmd:"<<cmd<<endl;
                break;
        }
    }
    return 0;
}
