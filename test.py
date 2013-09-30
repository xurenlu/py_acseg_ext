# -*- coding: utf-8 -*-
import pdb
import acseg
print "4"
acindex = acseg.AcIndex()
print "got idx"
#
acindex.load_dict("./src/word.txt")
print "load_dict done"
#acindex.add_word("2012")
acindex.fix()
print "====================="
words = acindex.full_seg("清仓特价 羽绒服时尚女式大众款羽绒服 高贵气质羽绒服 修身羽绒服 [100%]",1)
for word in words:
    print word
#words = acindex.full_seg("羽绒服时尚女式大众",6)
#words = acindex.full_seg("abcd",7,9)


