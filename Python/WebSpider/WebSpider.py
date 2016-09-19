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


    #伪装报头
    # headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.113 Safari/537.36'}
    # req = urllib.request.Request(url=weburl, headers=headers)

    webpage = urllib.request.urlopen(weburl)
    contentBytes = webpage.read().decode('utf-8')
    test_contentBytes = "http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u552446_1430186635.jpg?imageView2/1/w/128/h/128'"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u10248201462363342.jpg?imageView2/1/w/128/h/128' />"\
                   "+<img src='http://www.luoo.net/static/img/avatar.gif' />"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u537417_1419078283.jpg?imageView2/1/w/128/h/128' class='rounded' title='Shinzo'/>"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u553855_1419758975.jpg?imageView2/1/w/128/h/128' class='rounded' title='Young-1996'/>"\
                   "<img src='http://www.luoo.net/static/img/avatar.gif'/>"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u538890_1419156708.jpg?imageView2/1/w/128/h/128' class='rounded' title='Meepoooooooo'/>"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u689330_1428054958.jpg?imageView2/1/w/128/h/128' class='rounded' title='林锦青'/>"\
                   "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u8256.jpg?imageView2/1/w/128/h/128' class='rounded' title='crystal'/>"

    test_contentBytes += '\n'\
                    "<img src='http://7xkszy.com2.z0.glb.qiniucdn.com/pics/avatars/u544811470473414.jpg?imageView2/1/w/128/h/128'"


    #print(contentBytes)
    n = re.search(r'(http:.*^[jpg].*(jpg|png|gif))', str(test_contentBytes))
    print(n.string)
    print('**********************************************\n')

    for link in set(re.findall(r'(http:.*^[jpg].*(jpg|png|gif))', str(contentBytes))):
        print(link)
        link = link[0]
        try:
            urllib.request.urlretrieve(link, destFile(link))
        except:
            print('获取失败...')