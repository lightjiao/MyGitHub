#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#task_master.py

import random, time, queue
from multiprocessing.managers import BaseManager

#发送任务的队列
task_queue = queue.Queue()

#接受结果的队列
result_queue = queue.Queue()

#从BaseManager 继承的Queuemanager
class QueueManager(BaseManager):
    pass

#注册Queue到网络上
QueueManager.register('get_task_queue', callable= lambda : task_queue)
QueueManager.register('get_result_queue', callable= lambda : result_queue)

#绑定端口、设置密码
manager = QueueManager(address= ('', 50000), authkey= b'123')

#启动Queue:
manager.start()

#获得通过网络访问的Queue对象
task = manager.get_task_queue()
result = manager.get_result_queue()

#放置任务进去
for i in range(10):
    n = random.randint(0, 10000)
    print('Put task %d...' % n)
    task.put(n)

#从result队列读取结果
print('Try get result...')
for i in range(10):
    r = result.get(timeout = 10)
    print('Result: %s.' % r)

#关闭
manager.shutdown()
print('master exit')