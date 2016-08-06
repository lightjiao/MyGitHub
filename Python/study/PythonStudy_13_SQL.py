#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3

#打开db 文件，文件不存在则创建
conn = sqlite3.connect('../Data/test.db')

#创建一个cursor
cursor = conn.cursor()

#有利于重复执行
cursor.execute('drop table USER ')

cursor.execute('create table USER (ID VARCHAR2(20) PRIMARY KEY, NAME VARCHAR2(20))')

cursor.execute('INSERT INTO USER (id, name) VALUES (\'1\', \'Micheal\')')

#插入数据的行数
#使用Cursor对象执行insert，update，delete语句时，执行结果由rowcount返回影响的行数，就可以拿到执行结果。
print(cursor.rowcount)

#带入参的语句
cursor.execute('select * from user where id=? and name=?', ('1', 'Micheal'))

values = cursor.fetchall()

print(values)

cursor.close()

conn.commit()

conn.close()

