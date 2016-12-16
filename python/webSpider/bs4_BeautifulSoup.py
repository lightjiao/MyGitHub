#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import re
import os
import itertools
from PIL import Image
from io import BytesIO
from collections import deque
from bs4 import BeautifulSoup

targetDir = "E:/Picture/Python" # windows目录


def dest_file(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos + 1:])
    return t


proxies = {'http': 'http://127.0.0.1:1875'}

main_url = url = 'http://wanimal1983.org/page/5'

# jpg|png = 110 条数据
html_str = requests.get(url=url, proxies=proxies).text

soup = BeautifulSoup(html_str, 'html.parser')

for img in soup.find_all('img'):
    print(img.get("src"))
    img_url = img.get("src")
    try:
        content = requests.get(url=img_url, proxies=proxies).content
        img = Image.open(BytesIO(content))
        img.save(dest_file(img_url))
        print("获取图片成功: %s" % (img_url))
    except requests.RequestException:
        print("获取图片失败: %s" % (img_url))
