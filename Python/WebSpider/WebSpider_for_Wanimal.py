#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import re
import os
import itertools
from PIL import Image
from io import BytesIO
from collections import deque

targetDir = "/Users/lights/Desktop/pic"
file_name = "./all_img_url.txt"
proxies = {'http': 'http://192.168.100.131:8080'}

# 获取图片的正则表达式
re_Img = re.compile('(http:[^\"\$\;\:]*(jpg|png|bmp))')

# 仿浏览器
head_info = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.87 Safari/537.36',
             'Connection': 'keep-alive',
             'Proxy-Connection': 'keep-alive'}


def dest_file(path):
    if not os.path.isdir(targetDir):
        os.mkdir(targetDir)

    pos = path.rindex('/')
    t = os.path.join(targetDir, path[pos + 1:])
    return t


def get_img_url_from_web(page_num, url, fp):
    """
    获取网页中的所有图片链接
    :param page_num:
    :param url:
    :param fp:
    :return:
    """

    ret = requests.get(url=url, proxies=proxies).text

    for img_url, other in set(re_Img.findall(ret)):
        print('PAGE[%s]:正在获取图片链接：%s' % (str(page_num), img_url))
        # 将所有链接写入文件
        fp.writelines(str(page_num) + "," + img_url + "\n")


def generate_all_web_url():
    """
    遍历所有url，WANIMAL的url结构很简单
    :return:
    """
    main_url = url = 'http://wanimal1983.org/'

    with open(file_name, "w") as fp:
        for page_num in itertools.count(1):

            if page_num > 1:
                url = main_url + "page/" + str(page_num)

            if page_num > 150:
                break

            get_img_url_from_web(page_num, url, fp)
            print("翻页 url: %s" % url)


"""保存最近的20个链接，为了去除掉小图片"""
latest_20_img_url = deque(maxlen=20)


def generate_all_url_from_txt():
    """
    遍历文本文件中所有的链接, 会比较近五个链接是否类似
    :return:
    """
    with open(file_name, "r") as fp:
        count = 0
        while True:
            count += 1
            if count > 20:
                break

            url_info = fp.readline().split(",")
            img_url = url_info[1].strip()

            if img_url[:86] in latest_20_img_url:
                continue
            latest_20_img_url.append(img_url[:86])

            download_img(url_info[0], img_url)


def download_img(page_num, img_url):
    """
    :param page_num:
    :param img_url:
    :return:
    """
    try:
        content = requests.get(url=img_url, proxies=proxies).content
        img = Image.open(BytesIO(content))
        img.save(dest_file(img_url))
        print("Page[%s]获取图片成功: %s" % (page_num, img_url))
    except requests.RequestException:
        print("Page[%s]获取图片失败: %s" % (page_num, img_url))


def analyse_txt():
    """
    仅仅只是过滤一下扒下来的url文件
    :return:
    """
    with open(file_name, "r") as fp:
        count_dict = {}

        while True:
            url_info = fp.readline()
            if url_info == "":
                break
            url = url_info.split(",")[1].strip()
            core_str = url[:86]

            if core_str in count_dict:
                count_dict[core_str][0] += 1
                count_dict[core_str].append(url)
            else:
                count_dict[core_str] = list([1, url])

        with open("./new_url.txt", "w") as newfp:
            for k, v in count_dict.items():
                new_url = ""
                if v[0] > 1:
                    for i in range(v[0]):
                        if v[i+1].find("500") != -1:
                            new_url = v[i+1]
                            break
                        new_url = ""

                else:
                    new_url = v[1]

                if new_url == "":
                    continue

                print(new_url)

                newfp.write(new_url + "\n")


if __name__ == '__main__':
    # 判断图片大小 做一些简单的过滤
    # 多线程爬
    # get_img_from_url(mainweburl)
    # generate_all_web_url()
    # generate_all_url_from_txt()
    # analyse_txt()
    pass
