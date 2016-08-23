#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import orm
from model import User, Blog, Comment

def Modeltest():
    yield from orm.create_pool(user = 'www-data', password = '1', database = 'mypython3webapp')

    u = User(name = 'test', email = 'test@example.com', passwd = '123456', image = 'about:blank')

    yield from u.save()

if __name__ == '__main__':
    Modeltest()