#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika

def publish_message(message):
    """
    发送消息到RabbitMQ
    """

    # connect to local rabbit mq
    conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    channel = conn.channel()

    # declare a queue
    channel.queue_declare(queue='hello')

    # send message to a queue through default exchange
    channel.basic_publish(exchange='', routing_key='hello', body=message)

    print(" [x] sent %s" % message)

    # close connection to make sure the network buffers were flushed and our message was actually delivered to RabbitMQ
    conn.close()

for n in range(10):
    message = "Hello world " + str(n)
    publish_message(message)
