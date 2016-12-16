#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from multiprocessing import Pool, Process, Queue
import os, time, random, subprocess

##############################################################################
#线程调度#
##############################################################################
def writeTXT(filename):
    filename = 'D:\\' + str(filename) + '.txt'
    print(filename)
    with open(filename, 'w') as f:
        for i in range(1,100000):
            f.write(str(random.randint(0,9)))

def the_task(taskName):
    print('Run task %s (%s)...' % (taskName, os.getpid()))
    startTime = time.time()
    writeTXT(taskName)
    endTime = time.time()
    print('Task % runs %0.2f seconds.' % (taskName, (endTime - startTime)))

#线程调度开始函数
def Run_the_thread_task():
    print('Parent processing %s.' % os.getpid())

    p = Pool(3)

    for i in range(0, 10):
        p.apply_async(the_task, args = (i,))
    print('Waiting for all subprocesses done...')
    p.close()
    p.join()
    print('All subprocesses done.')
##############################################################################
##############################################################################


##############################################################################
#子进程#
##############################################################################
def Run_the_subprocess():

    #相当于运行cmd: nslookup www.python.org
    #print('$ nslookup www.python.org')
    #r = subprocess.call(['nslookup', 'www.python.org'])
    #print('Exit code:', r)
    
    #相当于运行cmd: nslookup 然后手动输入 set q=mx, python.org, exit 等三条命令
    print('$nslookup')
    p = subprocess.Popen(['nslookup'], stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    output, err = p.communicate(b'set q = mx\npython.org\nexit\n')
    print(output.decode('gbk'))
    print('Exit code:', p.returncode)
    

##############################################################################
##############################################################################

##############################################################################
#进程间通讯#
##############################################################################
#写数据进程执行的代码
def ProcessToWrite(queue):
    print('Process to write: %s' % os.getpid())
    for value in ['A', 'B', 'C']:
        print('Put %s to queue...' % value)
        queue.put(value)
        time.sleep(random.random())

#读数据进程执行的代码
def ProcessToRead(queue):
    print('Process to read: %s...' % os.getpid())
    while True:
        value = queue.get(True)
        print('Get %s from queue.' % value)

def Run_the_Process_communicate():
    queue = Queue()
    pw = Process(target = ProcessToWrite, args = (queue,))
    pr = Process(target = ProcessToRead,  args = (queue,))

    pw.start()

    pr.start()

    pw.join()
    #pr里是死循环，无法等待其结束， 只能强行终止
    pr.terminate()


##############################################################################
#小结
#在Unix/Linux下，可以使用fork()调用实现多进程。
#要实现跨平台的多进程，可以使用multiprocessing模块( "模拟"出fork() 的效果???)。
#进程间通信是通过Queue、Pipes等实现的。
##############################################################################




if __name__ == '__main__':
    Run_the_Process_communicate()