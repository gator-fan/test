/*************************************************************************
 * @File Name: func_call.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月01日 星期三 17时35分37秒
 ************************************************************************/

#include <stdio.h>

int bar(int c, int d)
{
  int e = c + d;
  return e;
}
int foo(int a, int b)
{
  return bar(a, b);
}
int main(void)
{
  foo(2, 5);
  return 0;
}
