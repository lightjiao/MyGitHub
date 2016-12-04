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

# targetDir = "/Users/lights/Desktop/pic" # linux目录
targetDir = "E:/Picture/Python"  # windows目录
file_name = "./all_img_url.txt"
# proxies = {'http': 'http://192.168.100.131:8080'} # 公司的代理
proxies = {'http': 'http://127.0.0.1:1875'} # lantern代理

def dest_file(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos + 1:])
    return t

def generate_all_page():
    """
    遍历所有的wanimal的页面
    :return:
    """
    main_url = url = 'http://wanimal1983.org'
    for page_num in range(150):
        if page_num <= 0:
            continue
        if page_num > 1:
            url = main_url + "/page/" + str(page_num)

        try:
            html_str = requests.get(url=url, proxies=proxies).text
            get_img_url_from_html(page_num, html_str)
        except requests.RequestException:
            print("获取主页面失败: %s" % (url))


def get_img_url_from_html(page_num, html_str):
    """
    解析html文本并获取图片
    :param page_num:
    :param url:
    :return:
    """
    soup = BeautifulSoup(html_str, 'html.parser')
    for img in soup.find_all('img'):
        img_url = img.get("src")
        if img_url != "" or img_url != None:
            download_img_from_url(page_num, img_url)


def download_img_from_url(page_num, img_url):
    """
    从url中下载图片
    :param page_num:
    :param url:
    :return:
    """
    try:
        content = requests.get(url=img_url, proxies=proxies).content
        img = Image.open(BytesIO(content))
        img.save(dest_file(img_url))
        print("Page[%s]获取图片成功: %s" % (str(page_num), img_url))
    except requests.RequestException:
        print("Page[%s]获取图片失败: %s" % (str(page_num), img_url))


if __name__ == '__main__':
    # 需要解决的问题: 多线程爬虫
    generate_all_page()
