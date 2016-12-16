#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame
from pygame.locals import *
from sys import exit

pygame.init()
SCREEN_SIZE = (640, 480)
screen = pygame.display.set_mode(SCREEN_SIZE)

font = pygame.font.SysFont('arial', 16)
font = pygame.font.SysFont('宋体', 20)
font_height = font.get_linesize()
event_text = []

zhongwen_text_surface = font.render(u'你好', True, (0, 0, 255))  # 依旧显示不了汉字

while True:
    event = pygame.event.wait()
    # 上个程序中，使用了pygame.event.get() 来处理所有的事件，这好像打开大门让所有的人进入。  #for event in pygame.event.get():
    # 如果我们使用pygame.event.wait()，Pygame就会等到发生一个事件才继续下去，就好像你在门的猫眼上盯着外面一样，来一个放一个……一般游戏中不太实用，因为游戏往往是需要动态运作的；
    # 而另外一个方法pygame.event.poll() 就好一些，一旦调用，它会根据现在的情形返回一个真实的事件，或者一个“什么都没有”
    event_text.append(str(event))
    event_text = event_text[int(-SCREEN_SIZE[1]/font_height):] #这个切片操作保证了event_text里面只保留一个屏幕的文字

    if event.type == QUIT:
        exit()

    screen.fill((255, 255, 255)) #fill Surface with a solid color(solid color 纯色)

    y = SCREEN_SIZE[1] - font_height #找一个合适的起笔的位置， 最下面开始但是要留一行的空
    for text in reversed(event_text):
        screen.blit(font.render(text, True, (0, 0, 0)), (0, y)) #后面再说这个

        y -= font_height #把笔提一行
        screen.blit(zhongwen_text_surface, (0, y))
        y -= zhongwen_text_surface.get_width()  # 把笔提一行

    pygame.display.update()