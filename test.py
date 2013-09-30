# -*- coding: utf-8 -*-
import acseg

acindex = acseg.AcIndex()
#
acindex.load_dict("./z.txt")
#acindex.add_word("2012")

acindex.fix()
print "\n=====================\n\n"
#words = acindex.full_seg("清仓特价 羽绒服时尚女式大众款羽绒服 高贵气质羽绒服 修身羽绒服 [100%]",6)
#for word in words:
#    print word
#words = acindex.full_seg("羽绒服时尚女式大众",6)
words = acindex.full_seg("20时尚12cd",0)
for word in words:
    print word
print "\n\n\n-========================\n"
words = acindex.full_seg("20时12尚cd",0,2)
for word in words:
    print word
print "\n\n\n-========================\n"
words = acindex.full_seg("20时尚12cd",6,3)
for word in words:
    print word
#words = acindex.full_seg("秋季时尚睡衣",10)
#for word in words:
#    print word

