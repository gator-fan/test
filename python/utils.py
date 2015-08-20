# coding=UTF-8
#!/usr/bin/python
from constants import QUERY_ADPOS, DSPID, TOKEN, QUERY_CREATIVE
import urllib2
import json
from urllib2 import HTTPError, URLError
from pprint import pprint
import sys

def help():
    print 'Usage: sina.py [action type] [action object] [action params]'
    print '  |'
    print '  |-- action type'
    print '  |          |-- upload'
    print '  |          |-- query'
    print '  |-- action object'
    print '  |          |-- creative'
    print '  |          |-- advertiser'
    print '  |          |-- resource'
    print '  |          |-- adpos'
    print '  |-- action params'
    print 'e.g. sina.py query creative 111 222 333'
    

def UrlOpen(url):
    #s=urllib2.urlopen(url).read();
    try:
        response = urllib2.urlopen(url)
        #print 'Response:', response
        #print 'URL     :', response.geturl()
        #headers = response.info()
        #print 'DATE    :', headers['date']
        #print 'HEADERS :', headers
        data = response.read()
        #print 'LENGTH  :', len(data)
        #resp = json.loads(data.decode('utf-8'))
        #resp = json.loads(data)
        #pprint(resp)
        print 'DATA    :', data
    except HTTPError, e:
        print "The server couldn't fullfill the request"
        print "Error code:",e.code
    except URLError, e:
        print "Fail to reach a server!"
        print "Reason:",e.reason

def QueryAdPos():
    url = QUERY_ADPOS + "?dspId=" + DSPID + "&token=" + TOKEN
    print "url is %s" % (url)
    UrlOpen(url)

def QueryCreative():
    argc = len(sys.argv)
    ideaIds = ""
    for ideaId in sys.argv[3:argc]:
        ideaIds += "\""
        ideaIds += ideaId
        ideaIds += "\""
        ideaIds += ","
    ideaIds = ideaIds[:-1]
    url = QUERY_CREATIVE + "?dspId=" + DSPID + "&token=" + TOKEN + "&ideaIds=[" + ideaIds + "]"
    print "url is %s" % (url)
    UrlOpen(url)

def UploadCreative():
    AnalyseCreativeInfo()
    url = UPLOAD_CREATIVE + "?dspId=" + DSPID + "&token=" + TOKEN + "&ideaIds=[" + ideaIds + "]"
    print "url is %s" % (url)
    UrlOpen(url)

