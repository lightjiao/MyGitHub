#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
from sys import exit
import random

background_image_filename = 'sushiplate.jpg'
mouse_image_filename = 'fugu.png'

pygame.init() #初始化pygame,为使用硬件做准备

screen = pygame.display.set_mode((640, 480))# 创建一个窗口

pygame.display.set_caption('Hello world!') #设置标题

background   = pygame.image.load(background_image_filename).convert()
mouse_cursor = pygame.image.load(mouse_image_filename).convert_alpha()

x_pos, y_pos = random.randint(0, 640), random.randint(0, 480)
x_speed, y_speed = random.randint(100, 200), random.randint(100, 200)
#x_pos, y_pos = math.trunc(random.random()*640), math.trunc(random.random()*480) #随机的起始坐标
#x_speed = y_speed = math.trunc(random.random()*100) + 100 #随机的移动速度 100 <= speed < 200

clock = pygame.time.Clock() #主循环的时间类


while True: # the main loop of game progress
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()

    screen.blit(background, (0, 0))  # 将背景图画上去
    screen.blit(mouse_cursor, (x_pos, y_pos))

    time_passed = clock.tick()
    time_passed_seconds = time_passed / 1000
    x_distance_moved = time_passed_seconds * x_speed
    y_distance_moved = time_passed_seconds * y_speed

    x_pos += x_distance_moved
    y_pos += y_distance_moved

    if x_pos > 640 or x_pos < 0:
        x_speed = -x_speed
    if y_pos > 480 or y_pos < 0:
        y_speed = -y_speed

    pygame.display.update() #刷新画面