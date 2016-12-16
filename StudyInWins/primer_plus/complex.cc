#include <iostream>

using namespace std;

class mycomplex
{
    private:
        int real;
        int imag;
    public:
        void setvalue(int real,int imag);
        void show(void);
        mycomplex operator +(mycomplex &b);
        mycomplex operator -(mycomplex &b);
};

void mycomplex::setvalue(int real,int imag)
{
    this->real = real;
    this->imag = imag;
}

void mycomplex::show(void)
{
    cout<<real<<'+'<<imag<<"*i"<<endl;
}

mycomplex mycomplex::operator +(mycomplex &b)
{
    mycomplex c;
    c.real = real + b.real;
    c.imag = imag + b.imag;
    return c;
}

mycomplex mycomplex::operator -(mycomplex &b)
{
    mycomplex c;
    c.real = real - b.real;
    c.imag = imag - b.imag;
    return c;
}

int main(int argc,char *argv[])
{
    mycomplex x;
    mycomplex y;
    mycomplex c;
    x.setvalue(10,10);
    y.setvalue(20,20);
    c = x + y;
    c.show();
}















