#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import xml.sax
import xml.dom.minidom

class SAXxmlHandler(xml.sax.ContentHandler):
    def startElement(self, name, attrs):
        print("1_ name:%s, attrs:%s" % (name, attrs))
        if name == 'file':
            print(attrs['filename'])
        if name == 'column':
            print(attrs['column-name'])
            print(attrs['column-lenght'])
            print(attrs['column-type'])

    def endElement(self, name):
        print("2_ name:%s " % name)

    def characters(self, text):
        print("3_ text:%s " % text)

def SAX_main():
    parser = xml.sax.make_parser()
    parser.setFeature(xml.sax.handler.feature_namespaces, 0)

    Handler = SAXxmlHandler()
    parser.setContentHandler(Handler)

    parser.parse("../Data/config.xml")

def DOM_main():
    dom = xml.dom.minidom.parse('../Data/config.xml')
    root = dom.documentElement
    bb = root.getElementsByTagName('file')
    for n in bb:
        print(n.getAttribute('filecode'), n.getAttribute('filename'))
    #print(bb)
    #print(bb[0].getAttribute('filename'))#获取标签属性值<file filename='核算明细'>
    #print(bb[0].firstChild.data)#获取标签对之间的数据<filename>核算明细</filename>


if __name__ == '__main__':
    #SAX_main()
    DOM_main()
    a = input('按任意键结束...')