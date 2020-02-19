#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup
from mztu_href import get_href

headers = {
    'User-Agent': "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1",
}
dir_name = 'E:\Picture\meizitu'


def webspider_img(href):
    """
    请求页面下载图片
    """
    html = requests.get(href, headers=headers)

    # html_soup = BeautifulSoup(html.text, 'lxml')
    html_soup = BeautifulSoup(html.text, "html.parser")
    max_span = html_soup.find('div', class_='pagenavi').find_all('span')[-2].get_text()

    for page in range(1, int(max_span) + 1):
        page_url = href + '/' + str(page)
        img_html = requests.get(page_url, headers)
        img_soup = BeautifulSoup(img_html.text, 'html.parser')
        img_url = img_soup.find('div', class_='main-image').find('img')['src']
        title = img_soup.find('div', class_='main-image').find('img')['alt']
        img_name = title + str(page)
        img_name = dir_name + '\\' + img_name

        # img_name = img_name.replace(" ", "")
        print(img_name, img_url)

        download_headers = headers
        download_headers['Referer'] = page_url

        img = requests.get(img_url, headers=headers)
        f = open(img_name + '.jpg', 'ab')  # 写入多媒体文件必须要 b 这个参数
        f.write(img.content)   # 多媒体文件要是用conctent
        f.close()


href = get_href()
href = [
    "http://www.mzitu.com/74394",
    "http://www.mzitu.com/62069",
    "http://www.mzitu.com/69132",
    "http://www.mzitu.com/82608",
    "http://www.mzitu.com/60054",
    "http://www.mzitu.com/70521",
    "http://www.mzitu.com/47760",
    "http://www.mzitu.com/31835",
    "http://www.mzitu.com/38380",
    "http://www.mzitu.com/67374",
    "http://www.mzitu.com/73654",
    "http://www.mzitu.com/4978",
    "http://www.mzitu.com/71176",
    "http://www.mzitu.com/63704",
]


a = [
    # 唐琪儿
    "http://www.mzitu.com/83148",
    "http://www.mzitu.com/98617",
    "http://www.mzitu.com/97854",
    "http://www.mzitu.com/92165",
    "http://www.mzitu.com/85377",
    "http://www.mzitu.com/85063",
]

mztu_href_20170812 = [
    "http://www.mzitu.com/98801",
    "http://www.mzitu.com/99566",
    "http://www.mzitu.com/99617",
    "http://www.mzitu.com/99666",
]

xiameijiang = [
    "http://www.mzitu.com/99413",
    "http://www.mzitu.com/98966",
    "http://www.mzitu.com/95122",
    "http://www.mzitu.com/94220",
    "http://www.mzitu.com/58157",
    "http://www.mzitu.com/55775",
    "http://www.mzitu.com/54427",
    "http://www.mzitu.com/53071",
    "http://www.mzitu.com/50574",
]
for n in xiameijiang:
    webspider_img(n)


