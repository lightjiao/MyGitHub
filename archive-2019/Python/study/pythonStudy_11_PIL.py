#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from PIL import Image

im = Image.open('../Data/guojia_smile_face.jpg')
w, h = im.size

print(w, h)

