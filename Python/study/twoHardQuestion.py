#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
from functools import reduce

#问题一
#编写一个能将给定非负整数列表中的数字排列成最大数字的函数。例如，给定[50，2，1,9]，最大数字为 95021。
def maxNumCombination(paramlist):
    if(reduce(lambda x, y: x and y, map(lambda n: (isinstance(n, int)) and (n >= 0) and (n == math.trunc(n)), paramlist))):
        return int(reduce(lambda x, y: x + y, map(str, sorted(paramlist, key = firstnum, reverse = True))))
    else:
        raise AttributeError('入参必须是数组，且元素必须是正整数')

    #下面是对上面式子的步骤化拆解，写完这个式子过后觉得Python 真是叼！！！
    #lTemp = sorted(list, key = firstnum, reverse = True)
    #lTemp = map(str, lTemp)
    #num   = reduce(lambda x, y: x + y, lTemp)
    #return int(num)

#将给定数字全都表示成 1.23的形式再比较大小
#可不可以将这个小函数写成 匿名函数 或者 有没有比较高阶的表达？？？？？？
def firstnum(n):
    while n > 9:
        n = n / 10
    return n



#问题二
#编写一个在1，2，…，9（顺序不能变）数字之间插入+或-或什么都不插入，使得计算结果总是 100 的程序，并输出所有的可能性。例如：1 + 2 + 34 – 5 + 67 – 8 + 9 = 100。
def sumToHundred():
    #分为两步，一、生成所有的 数字 排列组合的list；二、不断尝试其中的+ -号的情况
    pass

#获取所有数字的排列组合的 list嵌套list
#这可以写成 一个递归函数
def getAllNumCombination(paramlist):
    lAllCombination = []

    if len(paramlist) == 1:
        return paramlist
    elif len(paramlist) == 2:
        return [paramlist, paramlist[0]*10 + paramlist[1]]
    elif len(paramlist) == 3:
        pass

    return lAllCombination


#根据给定的数字list，算出所有能算出100 的组合
def getSumToHundred(paramlist):
    pass

###################################################test code
def list_1_index(paramlist):
    return paramlist

def list_2_index(paramlist):
    lTemplist = []
    lTemplist.append(paramlist)
    lTemplist.append([paramlist[0]*10+paramlist[1]])
    return lTemplist

def list_3_index(paramlist):
    lTemplist = []
    for i, index in enumerate(paramlist):
        if i == 0:
            continue
        lTemplist = list_2_index()

    lTemplist_1 = list_2_index(paramlist[0:2])
    for index in lTemplist_1:
        index.insert(2,paramlist[2])

    lTemplist_2 = list_2_index(paramlist[1:])
    for index in lTemplist_2:
        index.insert(0, paramlist[0])

    return lTemplist_1 + lTemplist_2

def list_4_index(paramlist):
    for i, value in enumerate(paramlist):
        pass
    pass



if __name__ == '__main__':
    print(list_3_index([3,4,5]))