#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup
# import sys
# reload(sys)

headers = {'User-Agent': "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1"}
dir_name = 'E:\Picture\meizitu'
proxies = {'http': 'http://127.0.0.1:50662'}  # lantern代理

href = "http://cecepa.com/artjq/jipinluolishaonvyinghuaxiliezhileisinayi114P/%INDEX%"  # %s = /index2
# http://cecepa.com/artjq/jipinluolishaonvyinghuaxiliezhileisinayi114P/
# http://cecepa.com/artjq/jipinluolishaonvyinghuaxiliezhileisinayi114P/index2.html

num = 0
for n in range(1, 12):
    if n <= 1:
        page_url_tail = ""
    else:
        page_url_tail = "index" + str(n) + ".html"

    page_url = href.replace("%INDEX%", page_url_tail)
    print(page_url)
    page_html = requests.get(page_url, headers=headers)
    html_soup = BeautifulSoup(page_html.text, "html.parser")

    img_info_list = html_soup.find('div', class_='con').find_all('img')

    for img_info in img_info_list:
        num += 1
        img_name = img_info['alt'] + str(num)
        img_url = img_info['src']
        print(img_name, img_url)

        img = requests.get(img_url, headers=headers)
        img_name = dir_name + '\\' + img_name
        f = open(img_name + '.jpg', 'ab')  # 写入多媒体文件必须要 b 这个参数
        f.write(img.content)   # 多媒体文件要是用conctent
        f.close()
