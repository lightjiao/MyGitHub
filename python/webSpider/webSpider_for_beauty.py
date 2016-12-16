#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import socket
import re, sys, os

targetDir = r'E:/Picture/Python'

mainweburl = weburl = 'http://www.tubaiwan.com' #这是一个黄图网站， 嗯

re_Img = re.compile(r'(http:[^\"\$\;]*(jpg|png|gif|bmp))') #获取图片的正则表达式

re_Href = re.compile(r'(href\s?=\s?\"[^\"]*\")') #获取跳转链接的正则表达式
re_GetLinkFromHref = re.compile(r'((http|\/)[^\"\$\;]*)') #从href 的结果中提取链接
re_Tubaiwan = re.compile(r'\.*')
#re_GetLinkFromHref.findall(n)[0][1:-1] #获取纯净的href链接

def destFile(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos+1:])
    return t

#用于存储已经爬过的url 需要占用大量的内存，内存浪费多。
allUrlSet = set()

#从链接中获取新的链接
def GetHrefFromUrl(url):
    webPage = urllib.request.urlopen(url)
    try:
        pageData = webPage.read().decode('utf-8')
    except Exception as e:
        pageData = webPage.read().decode('gbk')

    for n in set(re_Href.findall(pageData)):
        url = re_GetLinkFromHref.findall(n)[0][0]
        if not url.startswith('http'):
            tempurl = 'http://www.tubaiwan.com' + url
            url = tempurl
        if -1 != url.find('www.tubaiwan'):
            print('获取跳转链接：' + url)
            if url not in allUrlSet:
                allUrlSet.add(url)
                GetImgFromUrl(url)



#从链接中获取图片
def GetImgFromUrl(url):
    webPage = urllib.request.urlopen(url)
    try:
        pageData = webPage.read().decode('utf-8')
    except Exception as e:
        pageData = webPage.read().decode('gbk')

    for n in set(re_Img.findall(pageData)):
        imgfile = n[0]
        print('正在获取图片：' + imgfile)
        try:
            urllib.request.urlretrieve(imgfile, destFile(imgfile))
        except:
            print('获取失败...')


if __name__ == '__main__':
    # 判断图片大小 做一些简单的过滤
    # 判断链接是否已经爬过了，用数组判断
    # 多线程爬
    # 判断站内站外的链接， 有些链接时需要 做拼接后才能访问的
    GetHrefFromUrl(mainweburl)