#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup

headers = {'User-Agent': "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1"}
dir_name = 'E:\Picture\meizitu'

# href = "http://www.mzitu.com/87022"
# 夏瑶
href = "http://www.mzitu.com/41517"
href = "http://www.mzitu.com/44709"
href = "http://www.mzitu.com/44080"
href = "http://www.mzitu.com/41937"
href = "http://www.mzitu.com/41633"
href = "http://www.mzitu.com/40840"
href = "http://www.mzitu.com/40464"

# gina
href = "http://www.mzitu.com/85012"
href = "http://www.mzitu.com/84151"

# rosi
href = "http://www.mzitu.com/29557"

# other
href = "http://www.mzitu.com/88458"
href = "http://www.mzitu.com/84703"
href = "http://www.mzitu.com/37221"

# 七喜
href = "http://www.mzitu.com/22486"

# 语纯



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

    img = requests.get(img_url, headers=headers)
    f = open(img_name + '.jpg', 'ab')  # 写入多媒体文件必须要 b 这个参数
    f.write(img.content)   # 多媒体文件要是用conctent
    f.close()
