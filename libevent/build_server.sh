#########################################################################
# File Name: build_server.sh
# Author: wangfan
# mail: wangfan@mvad.com
# Created Time: 2015年07月22日 星期三 13时35分38秒
#########################################################################
#!/bin/bash

gcc -I/usr/include-o test server.c -L/usr/local/lib -levent
