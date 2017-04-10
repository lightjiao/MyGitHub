#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pika

# connect to local rabbit mq
conn = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = conn.channel()

# declare a queue
channel.queue_declare(queue='hello')

# send message to a queue through default exchange
channel.basic_publish(exchange='',
                      routing_key='hello',
                      body='hello world!')

print(" [x] sent 'hello world!'")

# close connection to make sure the network buffers were flushed and our message was actually delivered to RabbitMQ
conn.close()
