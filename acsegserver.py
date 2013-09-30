# -*- coding: utf-8 -*-
#计算标题中含有哪些直通车关键词的server
#监听9123端口;
#访问方式是:http://host:9123/?试试这些含有什么关键词

import acseg as acfilter
import sys,os
import threading
import time
from subprocess import *
sys.path.append("/home/x/lib/")
from BaseHTTPServer import *
from urlparse import urlparse
import  urllib
import string

acindex = acfilter.AcIndex()
acindex.load_dict("./dict")
acindex.fix()


def sub_words(text,max_seek_times):
    global acindex
    if max_seek_times==-1:
        #这个要先用0,再用3,再用6来分别找词;
        words1 = acindex.full_seg(text,0)
        words3 = acindex.full_seg(text,3)
        words8 = acindex.full_seg(text,8)
        
        words = words1
        for w in words3:
            if not w in words:
                words.append(w)
        for w in words8:
            if not w in words:
                words.append(w)
        return words
    else:
        words = acindex.full_seg(text,max_seek_times)
        return words

