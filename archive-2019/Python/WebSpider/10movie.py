#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import sys
from bs4 import BeautifulSoup

headers = {'User-Agent': "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1"}
number_10_movie_url = "http://tv.cntv.cn/videoset/C14345/page/"

def main():
    for n in range(1, 10):
        url = number_10_movie_url + str(n)
        response = requests.get(url, headers=headers)
        # print(response.text)
        html_soup = BeautifulSoup(response.text, 'html.parser')
        content = html_soup.find('div', class_='image_list').find_all('img')
        for n in content:
            print(n.get("title"))
            # print(type(n))
        # print(content)

if __name__ == '__main__':
    # html_fp = open("../../temp.html", "w")
    # sys.stdout = html_fp
    main()
