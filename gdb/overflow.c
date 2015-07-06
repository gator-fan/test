/*************************************************************************
 * @File Name: overflow.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月03日 星期五 19时52分02秒
 ************************************************************************/

#include <stdio.h>

void f()
{
  long *p = 0;
  p = (long*)(&p + 1); // get g()'s RBP
  *p = 0; // destruct g()'s RBP
}

void g()
{
  int *p = 0;
  long a = 0x1234;
  //printf("%p %x\n", &a, a);
  //printf("%p %x\n", &p, p);
  f();
  *p = 1; // write address x, core
}

void b(int argc, char** argv)
{
  printf("%p %p\n", &argc, &argv);
  g();
}

int main(int argc, char** argv)
{
  b(argc, argv);
  return 0;
}
