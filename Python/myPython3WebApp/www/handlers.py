#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Lights Jiao'

' url handlers '

from coroweb import get, post
from models import User, Blog, Comment

import time

@get('/test')
async def test(request):
    users = await User.findAll()
    return {
        '__template__':'test.html',
        'users':users
    }


@get('/')
async def index(request):
    summary = '这是一个摘要'
    blogs = [
        Blog(id='1', name='Test Blog',     summary=summary, created_at=time.time() - 120),
        Blog(id='2', name='Something New', summary=summary, created_at=time.time() - 3600),
        Blog(id='3', name='Learn Swift',   summary=summary, created_at=time.time() - 7200)
    ]
    return {
        '__template__':'blogs.html',
        'blogs':blogs
    }

@get('/api/users')
def api_get_users(*, page='1'):
    page_index = get_page_index(page)
    num = yield from User.findNumber('count(id)')
    p = Page(num, page_index)
    if num == 0:
        return dict(page=p, users=())
    users = yield from User.findAll(orderBy='created_at desc', limit=(p.offset, p.limit))
    for u in users:
        u.passwd = '******'
    return dict(page=p, users=users)