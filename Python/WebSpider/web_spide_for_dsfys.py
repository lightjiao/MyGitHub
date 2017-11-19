# !/usr/local/easyops/python/bin/python
# !-*- coding:utf-8 -*-

import datetime
import json
import requests
import hashlib
import time


def get_number_ten_content(page=1, page_size=50):
    """
    hack了一下官方的源代码，解析出来了官网后台的api，直接用api获取内容
    :return json: {
        "start": "0",
        "docs": [
            {
                "videoBrief": "本期节目主要内容: aaa",
                "videoThirdclass": "",
                "videoSecondclass": "文化,人物",
                "videoUrl": "http://tv.cctv.com/2017/06/07/VIDEARVDmbVbhFewOmcefmQ4170607.shtml",
                "videoEditMode": "0",
                "videoTitle": "《第10放映室》 20170606 美人吟——李玲玉",
                "videoFirstclass": "科教",
                "videoPlaystyle": "",
                "videoFocusDate": "1496772268000",
                "videoKeyFrameUrl": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a5485e290cae25b-730.jpg",
                "videoMediaType": "",
                "videoPublishFlg": "1",
                "videoSharedCode": "4f1e758a548b48e894cff5e290cae25b",
                "videoChannel": "",
                "videoId": "VIDEARVDmbVbhFewOmcefmQ4170607",
                "videoLength": "00:24:17",
                "videoLastmodifyDate": "1496791234000",
                "videoDeleteFlg": "0",
                "videoProductiontime": "1496771560000",
                "videoKeyFrameUrl2": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a548b48e290cae25b-1462.jpg",
                "videoKeyFrameUrl3": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a548b48e894ccae25b-730.jpg"
            }
        ],
        "numFound": "589"
    },
    """
    hack_url = "http://api.cntv.cn/lanmu/videolistByColumnId"
    querystring = {
        "id": "TOPC1451557487468814",
        "serviceId": "tvcctv",
        "type": "0",
        "n": str(page_size),  # 分页大小
        "p": str(page),  # 页码
        "t": "jsonp",
        "cb": "setItemByidELMTKErbhqmil6kE9iFZpnJ1170306"
    }

    headers = {
        'cache-control': "no-cache",
        'postman-token': "f8368899-20b0-a5e3-ae6b-fee4bfc2838c"
    }
    response = requests.get(url=hack_url, params=querystring, headers=headers)
    if response.status_code != 200:
        raise Exception("Get html failed", hack_url)
    response_data = json.loads(response.text[response.text.find("{"):-2])["response"]
    # count = response_data["numFound"]
    data = parse_number_ten_content(response_data)
    return data


def parse_number_ten_content(content):
    """
    解析内容
    """
    docs = content["docs"]
    for doc in docs:
        doc["name"] = doc["videoTitle"]
        try:
            video_productiontime = datetime.datetime.fromtimestamp(int(doc["videoProductiontime"]) / 1000).strftime(
                '%Y-%m-%d')
        except ValueError:
            video_productiontime = ""
        doc["videoProductiontime"] = video_productiontime
    return docs


def request_cmdb(method, uri, data=None):
    """
    请求CMDB
    :param method:
    :param uri:
    :param data:
    :return:
    """
    cmdb_header = {
        "host": "cmdb.easyops-only.com",
        "user": "lightjiao",
        "org": "1573353097"
    }
    if data is None:
        data = {}

    uri = uri.lstrip("/ ")
    url = "http://easyops.cn/%s" % uri
    response = requests.request(method, url=url, json=data, headers=cmdb_header)
    if response.status_code != 200:
        if "code" in response.json():
            raise IndexError("duplicate data", data, response.json())
        raise Exception("request cmdb failed", url, data, response.text)

    response_data = response.json()["data"]
    return response_data


def get_video_id_from_cmdb(video_id_list=None):
    """
    获取所有的videoId或者获取指定的videoId
    :param video_id_list:
    :return:
    """
    body = {
        "fields": {"videoId": 1, "instanceId": 1},
        "sort": {"instanceId": -1},
        "page_size": 3000
    }
    if video_id_list is not None:
        body["query"] = {"videoId": {"$in": video_id_list}}

    response_data = request_cmdb("POST", "/object/NumberTen/instance/_search", body)
    response_data_list = response_data["list"]
    return [item["videoId"] for item in response_data_list]


def send_email(instance_data, email_address="lightjiao@easyops.cn"):
    """
    发送通知邮件
    :param instance_data:
    :param email_address:
    :return:
    """
    message = ""
    for k, v in instance_data.items():
        message += "%-10s:%s" % (str(k), str(v))
        message += "\n\n"

    body = {
        "subject": "第十放映室节目更新啦!",
        "sendTo": email_address,
        "msg": message
    }

    response = request_cmdb("POST", "/message/email", body)
    print(response.json)


def discovery(content_list):
    video_id_list = []
    # 统计video_id
    for content in content_list:
        # 没有ID则创建一个ID
        if "videoId" not in content:
            content["videoId"] = hashlib.sha1(content["name"] + content["videoUrl"]).hexdigest()
        video_id_list.append(content["videoId"])

    video_id_list_in_cmdb = get_video_id_from_cmdb(video_id_list)
    for content in content_list:
        # 没有ID则创建一个ID
        if "videoId" not in content:
            content["videoId"] = hashlib.sha1(content["name"] + content["videoUrl"]).hexdigest()

        # ID已经在CMDB中存在则忽略
        video_id = content["videoId"]
        if video_id in video_id_list_in_cmdb:
            continue

        # 创建CMDB记录并且发出邮件
        try:
            instance_data = request_cmdb("POST", "/object/NumberTen/instance", content)
        except IndexError:
            content["name"] = content["name"] + str(time.time())
            instance_data = request_cmdb("POST", "/object/NumberTen/instance", content)

        print(instance_data["name"], instance_data["videoUrl"])
        send_email(instance_data=instance_data)


def discovery_all():
    """
    第一次运行的时候执行这个函数将所有的数据写入到CMDB
    :return:
    """
    page = 1
    page_size = 100
    for n in range(100):
        content_list = get_number_ten_content(page, page_size)
        if len(content_list) == 0:
            break
        discovery(content_list)
        page = page + 1


if __name__ == '__main__':
    response_content_list = get_number_ten_content(1, 20)
    discovery(response_content_list)
