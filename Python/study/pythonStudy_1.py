#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#切片
#d = {'a':1,'b':2,'c':3}

#遍历dict的value
#for value in d.itervalues():
#	#print value
#	pass

#遍历dict的key & value
#for k, v in d.iteritems():
#	print k, v

#列表生成器
#[x*x for x in range(10)]
#L = ['Hello', 'World', 18, 'Apple', None]
#print [s.lower() if isinstance(s,str) else s for s  in L]

#生成器(Generator)
g = (x*x for x in range(10))

#斐波拉契数列 的函数
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        #print b
        yield b #生成器会在此处暂停并返回b 给next(), 后面的每次next都在此处继续执行
        a, b = b, a+b
        n = n + 1
    return 'done'

for n in fib(6):
    pass
    #print(n)


#规范名字字符串的大小写, map是将函数作用于list的每一个元素并将结果作为新的list返回
def RightFormat(s):
    return s[0].upper() + s[1:].lower()
map(RightFormat, ['adam', 'LISA', 'barT'])
map(lambda x:x.title(), ['adam', 'LISA', 'barT'])

#list求积 reduce是递进的将临近两个元素作为函数的入参,并将结果继续和下一个元素做累积计算
def prod(param):
    return reduce(lambda x,y:x*y, param)

#删除1~100的素数 filter用于过滤序列, 用一个判断函数作用于每一个元素,判断结果为False的丢弃该元素
def isPrimeNum(n):
    divide = filter(lambda i:n%i==0, range(2,n/2))
    return len(divide) == 0

filter(isPrimeNum, range(1,101))

#杨辉三角
def triangles():
    L1=[1]
    while True:
        if len(L1) == 1:
            yield L1
        L2 = [L1[i] + L1[i+1] for i in range(len(L1)-1)]
        L2.insert(0,1)
        L2.append(1)
        L1 = L2
        yield L1

num = 0
for t in triangles():
    #print(t)  #打印杨辉三角
    num += 1
    if(num == 10):
        break

def _odd_iter():
    n = 1
    while True:
        n = n + 2
        yield n

def _not_divisible(n):
    return lambda x: x%n > 0

def primes():
    yield 2
    it = _odd_iter();
    while True:
        n = next(it)
        yield n
        it = filter(_not_divisible(n), it)#怎么就实现了循环遍历 it了？


def is_palindrome(n):
    s = str(n)
    return s[:] == s[::-1]#######切片的 z = -1 时候


######装饰器
def log(func):
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)
    return wrapper

@log
def now():
    print('2016-06-03')



now()
