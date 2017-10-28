#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import sys
from bs4 import BeautifulSoup

headers = {'User-Agent': "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1"}
show_status = {
    "1": True,
    "2": False
}

def main():
    nvliu66_url = "https://www.douyu.com/156277"
    response = requests.get(nvliu66_url, headers=headers)
    # print(response.text)
    html_soup = BeautifulSoup(response.text, "html.parser")
    html_soup.find("script")

if __name__ == '__main__':
    # html_fp = open("../../temp.html", "w")
    # sys.stdout = html_fp
    main()
