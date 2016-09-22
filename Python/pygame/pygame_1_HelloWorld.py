#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
from sys import exit

background_image_filename = 'sushiplate.jpg'
mouse_image_filename = 'fugu.png'
# 指定图像文件名称
# 背景的 sushiplate.jpg应要有640×480的分辨率，
# 而光标的fugu.png大约应为80×80，而且要有Alpha通道（如果你不知道这是 什么，还是下载吧……）。

pygame.init() #初始化pygame,为使用硬件做准备

screen = pygame.display.set_mode((640, 480))# 创建一个窗口
# set_mode(resolution=(0,0), flags=0, depth=0)
# @depth 的range 为 8-32 表示彩色位、色深
# @flags 有如下多种参数
# pygame.FULLSCREEN    create a fullscreen display
# pygame.DOUBLEBUF     recommended for HWSURFACE or OPENGL      #创建一个“双缓冲”窗口，建议在HWSURFACE或者OPENGL时使用
# pygame.HWSURFACE     hardware accelerated, only in FULLSCREEN #创建一个硬件加速的窗口，必须和FULLSCREEN同时使用
# pygame.OPENGL        create an OpenGL renderable display
# pygame.RESIZABLE     display window should be sizeable
# pygame.NOFRAME       display window will have no border or controls

pygame.display.set_caption('Hello world!') #设置标题

background   = pygame.image.load(background_image_filename).convert()
mouse_cursor = pygame.image.load(mouse_image_filename).convert_alpha()
# 加载并转换图像
# convert函数是将图像数据都转化为Surface对象，每次加载完图像以后就应该做这件事件（事实上因为 它太常用了，如果你不写pygame也会帮你做）；
# convert_alpha相比convert，保留了Alpha 通道信息（可以简单理解为透明的部分），这样我们的光标才可以是不规则的形状。

while True: # the main loop of game progress
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()

    screen.blit(background,(0,0)) #将背景图画上去
    x, y = pygame.mouse.get_pos() #获取鼠标坐标

    x -= mouse_cursor.get_width()/2
    y -= mouse_cursor.get_height()/2
    screen.blit(mouse_cursor,(x,y))

    # blit是个重要函数，第一个参数为一个Surface对象，第二个为左上角位置。
    # 画完以后一定记得用update更新一下，否则画面一片漆黑。

    pygame.display.update() #刷新画面