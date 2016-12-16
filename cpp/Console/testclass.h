#ifndef __C_TESTCLASS__
#define __C_TESTCLASS__


//这是一个关于构造函数写法的测试、说明

class Base
{
public:
    //最基本的构造函数
    Base(int b) : m_b(b)//冒号后面的语法相当于 m_b = b;
    {
    }
    
    //拷贝构造函数
    //（深度拷贝构造）拷贝构造函数无法拷贝动态分配的空间，需要重写一个新的拷贝构造函数
    /*以下场景会自动调用拷贝构造函数
    1）用一个已有的对象初始化一个新对象的时候
    2）将一个对象以值传递的方式传给形参的时候
    3）函数返回一个对象的时候
    
    所以当一个对象以传递值的方式传一个函数的时候，拷贝构造函数自动的被调用来生成函数中的对象。
    如果一个对象是被传入自己的拷贝构造函数，它的拷贝构造函数将会被调用来拷贝这个对象这样复制才可以传入它自己的拷贝构造函数，
    这会导致无限循环直至栈溢出除了当对象传入函数的时候被隐式调用以外，拷贝构造函数在对象被函数返回的时候也同样的被调用。*/
    Base(Base& ref) : m_b(ref.m_b)//拷贝构造函数此处必须写引用 而不是指针或者具体的对象  Here is a problem，指针貌似可以？？
    {
    }
    
private:
    int m_b;
};



//派生类
class Derivd : public Base
{
public:
    //普通派生类构造函数的写法
    Derivd(int b, int d) : Base(b), m_d(d)
    {
    }
    
private:
    int m_d;
};


//派生类示例_2:多继承
class Base1
{
public:
    Base1(int b1) : m_b1(b1)
    {
    }
    
private:
    int m_b1;
};

class Base2
{
public:
    Base2(int b2) : m_b2(b2)
    {
    }
    
private:
    int m_b2;
};

class Derivd2 : public Base1, Base2
{
public:
    Derivd2(int b1, int b2, int d) : Base1(b1), Base2(b2), m_d(d)
    {
        //注意冒号语法后面的顺序无所谓，创造基类是按照上面的继承声明顺序来进行的
    }
    
private:
    int m_d;
};

#endif

