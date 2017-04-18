#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika
import time
# from random import Random
import random

# declare call back func
def call_back(ch, method, properties, body):
    print(" [x] %s finished %r" % (time.ctime()[-10:-5], body))

    """
    发送消息回执
    在no_ack 为false的情况下，如果一条消息断开连接了(网络断开或者worker死掉)，服务端没有收到ack消息
    那么这一条消息会被RabbitMQ服务端重新发送一次
    *RabbitMQ的worker没有超时一说
    """
    ch.basic_ack(delivery_tag=method.delivery_tag)


if __name__ == '__main__':
    # connect to local rabbit mq
    conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    channel = conn.channel()

    # declare a exchange
    channel.exchange_declare(exchange='logs', exchange_type='fanout')

    # declare a queue with random name
    result = channel.queue_declare(exclusive=True)
    queue_name = result.method.queue
    print(queue_name)

    # bind queue to exchange
    channel.queue_bind(exchange='logs', queue=queue_name)

    """
    限制当前worker缓存消息的大小
    一个worker处理消息本身也是一条一条的处理，worker中也会存在一个消息缓存
    这个数量就是消息缓存的大小 - 默认大小不知道
    """
    channel.basic_qos(prefetch_count=1)

    channel.basic_consume(call_back,
                          queue=queue_name,
                          # no_ack=True,    #Message acknowledgments are turned on by defaul
                          )

    print(" [*] waiting for message. to exit press ctrl+c")
    channel.start_consuming()
