#include <iostream>
#include <string.h>

using namespace std;

class mphone
{
    public:
        mphone(int weigth,int power = 100,bool state = true);
        virtual void show(void) = 0;
        void poweron(void);
        void on(void);
        void off(void);
    private:
        int  weigth;
        int  power;
        bool state;
};

mphone::mphone(int weigth,int power,bool state)
{
    this->weigth = weigth;
    this->power  = power;
    this->state  = state;
    cout<<"mphone is create"<<endl;
}
/*
void mphone::show(void)
{
    cout<<"weigth:"<<weigth
        <<" power:"<<power<<"%";
    if(state)
    {
        cout<<" state:"<<"on"<<endl;
    }
    else
    {
        cout<<" state:"<<"off"<<endl;
    }
}
*/
void mphone::on(void)
{
    if(state)
    {
        cout<<"this phone is already power on"<<endl;
    }
    else
    {
        state = true;
    }
}

void mphone::off(void)
{
    if(state)
    {
        state = false;
    }
    else
    {
        cout<<"this phone is already power off"<<endl;
    }
}

class nokia:public mphone
{
    public:
        void fight(void)
        {
            cout<<"figth through nokia phone"<<endl;
        }
        nokia(int weigth,int power,bool state);
        void show(void)
        {
            cout<<"I can used for weapon"<<endl;
        }
};

nokia::nokia(int weigth,int power = 100,bool state = true):mphone(weigth,power,state)
{
}

void show(mphone *p)
{
    p->show();
}

int main()
{
    //mphone *pmphone = new mphone(1,1,true);
    mphone *pnokia  = new nokia(1,100,false);
    //show(pmphone);
    show(pnokia);
}
