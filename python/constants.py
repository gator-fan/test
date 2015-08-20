# coding=UTF-8
#!/usr/bin/python

formatter = "Unknow action %r for %r"

DSPID = "4"
TOKEN = "MzBhODdkYzIxMTA2ZTQwMzcy"

# @Name: Query creative 
# @Param: dspId, token, ideaIds
QUERY_CREATIVE = "http://amp.ad.sina.com.cn/sax/interface/idea/getstatus.action"

# @Name: Upload creative 
# @Param: dspId, token, id, name, width, height, type(0, non-flash), html, advertiserId
UPLOAD_CREATIVE = "http://amp.ad.sina.com.cn/sax/interface/idea/upload.action"

# @Name: Query resource postion, width, height
# @Param: dspId, token
QUERY_RESOURCE = "http://amp.ad.sina.com.cn/sax/interface/idea/adposWdht!queryAdposWdht.action"

# @Name: Query resource position only
# @Param: dspId, token
QUERY_ADPOS = "http://amp.ad.sina.com.cn/sax/interface/idea/adposWdht!queryAdpos.action"

