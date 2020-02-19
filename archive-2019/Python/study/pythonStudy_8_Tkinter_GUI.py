#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tkinter import *
import tkinter.messagebox as messagebox
import tkinter.filedialog as filedialog
import tkinter.ttk as ttk
import tkinter.tix as tix


class Application(Tk):
    def __init__(self, master = None):
        try:
            Tk.__init__(self, master)
            self.createWidgets()
            w, h = 300, 400
            ws = self.winfo_screenwidth()
            hs = self.winfo_screenheight()
            x = (ws / 2) - (w / 2)
            y = (hs / 2) - (h / 2)
            #self.geometry("%dx%d+%d+%d" % (w, h, x, y))
            self.geometry('+%d+%d' % (x, y))

        except Exception as e:
            messagebox.showerror(title='错误！', message=e)
            raise e

    def createWidgets(self):
        try:
            self.label_1 = Label(self, text= '用户名:').grid(row= 0, column= 0)
            self.label_2 = Label(self, text= '密  码:').grid(row= 1, column= 0)

            self.entry_1 = Entry(self).grid(row= 0, column= 1)
            self.entry_2 = Entry(self).grid(row= 1, column= 1)

            self.checkbutton_1_var = StringVar()
            self.checkbutton_1 = Checkbutton(self, text= '隐身登录', variable = self.checkbutton_1_var)
            self.checkbutton_1.grid(columnspan = 2, sticky = W)

            #self.headPhoto = PhotoImage(file= './Data/pic.gif')
            #self.imgLabel  = Label(self, image= self.headPhoto)
            #self.imgLabel.grid(row= 0, column= 2, columnspan= 2, rowspan= 2, sticky= W+E+N+S, padx= 5, pady= 5)

            self.button_1 = Button(self, text= '  登录  ').grid(row= 2, column= 2)
            self.button_2 = Button(self, text= '  取消  ', command= self.quit).grid(row= 2, column= 3)

            #self.apply(self.button_2, command)

        except Exception as e:
            raise e
        

    def createWidgets_1(self):
        try:
            self.LabelFrame1 = Label(self, text='Excel文件路径:')
            self.LabelFrame1.pack()

            variable = StringVar(self)
            variable.set('one')
            self.OptionMenu = OptionMenu(self, variable = variable, value=("one", "two", "three"))
            self.OptionMenu.pack()

            self.nameInput = Entry(self)
            self.nameInput.pack()
            self.alertButton = Button(self,  text = 'Hello', command = self.hello)
            self.alertButton.pack()
            self.openfileButton = Button(self, text = '选择文件', command = self.openfile)
            self.openfileButton.pack()
            self.ListBox = ttk.Combobox(self, text = 'TTK.COMBOBOX', values = ['1', '2'])
            self.ListBox.pack()
            self.QuitButton = Button(self, text = '关闭', command = self.quit)
            self.QuitButton.pack()

        except Exception as e:
            raise e


    def hello(self):
        try:
            #name = self.nameInput.get() or 'World'
            messagebox.showinfo(title='Message', message='Hello, World')

        except Exception as e:
            raise e

    def openfile(self):
        try:
            filename = filedialog.askopenfilename()
            self.nameInput.set(filename)

        except Exception as e:
            raise e




if __name__ == '__main__':
    app = Application()
    app.title('Excel数据导出工具Edit by JHB with Python Tk GUI')
    app.mainloop()