#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import socket
import re, sys, os

targetDir = r'E:/Picture/Python'

weburl = "http://www.luoo.net/music/679?sid=12942"
#weburl = "http://www.google.com"

def destFile(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos+1:])
    return t

if __name__ == '__main__':
    #伪装报头
    headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.113 Safari/537.36'}

    #设置代理
    #proxies = {'http':'http://127.0.0.1:16823'}

    req = urllib.request.Request(url=weburl, headers=headers)

    webpage = urllib.request.urlopen(req)
    contentBytes = webpage.read().decode('utf-8')

    for link in set(re.findall(r'(http:(.)*(jpg|png|gif))', str(contentBytes))):
        print(link[0])
        try:
            urllib.request.urlretrieve(link[0], destFile(link[0]))
        except:
            print('获取失败...')