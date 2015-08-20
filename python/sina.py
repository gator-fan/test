#!/usr/bin/python
import urllib2
import sys,os

import utils
from utils import help,QueryAdPos,QueryCreative
import constants


if __name__ == '__main__':
    #print len(sys.argv)
    #print sys.argv[0]
    if len(sys.argv) < 2:
        utils.help()
        sys.exit()
    if sys.argv[1] == 'upload':
        if sys.argv[2] == 'creative':
            UploadCreative()
        elif sys.argv[2] == 'advertiser':
            UploadAdvertiser()
        else:
            print formatter % ('object', sys.argv[1])
            help()
            sys.exit()
    elif sys.argv[1] == 'query':
        if sys.argv[2] == 'creative':
            QueryCreative()
        elif sys.argv[2] == 'resource':
            QueryResource()
        elif sys.argv[2] == 'adpos':
            QueryAdPos()
        else:
            print formatter % ('object', sys.argv[1])
            utils.help()
            sys.exit()
    else:
        print formatter % ('type', sys.argv[1])
        utils.help()
        sys.exit()
