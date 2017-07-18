#!/usr/local/easyops/python/bin/python
#!-*- coding:utf-8 -*-

import datetime
import json
import hashlib, hmac, time, requests
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

ACCESSKEY = EASYOPS_OPEN_API_ACCESS
SECRETKEY = EASYOPS_OPEN_API_SECRET
def request_open_api(method, uri, body=None):
    """
    请求openapi
    """
    if body is not None:
        md5 = hashlib.md5()
        md5.update(body)
        body_md5 = md5.hexdigest()
    else:
        body_md5 = ""

    time_stamp = str(int(time.time()))
    string_to_signature = "\n".join([
            method,
            uri,
            "",
            "application/json",
            body_md5,
            time_stamp,
            ACCESSKEY]
        ).encode()
    secretkey_encode = SECRETKEY.encode()
    signature = hmac.new(secretkey_encode, string_to_signature, hashlib.sha1).hexdigest()

    url = "http://" + EASYOPS_OPEN_API_HOST + uri
    params = {"accesskey": ACCESSKEY, "signature": signature, "expires": time_stamp}
    headers = {"Host": "openapi.easyops-only.com", 'Content-Type': 'application/json'}

    return requests.request(method=method, url=url, data=body, headers=headers, params=params)


def count_instance(objectId="NumberTenScreeningRoom"):
    """
    获取第十放映室节目实例总数量
    """
    uri = "/cmdb/object/%s/instance" % "NumberTenScreeningRoom"
    response = request_open_api("GET", uri)
    return response.json()["data"]["total"]


def get_dsfys_content(page=1, page_size=50):
    """
    hack了一下官方的源代码，解析出来了官网后台的api，直接用api获取内容
    :return json: {
        "start": "0",
        "docs": [
            {
                "videoBrief": "本期节目主要内容：\n    李玲玉是中国乐坛第一位甜歌皇后，她曾创造八年录制八十八张专辑的疯狂纪录，二十四岁便已红遍中国及东南亚地区。在86版电视剧《西游记》中，李玲玉扮演的玉兔精和电视剧《孝庄秘史》中扮演的贵太妃都给观众留下了深刻印象。\n（《第10放映室》 20170606 美人吟——李玲玉）",
                "videoThirdclass": "",
                "videoSecondclass": "文化,人物",
                "videoUrl": "http://tv.cctv.com/2017/06/07/VIDEARVDmbVbhFewOmcefmQ4170607.shtml",
                "videoEditMode": "0",
                "videoTitle": "《第10放映室》 20170606 美人吟——李玲玉",
                "videoFirstclass": "科教",
                "videoPlaystyle": "",
                "videoFocusDate": "1496772268000",
                "videoKeyFrameUrl": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a548b48e894cff5e290cae25b-730.jpg",
                "videoMediaType": "",
                "videoPublishFlg": "1",
                "videoSharedCode": "4f1e758a548b48e894cff5e290cae25b",
                "videoChannel": "",
                "videoId": "VIDEARVDmbVbhFewOmcefmQ4170607",
                "videoLength": "00:24:17",
                "videoLastmodifyDate": "1496791234000",
                "videoDeleteFlg": "0",
                "videoProductiontime": "1496771560000",
                "videoKeyFrameUrl2": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a548b48e894cff5e290cae25b-1462.jpg",
                "videoKeyFrameUrl3": "http://p1.img.cctvpic.com/fmspic/2017/06/07/4f1e758a548b48e894cff5e290cae25b-730.jpg"
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
        "n": str(page_size),    # 分页大小
        "p": str(page),       # 页码
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
    response_content = json.loads(response.text[response.text.find("{"):-2])["response"]
    total = response_content["numFound"]
    return response_content, total


def parse_dsfys_content(content):
    """
    解析内容
    """
    print content
    docs = content["docs"]
    for doc in docs:
        doc["name"] = doc["videoTitle"]
        try:
            videoProductiontime = datetime.datetime.fromtimestamp(int(doc["videoProductiontime"])/1000).strftime('%Y-%m-%d')
        except ValueError as e:
            videoProductiontime = ""
        doc["videoProductiontime"] = videoProductiontime
    return docs


def search_latest_one_of_dsfys():
    """
    按创建时间排序获取最新的实例
    """
    body = {
        "sort": {"instanceId": -1},
        "page_size": 1
    }

    response = request_open_api("POST", "/cmdb/object/NumberTenScreeningRoom/instance/_search", json.dumps(body))
    return response.json()["data"]["list"][0]


def send_email(instance_data, email_address="lightjiao@easyops.cn"):
    """
    发送通知邮件
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

    response = request_open_api("POST", "/cmdb/message/email", json.dumps(body))
    print response.text


if __name__ == '__main__':
    
    before_count = count_instance("NumberTenScreeningRoom")
    response_content, total = get_dsfys_content(1, 10)
    content = parse_dsfys_content(response_content)
    AutoDiscoveryJson(content)
    after_count = count_instance("NumberTenScreeningRoom")

    # 前后数量有变更则发邮件通知
    if after_count > before_count:
        instance_data = search_latest_one_of_dsfys()
        send_email(instance_data=instance_data)
