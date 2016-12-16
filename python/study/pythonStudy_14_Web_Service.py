#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#service.py

from wsgiref.simple_server import make_server

#服务的具体实现
def application(environ, start_response):
    start_response('200 oK', [('Content-Type', 'text/html')])
    body = '<h1>Hello, %s!</h1>' % (environ['PATH_INFO'][1:] or 'web')
    return [body.encode('utf-8')]
    #return [b'<h1>Hello web!</h1>']


#创建一个服务器,IP为空， 端口为8000 处理函数为application
httpd = make_server('', 8000, application)
print('Serving HTTP on port 8000...')

#开始监听http请求
httpd.serve_forever()