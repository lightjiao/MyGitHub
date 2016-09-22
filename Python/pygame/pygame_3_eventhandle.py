#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
import sys

bakcground_image_filename = 'sushiplate.jpg'

pygame.init()
screen = pygame.display.set_mode((640,480))
bakcground = pygame.image.load(bakcground_image_filename).convert()

x, y = 0, 0
move_x, move_y = 0, 0

# pygame.event.set_allowed()  #设置允许的事件
# pygame.event.set_blocked(KEYDOWN)  #设置禁止的事件
# pygame.event.set_grab(True) #锁定鼠标、键盘只活动在这一个窗口中

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            sys.exit()

    if event.type == KEYDOWN:#键盘有按下
        if event.key == K_LEFT:#方向键左键
            move_x = -1
        elif event.key == K_RIGHT:
            move_x = +1
        elif event.key == K_UP:
            move_y = -1
        elif event.key == K_DOWN:
            move_y = 1

    elif event.type == KEYUP:#键盘放开
        move_x, move_y = 0, 0

    x += move_x
    y += move_y

    screen.fill((0, 0, 0))
    screen.blit(bakcground, (x, y))
    pygame.display.update()
