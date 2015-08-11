#########################################################################
# File Name: build.sh
# Author: wangfan
# mail: wangfan@mvad.com
# Created Time: 2015年07月22日 星期三 13时16分07秒
#########################################################################
#!/bin/bash

gcc  example.c -L../ -lhiredis -I../
