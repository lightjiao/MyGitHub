# -*- coding: utf-8 -*-
import sys

class RWFile(object):
    #@filename: TXT文件名， @formatList:格式信息-每个字段长度的List
    def __init__(self, filename, formatList):
        try:
            self.m_sFilename       = filename
            self.m_lFormatInfoList = formatList
            self.m_nCurrentlinenum = 0 # 文件指针所在行
        except Exception as e:
            raise e

    #读文件总条数信息
    def readCountInFirstLine(self):
        try:
            self.m_nCount = self.m_fpFile.readline()
            return int(self.m_nCount)
        except Exception as e:
            raise e

    #读取一行数据, 返回数据List
    def readOneLineByFormat(self):
        try:
            sLineContent = self.m_fpFile.readline()
            sLineContent = sLineContent.encode('gbk')

            self.m_lOneLineContent = []

            if len(sLineContent) == 0:
                return []
            else:
                for n in self.m_lFormatInfoList:
                    sContent = sLineContent[0:n].strip().decode('gbk')
                    self.m_lOneLineContent.append(sContent)
                    sLineContent = sLineContent[n:]

            return self.m_lOneLineContent

        except Exception as e:
            raise e

    #读取多行数据, 返回数据结果集（二维数组）
    def readContentByFormat(self, startlinenum = 0, limit = 100):
        try:
            self.m_lFormatContent = []
            while True:
                self.readOneLineByFormat()
                self.m_nCurrentlinenum += 1
                if self.m_nCurrentlinenum <= startlinenum:
                    continue
                if (self.m_nCurrentlinenum > startlinenum + limit) or len(self.m_lOneLineContent) == 0:
                    break

                self.m_lFormatContent.append(self.m_lOneLineContent)

            return self.m_lFormatContent

        except Exception as e:
            raise e

    #清空文件
    def TrcTheFile(self):
        self.m_fpFile.truncate()

    def open(self):
        try:
            self.m_fpFile = open(self.m_sFilename, 'r+')
        except Exception as e:
            raise e

    def close(self):
        try:
            self.m_fpFile.close()
        except Exception as e:
            raise e

    #写入总行数信息
    def writeCountInFirstLine(self, nCount):
        try:
            sCount = str(nCount)
            sCount = (8 - len(sCount)) * '0' + sCount + '\n'
            self.m_fpFile.write(sCount)
        except Exception as e:
            raise e

    #根据格式信息按行写文件 @contentlist:文件内容List
    def writelineByFormat(self, contentlist):
        try:
            sAllContent = ''
            for i, value in enumerate(contentlist):
                sAllContent += value
                nSpaceCount = self.m_lFormatInfoList[i] - len(str(value).encode('gbk'))
                sAllContent += ' ' * nSpaceCount #追加空格
            sAllContent += '\n'
            self.m_fpFile.write(sAllContent)
        except Exception as e:
            raise e



if __name__ == '__main__':
    a = '焦鸿彬    123'
    a = a.encode('gbk')
    a = a[0:10].decode('gbk')
    print(a)