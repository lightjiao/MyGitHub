#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Lights Jiao'

'load app.py by auto'

import os, sys, time, subprocess

from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

def Log(s):
    print('[Monitor] %s' % s)


class MyFileSystemEventHandler(FileSystemEventHandler):
    def __init__(self, fn):
        super(MyFileSystemEventHandler, self).__init__()
        self.restart = fn

    def on_any_event(self, event):
        if event.src_path.endswith('.py'):
            Log('Python source file changed: %s' % event.src_path)
            self.restart()

command = ['echo', 'ok']
process = None

def _killProcess():
    global process, command
    if process:
        Log('Kill process [%s]...' % process.pid)
        process.kill()
        process.wait()
        Log('Process ended with code %s.' % process.returncode)
        process = None


def _startProces():
    global process, command
    Log('Start process %s ...' % ' '.join(command))
    process = subprocess.Popen(command, stdin=sys.stdin, stdout=sys.stdout,stderr=sys.stderr)


def RestartProcess():
    _killProcess()
    _startProces()


def StartWatch(path, callback):
    observer = Observer()
    observer.schedule(MyFileSystemEventHandler(RestartProcess), path, recursive=True)
    observer.start()
    Log('Watching directory %s...' % path)
    _startProces()
    try:
        while True:
            time.sleep(0.5)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()


if __name__ == '__main__':
    argv = sys.argv[1:]
    if not argv:
        argv.append('app.py')
    if not argv:
        print('Usage: ./pymonitor your-script.py')
        exit(0)
    if argv[0] != 'python':
        argv.insert(0, 'python')
    command = argv
    path    = os.path.abspath('.')
    StartWatch(path, None)



















