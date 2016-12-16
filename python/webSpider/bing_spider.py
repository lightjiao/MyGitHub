#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import re, os, xml.dom.minidom

targetDir = r'E:/Picture/Python'

mainweburl = 'http://cn.bing.com/HPImageArchive.aspx?idx=%INDEX%&n=10'

def destFile(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos+1:])
    return t

if __name__ == '__main__':
    AllUrlSet = set()
    for index in range(20):
        weburl = mainweburl.replace('%INDEX%', str(index))
        print(weburl)
        webpage = urllib.request.urlopen(weburl)
        contentBytes = webpage.read().decode('utf-8')
        try:
            XMLDom = xml.dom.minidom.parseString(contentBytes)
            XMLRoot = XMLDom.documentElement
            _files = XMLRoot.getElementsByTagName('url')
            for n in _files:
                urlcontent = n.firstChild.data
                urlcontent = urlcontent.replace('1366x768', '1920x1080')
                urlcontent = 'http://s.cn.bing.net' + urlcontent
                if urlcontent not in AllUrlSet:
                    AllUrlSet.add(urlcontent)
                    print(urlcontent)
                    try:
                        urllib.request.urlretrieve(urlcontent, destFile(urlcontent))
                    except:
                        print('获取失败...')
        except Exception as e:
            print('获取结束...')
            break