#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame, sys
from pygame.locals import *
from random import randint

snakelen  = 0                                  #蛇的长度
snakepos  = (randint(0, 640), randint(0, 480)) #蛇的起始位置
snakedest = randint(0, 3)                      #蛇的方向

if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((640, 480))
    screen.fill((0, 0, 0))

    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                sys.exit()

            if event.type == KEYDOWN and event.key == K_SPACE:
                snakelen += 1
                snakepos = (randint(0, 640), randint(0, 480))  # 蛇的起始位置
                pygame.draw.rect(screen, (255, 255, 255), (snakepos[0], snakepos[1], 640, 10), 2)



        pygame.display.update()