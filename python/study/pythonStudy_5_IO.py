#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os

#使用with 语句操作文件的读写
#with open('./Data/test.txt') as f:
#    pass

sPath = os.path.abspath('.')

sTestPath = os.path.join(sPath, 'testDir')

#os.rmdir(sTestPath)
#os.mkdir(sTestPath)

print([x for x in os.listdir('.') if os.path.isdir(x)])
print([x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1] == '.py'])

filename = './Data/test.txt'
newfilename = filename
nFilenameAppend = 0
while 1:
    try:
        m_fpFile = open(newfilename, 'x')
        break
    
    except OSError :
        nFilenameAppend += 1
        newfilename = filename + '_' + str(nFilenameAppend)
        continue