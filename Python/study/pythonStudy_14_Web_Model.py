#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def home():
    return render_template('home.html', page_list = list(range(5)))


@app.route('/signin', methods=['GET'])
def signin_form():
    return render_template('form.html')


@app.route('/signin', methods=['POST'])
def signin():
    username = request.form['username']
    password = request.form['password']

    if username == 'JHB' and password == '1':
        return render_template('signin-ok.html', username = username)
    return render_template('form.html', message = 'Bad username or password', username = username)

if __name__ == '__main__':
    app.run()
