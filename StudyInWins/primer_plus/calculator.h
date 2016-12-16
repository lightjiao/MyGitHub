
#ifndef __CALCULATER_H__
#define __CALCULATER_H__
#include "mystack.h"

using namespace std;

class calcu
{
    public:
        calcu(unsigned int space = 10);
        double compute(const char *s);
        double compute(string &s);
        void clear(void);
    private:
        mystack<double> numstack;
        mystack<char>   opstack;
        int oplevel(char op);
        double opcompute(double a,double b,char op);
};

#endif
