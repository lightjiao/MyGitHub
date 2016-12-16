#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import asyncio

import orm
from models import User, Blog, Comment

async def Modeltest(loop):
    await orm.create_pool(loop, user = 'www-data', password = '1', db = 'mypython3webapp')

    u = User(name = 'test', email = 'test@example.com', passwd = '123456', image = 'about:blank')

    await u.save()

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(Modeltest(loop))
    loop.run_forever()
