#!/usr/bin/env python3
# -*- coding: utf-8 -*-


#测试Python中的splite函数
def testSplite():
    s = "弢|你好啊|123|弢弢弢|abc"
    return s.split('|')

if __name__ == '__main__':
    print(testSplite())
    print("弢".encode('utf-8'))
    print("|".encode('utf-8'))