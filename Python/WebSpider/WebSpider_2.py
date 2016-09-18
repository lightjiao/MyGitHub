#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
'''urllib中的parse用来对url解析'''
import urllib.parse
import json

fp = open('C:/Users/Lights/Desktop/temp.log')

url = "http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=null"

content = fp.readline()

data = {}
data['type']='AUTO'
data['i'] = content
data['doctype'] = 'json'
data['xmlVersion'] = '1.8'
data['keyfrom'] = 'fanyi.web'
data['ue'] = 'UTF-8'
data['typoResult'] = 'true'
data = urllib.parse.urlencode(data).encode('utf-8')

#伪装浏览器请求
head = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.113 Safari/537.36'}
req = urllib.request.Request(url=url, headers=head)
#req.add_header()

#设置代理


webPage = urllib.request.urlopen(req, data)
htmltext = webPage.read().decode('utf-8')

target =json.loads(htmltext)

print ("翻译结果是：%s" %(target['translateResult'][0][0]['tgt']))