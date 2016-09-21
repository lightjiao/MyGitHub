#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import socket
import re, sys, os

targetDir = r'E:/Picture/Python'

weburl = 'http://www.luoo.net/music/679?sid=12942'
#weburl = 'http://cn.bing.com/'
#weburl = 'http://wanimal1983.org'

def destFile(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos+1:])
    return t

if __name__ == '__main__':
    # 设置代理
    # proxies = {'http': 'http://127.0.0.1:16823'}
    # proxise_support = urllib.request.ProxyHandler(proxies)
    # opener = urllib.request.build_opener(proxise_support)
    # urllib.request.install_opener(opener)

    #伪装浏览器请求
    # headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.113 Safari/537.36'}
    # req = urllib.request.Request(url=weburl, headers=headers)

    webpage = urllib.request.urlopen(weburl)
    contentBytes = webpage.read().decode('utf-8')

    re_srcimg = re.compile(r'(http:([^\"])*(jpg|png|gif))') #原来错误的正则表达式 (http:.*(jpg|png|gif)) 没有判断字符串的合法性
    for image in set(re_srcimg.findall(contentBytes)):
        imgfile = image[0]
        print(imgfile)
        try:
            urllib.request.urlretrieve(imgfile, destFile(imgfile))
        except:
            print('获取失败...')
