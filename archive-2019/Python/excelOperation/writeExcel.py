#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import xlwt, json


def add_sheet(xls, sheet_name):
    return xls.add_sheet(sheetname=sheet_name)


def init_sheet(sheet):
    s = ['属性id', '属性名', '属性类型']
    for i, v in enumerate(s):
        sheet.write(0, i, v)


def set_style(name,height,bold=False):
    style = xlwt.XFStyle()  # 初始化样式

    font = xlwt.Font()  # 为样式创建字体
    font.name = name # 'MicrosoftYaHei'
    font.bold = bold
    font.color_index = 4
    font.height = height

    # borders= xlwt.Borders()
    # borders.left= 6
    # borders.right= 6
    # borders.top= 6
    # borders.bottom= 6

    style.font = font
    # style.borders = borders

    return style


if __name__ == '__main__':
    xls = xlwt.Workbook() #创建工作簿

    json_str = open('./temp.json').read()
    json_arr = json.loads(json_str)

    for obj, obj_arr in json_arr.items():

        sheet = xls.add_sheet(sheetname=obj)
        init_sheet(sheet)

        arrtList = obj_arr['attrList']
        line = 1
        for attr in arrtList:

            sheet.col(0).width = 4000
            sheet.col(1).width = 5000
            # sheet.col().width = 4000

            proper = attr['value']['type']
            if 'default' in attr['value'].keys():
                proper = attr['value']['default']
            if 'regex' in attr['value'].keys():
                proper += '(' + json.dumps(attr['value']['regex'], ensure_ascii=False,indent=2) + ')'
            if proper.startswith('FK'):
                proper += '(' + attr['value']['rule']['obj'] + ')'

            sheet.write(line, 0, attr['id'], set_style('MicrosoftYaHei',220))
            sheet.write(line, 1, attr['name'], set_style('MicrosoftYaHei',220))
            sheet.write(line, 2, proper, set_style('MicrosoftYaHei',220))
            line += 1


    xls.save('demo1.xls') #保存文件
