#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Student(object):
    pass


class Screen(object):
    @property
    def width(self):
        return self._width

    @width.setter
    def width(self, value):
        if(value > 1024):
            print('too large value of width...')
            return
        self._width = value

    @property
    def height(self):
        return self._height
    
    @height.setter
    def height(self, value):
        self._height = value

    @property
    def resolution(self):
        return self._width * self._height

class Fib(object):
    def __init__(self):
        self.a, self.b = 0, 1

    def __iter__(self):
        return self

    def __next__(self):
        self.a, self.b = self.b, self.a + self.b
        if(self.a > 10000):
            raise StopIteration()
        return self.a

#链式、动态的调用：print (Chain().status.user.timeline.list)
class Chain(object):
    def __init__(self, path = ''):
        self._path = path

    def __getattr__(self, path):
        return Chain('%s/%s' % (self._path, path))

    def __str__(self):
        return self._path

    __repr__ = __str__

def fn(self, name = 'World'):
    print('Hello, %s.' % name)

#用type()函数动态的创建一个类
Hello = type('Hello', (object,), dict(hello = fn))


#使用元类:
#metaclass
#除了使用type()动态创建类以外，要控制类的创建行为，还可以使用metaclass。
#metaclass，直译为元类，简单的解释就是：
#当我们定义了类以后，就可以根据这个类创建出实例，所以：先定义类，然后创建实例。
#但是如果我们想创建出类呢？那就必须根据metaclass创建出类，所以：先定义metaclass，然后创建类。
#连接起来就是：先定义metaclass，就可以创建类，最后创建实例。
#所以，metaclass允许你创建类或者修改类。换句话说，你可以把类看成是metaclass创建出来的“实例”。
#metaclass是Python面向对象里最难理解，也是最难使用的魔术代码。

class ListMetaclass(type):#metaclass 是类的模板, 所以必须从type 类型派生
    def __new__(cls, name, bases, attrs):
        attrs['add'] = lambda self, value: self.append(value)
        return type.__new__(cls, name, bases, attrs)

class MyList(list, metaclass = ListMetaclass):
    pass


class Animal(object):
    def __init__(self):
        print('__init__ Animal')

class Memmal(Animal):
    def __init__(self):
        print('__init__ Memmal')
        super(Animal, self).__init__()
        print('__init__ Memmal After')
        
class Dog(Memmal):
    def __init__(self):
        print('__init__ Dog')
        super(Memmal, self).__init__()
        print('__init__ Dog After')
        

#d = Dog()
