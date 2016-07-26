#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import xlrd


#打开Excel文件
def OpenExcel(filename = './Data/直销系统文件接口格式解析1.1版本.xls'):
    try:
        ExcelFile = xlrd.open_workbook(filename)
        return ExcelFile
    except Exception as e:
        raise Exception(e)

#根据索引获取Excel表格中的数据 参数：filename:Excel文件路径，   index:表格所在标签页，  colnameindex：数据格式所在行
def GetTableByIndex(filename = './Data/直销系统文件接口格式解析1.1版本.xls', index = 0, colnameindex = 0):
    table = OpenExcel(filename).sheet_by_index(index)
    nTableRowNum = table.nrows  # 行数
    nTableColNum = table.ncols  # 列数
    if nTableColNum == 0 or nTableRowNum == 0:
        raise EOFError('所选Table页数据为空')
    try:
        dataFormatInfo = table.row_values(colnameindex)#获取数据格式
    except Exception:
        raise AttributeError('数据格式所在行超过了Table数据范围')

    return table, nTableRowNum, nTableColNum, dataFormatInfo



def CreateTxt(filename = './Data/金手指数据.txt'):
    try:
        TxtFile = open(filename, 'w')
        return TxtFile
    except Exception as e:
        raise Exception(e)


#需要的参数  数据起始行，数据起始列，数据格式信息所在行，txt文件路径
def main(txtfilepath = './Data/金手指数据.txt', txtstartrow = 0, txtstartcol = 0):
    xlTable, nTableRowNum, nTableColNum, dicDataFormatInfo = GetTableByIndex(index = 2, colnameindex=4)
    #print(dicDataFormatInfo)

    fpTXT = CreateTxt(txtfilepath)
    for i in range(txtstartrow, nTableRowNum):
        dicRowValue = xlTable.row_values(i)
        if dicRowValue:
            lRowValueList = []
            bHaveValue = False
            for j in range(txtstartcol, nTableColNum):
                if str(dicRowValue[j]) != '':
                    bHaveValue = True
                lRowValueList.append(str(dicRowValue[j]))
            if bHaveValue:
                fpTXT.writelines(lRowValueList)
                fpTXT.write('\n')

    print('金手指文件生成成功！')


if __name__ == '__main__':
    main(txtstartrow = 6, txtstartcol = 1)