# -*- coding: utf-8 -*-
from PyQt5 import QtCore, QtGui, QtWidgets
import xml.dom.minidom

from main_UI import Ui_Form
from RWFile  import RWFile

import sys

#这两行代码哪里来的？
#reload(sys)
#sys.setdefaultencoding('utf-8')

class mywindow(QtWidgets.QWidget, Ui_Form):
    def __init__(self):
        super(mywindow, self).__init__()
        self.setupUi(self)
        self._setComboBoxText()
        self.m_sFilename = None
        self.toolButton.clicked.connect(self.Getfilename)
        self.pushButton.clicked.connect(self.AnalyseTXT)
        self.pushButton_2.clicked.connect(self.SaveFile)
        self.ErrorMessageDialog = QtWidgets.QMessageBox(self)

    #解析XML配置信息
    def _setComboBoxText(self):
        try:
            self.m_XMLDom = xml.dom.minidom.parse("config.xml")
            self.m_XMLRoot = self.m_XMLDom.documentElement
            _files = self.m_XMLRoot.getElementsByTagName('file')
            for n in _files:
                nFilecode = int(n.getAttribute('filecode'))
                sFiletype = n.getAttribute('filename')
                self.comboBox.addItem(sFiletype, nFilecode)#此处的filecode 无效
        except Exception as e:
            self.ErrorMessageDialog.warning(self, '错误', str(e))


    #获取金手指文件名
    def Getfilename(self):
        try:
            self.openFileDialog = QtWidgets.QFileDialog(self)
            self.openFileDialog.setObjectName("获取TXT文件")
            self.m_sFilename = self.openFileDialog.getOpenFileName()[0]
            self.lineEdit.setText(self.m_sFilename)

        except Exception as e:
            self.ErrorMessageDialog.warning(self, '错误', str(e))

    #初始化表格
    def InitTableView(self):
        try:
            self.model = QtGui.QStandardItemModel(self.tableView)
            _files = self.m_XMLRoot.getElementsByTagName('file')

            self.model.clear()

            for n in _files:
                nFilecode = int(n.getAttribute('filecode'))
                if nFilecode == int(self.comboBox.currentIndex()):

                    #获取是否存在第一行信息
                    self.m_nFirstline = int(n.getAttribute('firstlinecount'))

                    #获取列数 获取格式信息
                    self.m_nColumnCount = 0
                    self.m_lFormatList  = []
                    for m in n.childNodes:
                        if isinstance(m, xml.dom.minidom.Element):
                            self.m_nColumnCount += 1#获取总列数
                            self.m_lFormatList.append(int(m.getAttribute('column-lenght')))#获取格式信息

                    self.model.setColumnCount(self.m_nColumnCount)
                    #sele.model.appendColumn()

                    #设置界面的表头
                    nColumnNo = 0
                    for m in n.childNodes:
                        if isinstance(m, xml.dom.minidom.Element):
                            sColumnName = m.getAttribute('column-name')
                            self.model.setHeaderData(nColumnNo, QtCore.Qt.Horizontal, sColumnName)
                            nColumnNo += 1

            self.tableView.setModel(self.model)
            #设置相邻两行变色
            self.tableView.setAlternatingRowColors(True)
            #设置列宽 --似乎没有起作用
            for n in self.m_lFormatList:
                if n >= 20:
                    self.tableView.setColumnWidth(n, 200)

        except Exception as e:
            self.ErrorMessageDialog.warning(self, '错误', str(e))

    #解析TXT文件
    def AnalyseTXT(self):
        try:
            if self.m_sFilename == None:
                raise AttributeError('请选择文件')

            self.InitTableView()

            self.m_RWFile = RWFile(self.m_sFilename, self.m_lFormatList)
            self.m_RWFile.open()

            if self.m_nFirstline == 1:
                self.m_nRowCount = self.m_RWFile.readCountInFirstLine()

            #self.model.appendRow()
            #设置数据
            nRow = 0
            Content = self.m_RWFile.readContentByFormat(startlinenum=-1, limit=-1)

            ######需要将 设置结果集 做一个封装 已到达良好的翻页、动态加载的实现
            for list in Content:
                for nCol, value in enumerate(list):
                    self.model.setItem(nRow, nCol, QtGui.QStandardItem(value))

                nRow += 1

            self.m_RWFile.close()

        except Exception as e:
            print(e)
            self.ErrorMessageDialog.warning(self, '错误', str(e))

    #保存TXT文件
    def SaveFile(self):
        try:
            self.m_RWFile.open()
            self.m_RWFile.TrcTheFile()
            if self.m_nFirstline == 1:
                self.m_RWFile.writeCountInFirstLine(self.m_nRowCount)

            for nRow in range(self.m_nRowCount):
                lContentList = []
                for nCol in range(self.m_nColumnCount):
                    lContentList.append(self.model.item(nRow, nCol).text())
                self.m_RWFile.writelineByFormat(lContentList)

            self.m_RWFile.close()

        except Exception as e:
            self.ErrorMessageDialog.warning(self, '错误', str(e))


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    myshow = mywindow()
    myshow.show()
    app.exec_()
