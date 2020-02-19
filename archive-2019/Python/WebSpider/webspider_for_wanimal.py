#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import os
from PIL import Image
from io import BytesIO
from bs4 import BeautifulSoup
from multiprocessing import pool

# targetDir = "/Users/lights/Desktop/pic" # linux目录
targetDir = "E:/Picture/wanimal"  # windows目录s
file_name = "./all_img_url.txt"
# proxies = {'http': 'http://192.168.100.131:8080'} # 公司的代理
proxies = {'http': 'http://127.0.0.1:1875'}  # lantern代理

# 记录文件是否已经存在的计数，超过一定次数则程序终止
file_exists_count = 0

def dest_file(path):
    """
    生成文件路径并判断文件是否已经存在，超过十个文件存在则返回false
    :param path:
    :return:
    """
    global file_exists_count
    print(file_exists_count)

    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos + 1:])

    if os.path.isfile(t) :
        file_exists_count += 1
    if file_exists_count > 10:
        return False

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
            print("获取主页面失败: %s" % url)


def get_img_url_from_html(page_num, html_str):
    """
    解析html文本并获取图片
    :param page_num:
    :param html_str:
    :return:
    """
    thread_pool = pool.Pool(10)  # 线程池
    soup = BeautifulSoup(html_str, 'html.parser')
    for img in soup.find_all('img'):
        img_url = img.get("src")
        if img_url != "" or img_url is not None:
            thread_pool.apply_async(download_img_from_url, args=(page_num, img_url))
            # download_img_from_url(page_num, img_url)

    print('Waiting for all subprocesses done...')
    thread_pool.close()
    thread_pool.join()
    print('All subprocesses done.')


def download_img_from_url(page_num, img_url):
    """
    从url中下载图片
    :param page_num:
    :param img_url:
    :return:
    """
    try:
        content = requests.get(url=img_url, proxies=proxies).content
        img = Image.open(BytesIO(content))

        filename = dest_file(img_url)
        print(filename)
        # if filename is not False:
        #     img.save()
        # else :
        #     print("已经存在重复的十个文件，程序终止......")
        #     return
        # print("Page[%s]获取图片成功: %s" % (str(page_num), img_url))
    except requests.RequestException:
        print("Page[%s]获取图片失败: %s" % (str(page_num), img_url))


if __name__ == '__main__':
    generate_all_page()
