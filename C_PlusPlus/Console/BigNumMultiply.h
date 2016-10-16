#ifndef __BIG_NUM_MULTIPLY_H__
#define __BIG_NUM_MULTIPLY_H__

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class CBigNumMultiply
{
private:
    string      m_sA;
    string      m_sB;
    string      m_sResult;

    vector<int> m_vecA;
    vector<int> m_vecB;
    vector<int> m_vecResult;

    void CharToNum();
    void Multiply();
    void NumToChar();

public:
    CBigNumMultiply(string a, string b) :m_sA(a), m_sB(b) {};
    string& GetResult();
};


extern void BigNumMultiplyMain();

#endif
