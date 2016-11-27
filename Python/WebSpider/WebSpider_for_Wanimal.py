#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import re
import os
import sys
import requests


targetDir = r'E:/Picture/Python'

# 这是一个黄图网站， 嗯
# mainweburl = weburl = 'http://www.tubaiwan.com'
mainweburl = weburl = 'http://wanimal1983.org/'
# http://wanimal1983.org/archive


# 获取图片的正则表达式
re_Img = re.compile('(http:[^\"\$\;\:]*(jpg|png|gif|bmp))')

# 获取跳转链接的正则表达式
re_Href = re.compile('(href\s?=\s?\"[^\"]*\")')

# 从href 的结果中提取链接
re_GetLinkFromHref = re.compile('((http|\/)[^\"\$\;]*)')

# 代理
prox_hanlder = urllib.request.ProxyHandler({'http': 'http://127.0.0.1:1874'})

# 代理的第二种解决方案，但似乎没有生效的样子, 只会返回www.google.com/chrome 的网址, 获取是lantern默认的跳转的问题
# opener = urllib.request.build_opener(prox_hanlder)
# urllib.request.install_opener(opener)


# 仿浏览器
head_info = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.87 Safari/537.36',
             'Connection': 'keep-alive',
             'Proxy-Connection': 'keep-alive'}
             # 'Host': 'www.tumblr.com'}


def dest_file(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos + 1:])
    return t


# 用于存储已经爬过的url 需要占用大量的内存，内存浪费多。
all_url_set = set()


# 从链接中获取图片
def get_img_from_url(url):
    req = urllib.request.Request(url=url, headers=head_info)
    web_page = urllib.request.urlopen(req)

    try:
        page_data = web_page.read().decode('utf-8')
    except Exception as e:
        page_data = web_page.read().decode('gbk')

    for n in set(re_Img.findall(page_data)):
        imgfile = n[0]
        print('正在获取图片：' + imgfile)

        # try:
        #     urllib.request.urlretrieve(imgfile, dest_file(imgfile))
        # except Exception :
        #     print('获取失败...')


if __name__ == '__main__':
    # 判断图片大小 做一些简单的过滤
    # 多线程爬
    get_img_from_url(mainweburl)
