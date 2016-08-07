#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
from functools import reduce

#问题一
#编写一个能将给定非负整数列表中的数字排列成最大数字的函数。例如，给定[50, 2, 1, 9]，最大数字为 95021。
def maxNumCombination(paramlist):
    if(reduce(lambda x, y: x and y, map(lambda n: (isinstance(n, int)) and (n >= 0) and (n == math.trunc(n)), paramlist))):
        return int(reduce(lambda x, y: x + y, map(str, sorted(paramlist, key = lambda n:float(reduce(lambda x, y: (x if x.find('.') > 0 else (x + '.')) + y, str(n))), reverse = True))))
    else:
        raise AttributeError('入参必须是数组，且元素必须是正整数')

    #下面是对上面式子的步骤化拆解，写完这个式子过后觉得Python 真是叼！！！
    #lTemp = sorted(list, key = firstnum, reverse = True)
    #lTemp = map(str, lTemp)
    #num   = reduce(lambda x, y: x + y, lTemp)
    #return int(num)

    #补充，其中key = firstnum 改写成了 key = lambda n: float(reduce(lambda x, y: (x if x.find('.') > 0 else (x + '.')) + y, str(n)))
    #是将数字转化成为 1.23 的形式再去比较

#原来的firstnum函数
def firstnum(n):
    while n > 9:
        n = n / 10
    return n


################################################################################################################################
################################################################################################################################
################################################################################################################################

#问题二
#编写一个在1，2，…，9（顺序不能变）数字之间插入+或-或什么都不插入，使得计算结果总是 100 的程序，并输出所有的可能性。例如：1 + 2 + 34 – 5 + 67 – 8 + 9 = 100。
def sumToHundred():
    #思路一（失败）  分为两步，一、生成所有的 数字 排列组合的list；二、不断尝试其中的+ -号的情况
    #思路二（定义一个长度为17 的数组）每个数字之间的链接有三种情况 + - 或者空
    lNUmlist = []
    num = 1
    for i in range(0, 17):
        if(i % 2 == 0):
            lNUmlist.append(str(num))
            num += 1
        else:
            lNUmlist.append("")

    lAllNumCombination = []
    get100(lNUmlist, 1, 16, lNUmlist, lAllNumCombination)

    for value in sumToHundred():
        print(reduce(lambda x, y: x + (' ' + y + ' ' if y == '+' or y == '-' else y), value) + ' = 100')

    return lAllNumCombination

#获取所有的组合
def get100(data1, count, times, data2, lAllNumCombination):
    if count >= times:
        if calculate100(data2) == 100:
            lAllNumCombination.append(data2)
            #print(reduce(lambda x, y: x + (' ' + y + ' ' if y == '+' or y == '-' else y), data2) + ' = 100')
        return

    temp1 = list(data2)
    temp2 = list(data2)
    temp3 = list(data2)

    temp1[count] = '+'
    temp2[count] = '-'
    temp3[count] = ''
    count += 2

    get100(data1, count, times, temp1, lAllNumCombination)
    get100(data1, count, times, temp2, lAllNumCombination)
    get100(data1, count, times, temp3, lAllNumCombination)


#根据入参的组合计算结果
def calculate100(paramlist):
    sum = 0
    tempnum  = 0
    bitCount = 0
    for i, value in enumerate(reversed(paramlist)):
        if value == '+':
            sum += tempnum
            tempnum  = 0
            bitCount = 0

        elif value == '-':
            sum -= tempnum
            tempnum = 0
            bitCount = 0

        elif value == '':
            bitCount += 1

        else:
            tempnum += math.pow(10, bitCount) * int(value)

    sum += tempnum
    return sum


#第二个问题的第二种解法（非递归）



if __name__ == '__main__':
    pass



