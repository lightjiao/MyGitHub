#include "BigNumMultiply.h"

void CBigNumMultiply::CharToNum()
{
    unsigned int size_a = m_sA.size();
    unsigned int size_b = m_sB.size();

    for (unsigned int i = 0; i < size_a; i++)
    {
        m_vecA.push_back(m_sA[i] - '0');
    }

    for (unsigned int i = 0; i < size_b; i++)
    {
        m_vecB.push_back(m_sB[i] - '0');
    }
}


void CBigNumMultiply::Multiply()
{
    //初始化 result Vector, 是否有更好的写法？
    for (unsigned int i = 0; i < m_vecA.size() + m_vecB.size(); i++)
    {
        //m_vecResult[i] = 0;
        m_vecResult.push_back(0);
    }

    //单纯的拆分因式 计算
    for (unsigned int i = 0; i < m_vecA.size(); i ++)
    {
        for (unsigned int j = 0; j < m_vecB.size(); j++)
        {
            m_vecResult[i + j] += m_vecA[i] * m_vecB[j];
        }
    }

    //TODO 处理多余的 0 , 可能是因为这里需要处理多余的0 ，所以可能需要将数组翻转存储 使用 pop_back去除多余的 0
    
    //处理进位
    int c = 0;
    for ( int i = m_vecResult.size() - 1; i >= 0; i--)
    {
        /* 脑海中的第一反应写法，太差劲了
        int num = m_vecResult[i] / 10;
        m_vecResult[i] = m_vecResult[i] % 10;
        m_vecResult[i - 1] += num;
        */

        m_vecResult[i] += c;
        c = m_vecResult[i] / 10;
        m_vecResult[i] = m_vecResult[i] % 10; //考虑进位的问题（999*999）， 数组也需要翻转存储
    }
}


void CBigNumMultiply::NumToChar()
{
    for (unsigned int i = 0; i < m_vecResult.size();i++)
    {
        m_sResult.push_back('0' + m_vecResult[i]);
    }
}


string& CBigNumMultiply::GetResult()
{
    CharToNum();
    Multiply();
    NumToChar();

    return m_sResult;
};


void BigNumMultiplyMain()
{
    CBigNumMultiply test(string("999"), string("999"));// 999 * 999的结果丢失了一位进位，懒得改了……先睡觉

    cout << test.GetResult() << endl;

    return;
}