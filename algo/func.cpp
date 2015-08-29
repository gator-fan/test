/*************************************************************************
 * @File Name: func.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月30日 星期四 17时17分00秒
 ************************************************************************/

#include <iostream>
using namespace std;

extern "C" { 
  extern int printf (char *, ...); 
}

class a { 
  public: 
    void sub (int i) 
    { 
      printf ("__FUNCTION__ = %s\n", __FUNCTION__); 
      printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__); 
    } 
};

int main (void) 
{ 
  a ax; 
  ax.sub (0); 
  return 0; 
}
