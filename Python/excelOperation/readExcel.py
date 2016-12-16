# -*- coding: utf-8 -*-

import xlrd

def main():
    sExcelFilename = input('Excel路径:')
    table = xlrd.open_workbook(sExcelFilename).sheet_by_index(0)
    nTableRowNum = table.nrows

    nMaxBankacctnoLength = 0
    for nTemRow in range(nTableRowNum):
        lRowValue = table.row_values(nTemRow)
        for i, value in enumerate(lRowValue):
            if i == 2:
                if len(value) > nMaxBankacctnoLength:
                    nMaxBankacctnoLength = len(value)

    with open('D:/ExcelTxt.sql', 'w') as fpExcelTXT:
        for nRow in range(2, nTableRowNum):
            sql = 'update fcs_bankaccount t set t.accountflag = \'1\' where t.bankacctno = %BANKACCTNO% and t.accttype = %ACCTTYPE%;\n'
            lRowValue = table.row_values(nRow)
            for i, value in enumerate(lRowValue):
                if i == 2:
                    sBankacctStr = '\'' + value + '\''
                    sBankacctStr += ' ' * (nMaxBankacctnoLength - len(value.encode('gbk')))
                    sql = sql.replace('%BANKACCTNO%', sBankacctStr)
                elif i == 4:
                    sql = sql.replace('%ACCTTYPE%', value)
            fpExcelTXT.write(sql.encode('gbk'))

if __name__ == '__main__':
    main()