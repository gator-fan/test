/*************************************************************************
 * @File Name: test.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月25日 星期四 16时18分36秒
 ************************************************************************/

#include "stdio.h"
#include "stdlib.h"

void a(){
  printf("\t\t+---call a() function\n");
}

void c(){
  printf("\t\t+---call c() function\n");
}

int b(){
  printf("\t+--- call b() function\n");
  a();
  c();
  return 0;
}

int main(){
  printf(" main() function()\n");
  b();
}
