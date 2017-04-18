#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
import time
# from random import Random
import random

# connect to local rabbit mq
conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = conn.channel()

# declare a queue
channel.queue_declare(queue='hello')

# declare call back func
def call_back(ch, method, properties, body):
    # print(" [x] %s start reveived %r" % (time.ctime()[-7:-5], body))
    # time.sleep(Random.randint(1, 5))
    # time.sleep(random.randint(0, 10))

    # if body.decode()[-1] == "1":
    #     print("-------- sleep 10000 ----------")
    #     time.sleep(10000)

    print(" [x] %s finished %r" % (time.ctime()[-10:-5], body))


channel.basic_consume(call_back,
                      queue='hello',
                      no_ack=True)

print(" [*] waiting for message. to exit press ctrl+c")
channel.start_consuming()
