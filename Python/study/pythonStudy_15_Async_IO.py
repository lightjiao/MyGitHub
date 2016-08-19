#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import time

############### 协程(yield)情景下的生产者-消费者模型 ###########
#消费者
def consumer():
    r = ''
    while True:
        n = yield r
        if not n:
            return
        print('[CONSUMER]:Consuming %s ...' % n)
        r = '200 OK'

#生产者
def produce(c):
    c.send(None)
    n = 0
    while n < 5:
        n += 1
        print('[PRODUCER]:Producing %s ...' % n)
        r = c.send(n)
        print('[PRODUCER]:Consumer return: %s ...' % r)
    c.close()


####################### 异步IO ############################
import threading
import asyncio #python 3.4+

@asyncio.coroutine # 把一个generator标记为corountine(协程)类型, 然后将这个coroutine扔到Eventloop中执行
def hello():
    print('Hello world!', threading.current_thread())
    begintime = time.clock()
    # 异步调用 asyncio.sleep(1)
    r = yield from asyncio.sleep(1)
    print('Hello again! and time = %.5fs' % float(time.clock()-begintime) )

@asyncio.coroutine
def wget(host):
    print('wget %s ...' % host)
    connect = asyncio.open_connection(host, 80)
    reader, writer = yield from connect
    header = 'GET / HTTP/1.0\r\nHost:%s\r\n\r\n' % host
    writer.write(header.encode('utf-8'))
    yield from writer.drain()
    while True:
        line = yield from reader.readline()
        if line == b'\r\n':
            break
        print('%s header > %s' % (host, line.decode('utf-8').rstrip()))

    # Ignore the body close the socket
    writer.close()


####################### main func #########################
#协程的main()
def main_1():
    c = consumer()
    produce(c)

#异步IO的main()
def main_2():
    #获取evenloop
    loop = asyncio.get_event_loop()
    #task = [hello(), hello()]
    task = [wget(host) for host in  ['www.sina.com.cn', 'www.sohu.com', 'www.163.com']]
    loop.run_until_complete(asyncio.wait(task))#异步IO执行任务
    loop.close()

if __name__ == '__main__':
    main_2()