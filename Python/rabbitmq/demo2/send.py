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

    # declare a exchange
    channel.exchange_declare(exchange='logs', exchange_type='fanout')

    # we send message by exchange, not queue

    # send message to a queue through default exchange
    channel.basic_publish(exchange='logs', routing_key='', body=message)

    print(" [x] sent %s" % message)

    # close connection to make sure the network buffers were flushed and our message was actually delivered to RabbitMQ
    conn.close()



for n in range(10):
    message = "Hello world " + str(n)
    publish_message(message)
