#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup
import os


headers = {'User-Agent':"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1"}##浏览器请求头（大部分网站没有这个请求头会报错、请务必加上哦）
all_url = 'http://www.mzitu.com/all'
dir_name = 'E:\Picture\meizitu'

start_html = requests.get(all_url,  headers=headers)

soup = BeautifulSoup(start_html.text, 'lxml')

all_a = soup.find('div', class_='all').find_all('a')

# meizitu.net/2016/11/19c64.jpg
# E:\Picture\meizitu\甜美性感MM陈梓涵私拍图 肤白貌美大长腿,胸挺腰细气质佳65 http://i.meizitu.net/2016/11/19c65.jpg
# E:\Picture\meizitu\夹一下可好? 日本性感女神中村静香大秀爆乳 F级肉弹胸悍无比1 http://i.meizitu.net/2016/11/19a01.jpg
for n in all_a:
    title = n.get_text()
    href = n.get('href')

    html = requests.get(href, headers=headers)
    html_soup = BeautifulSoup(html.text, 'lxml')
    max_span = html_soup.find('div', class_='pagenavi').find_all('span')[-2].get_text()

    for page in range(1, int(max_span) + 1):
        page_url = href + '/' + str(page)
        img_html = requests.get(page_url, headers)
        img_soup = BeautifulSoup(img_html.text, 'lxml')
        img_url = img_soup.find('div', class_='main-image').find('img')['src']
        img_name = title + str(page)
        img_name = dir_name + '\\' + img_name

        print(img_name, img_url)

        img = requests.get(img_url, headers=headers)
        f = open(img_name+'.jpg', 'ab')  ##写入多媒体文件必须要 b 这个参数！！必须要！！
        f.write(img.content)   ##多媒体文件要是用conctent哦！
        f.close()
