#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re

#test = '用户输入的字符串'
#if re.match(r'正则表达式', test):
#   print('ok')
#else:
#   print('failed')

sTest = 'a b     c'
#print(sTest.split(' '))
print(re.split(r'\s+',       'a b     c d'))
print(re.split(r'[\s\,]+',   'a,b, c d'))
print(re.split(r'[\s\,\;]+', 'a,b;; c  d'))

m = re.match(r'^(\d{3})\-(\d{3,8})$', '010-12345')
print(m.groups())
print(m.group(0))
print(m.group(1))
print(m.group(2))

t = '19:05:30'
m = re.match(r'^([0-1][0-9]|2[0-3]|[0-9])\:'+
             r'([0-5][0-9]|[0-9])\:'+
             r'([0-5][0-9]|[0-9])', t)

print(m.groups())

#贪婪匹配
#正则匹配默认是贪婪匹配，也就是匹配尽可能多的字符。举例如下，匹配出数字后面的0：
print(re.match(r'^(\d+)(0*)$', '102300').groups())
#避免贪婪匹配(尽可能少的匹配)
print(re.match(r'^(\d+?)(0*)$', '102300').groups())


#当我们在Python中使用正则表达式时，re模块内部会干两件事情：
#编译正则表达式，如果正则表达式的字符串本身不合法，会报错；
#用编译后的正则表达式去匹配字符串。
#如果一个正则表达式要重复使用几千次，出于效率的考虑，我们可以预编译该正则表达式，接下来重复使用时就不需要编译这个步骤了，直接匹配：
re_telephon = re.compile(r'^(\d{3})-(\d{3,8})$') #编译
#使用
print(re_telephon.match('010-12345').groups())


#验证email的练习
re_email = re.compile(r'^(\<[a-zA-Z\s\.]*\>)*([a-zA-Z\.\s]*\@[a-zA-Z]*\.[a-zA-Z]+)$')
print(re_email.match('someone@gmail.com').groups())
print(re_email.match('bill.gates@microsoft.com').groups())
print(re_email.match('<Tom Paris> tom@voyager.org').groups())



