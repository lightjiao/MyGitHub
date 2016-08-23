#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import logging, functools, asyncio, inspect

from aiohttp import web

def get(path):
    '''
    Define decorator @get('/path')
    '''
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            return func(*args, **kw)
        wrapper.__method__ = 'GET'
        wrapper.__route__  = path
        return wrapper
    return decorator

#this func write by my own, may be wrong
def post(path):
    '''
    Define decorator @post('/path')
    '''
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kw):
            return func(*args, **kw)
        wrapper.__method__ = 'POST'
        wrapper.__route__  = path
        return wrapper
    return decorator


class RequestHandler(object):
    def __init__(self, app, fn):
        self._app  = app
        self._func = fn

    async def __call__(self, request):
        kw = {}#...获取参数   ???
        r = await self._func(**kw)
        return r

def add_route(app, fn):
    method = getattr(fn, '__method__', None)
    path   = getattr(fn, '__route__',  None)
    if path is None or method is None:
        raise ValueError('@get or @post not define in %s. ' % str(fn))
    if not asyncio.iscoroutinefunction(fn) and not inspect.isgeneratorfunction(fn):
        fn = asyncio.coroutine(fn)
    logging.info('add route %s %s => %s(%s)' % (method, path, fn.__name__, ','.join(inspect.signature(fn).parameters.keys())))
    app.router.add_route(method, path, RequestHandler(app, fn))

def add_routes(app, module_name):
    n = module_name.rfind('.')
    if n == (-1):
        mod = __import__(module_name, globals(), locals())
    else:
        name = module_name[n+1:]
        mod  = getattr(__import__(module_name[:n], globals(), locals(), [name], name))

    for attr in dir(mod):
        if attr.startswith('_'):
            continue
        fn = getattr(mod, attr)
        if callable(fn):
            method = getattr(fn, '__method__', None)
            path   = getattr(fn, '__route__', None)
            if method and path:
                add_route(app, fn)

async def logger_factory(app, handler):
    async def logger(request):
        #记录日志
        logging.info('Request: %s %s' % (request.method, request.path))
        return (await handler(request))\

async def response_factory(app, handler):
    async def response(request):
        #结果
        r = await handler(request)
        if isinstance(r, web.StreamResponse):
            return r
        if isinstance(r, bytes):
            resp = web.Response(body=r)
            resp.content_type = 'application/octet-stream'
            return resp
        if isinstance(r, str):
            resp = web.Response(body=r.encode('utf-8'))
            resp.content_type = 'text/html;charset=utf-8'
            return resp
        




















