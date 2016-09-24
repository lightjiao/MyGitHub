#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pygame, sys
from pygame.locals import *
from random import randint

snake      = [(16, 12),(17, 12),(18, 12),(19, 12),(20, 12)]       #蛇的身体所在的坐标, 蛇的身体是20*20 的像素方格
snakepos   = (randint(0, 32), randint(0, 24))   #蛇的起始位置 蛇的身体是20*20 的像素方格(640/20 = 32, 480/20 = 24)，其中一半黑色一半白色
snakespeed = 250                                #贪吃蛇的速度
snakedest  = 2                                  #蛇的方向

time = 0

destUP    = lambda pos: (pos[0], pos[1] - 1)
destDown  = lambda pos: (pos[0], pos[1] + 1)
destLeft  = lambda pos: (pos[0] - 1, pos[1])
destRight = lambda pos: (pos[0] + 1, pos[1])

destList  = [destUP, destDown, destLeft, destRight]

snakemove = lambda snake, dest: [dest(snake[0])] + snake[:-1]
snakegrow = lambda snake, dest: [dest(snake[0])] + snake

def newfoodpos():
    foodpos = (randint(0, 32), randint(0, 24))
    while foodpos in snake:
        foodpos = (randint(0, 32), randint(0, 24))
    return foodpos

def drawSnake(snake):
    _x, _y = -1, -1
    for (x, y) in snake:
        pygame.draw.rect(screen, (255, 255, 255), (x * 20, y * 20, 10, 10))

        if (_x == -1):
            _x, _y = x, y
        elif (_x == x):
            _y = (_y + y) / 2
        elif (_y == y):
            _x = (_x + x) / 2
        pygame.draw.rect(screen, (255, 255, 255), (_x * 20, _y * 20, 10, 10)) #画出两个节点中间的部分，显示的更好看一些
        _x, _y = x, y




if __name__ == '__main__':
    pygame.init()
    screen = pygame.display.set_mode((640, 480))

    FPSClock = pygame.time.Clock()

    foodpos = newfoodpos()

    while True:
        timePassed = FPSClock.tick(30)
        if time > snakespeed:
            time = 0
            snake = snakemove(snake, destList[snakedest])
        else:
            time += timePassed

        for event in pygame.event.get():
            if event.type == QUIT:
                sys.exit()

            if event.type == KEYDOWN:
                if event.key == K_UP and snakedest != destList.index(destDown):
                    snakemove(snake, destUP)
                    snakedest = destList.index(destUP)
                elif event.key == K_DOWN and snakedest != destList.index(destUP):
                    snakemove(snake, destDown)
                    snakedest = destList.index(destDown)
                elif event.key == K_LEFT and snakedest != destList.index(destRight):
                    snakemove(snake, destLeft)
                    snakedest = destList.index(destLeft)
                elif event.key == K_RIGHT and snakedest != destList.index(destLeft):
                    snakemove(snake, destRight)
                    snakedest = destList.index(destRight)

                elif event.key == K_SPACE:
                    pass #暂停

        #吃到食物
        if snake[0] == foodpos:
            snake = snakegrow(snake, destList[snakedest])
            foodpos = newfoodpos()
            snakespeed -= 1

        #判断输赢
        if snake[0] in snake[1:] or snake[0][0] < 0 or snake[0][0] > 32 or snake[0][1] < 0 or snake[0][1] > 24:
            print(snake)
            print('game over')
            break

        screen.fill((0, 0, 0))

        #画出snake
        drawSnake(snake)

        pygame.draw.circle(screen, (255, 255, 255), (foodpos[0]*20 + 5, foodpos[1]*20 + 5), 5)

        pygame.display.update()