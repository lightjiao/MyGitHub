#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3

#打开db 文件，文件不存在则创建
conn = sqlite3.connect('../Data/test.db')

#创建一个cursor
cursor = conn.cursor()

cursor.execute('create table USER (ID VARCHAR2(20) PRIMARY KEY, NAME VARCHAR2(20))')
