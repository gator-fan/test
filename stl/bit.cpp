/*************************************************************************
 * @File Name: bit.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年05月28日 星期四 18时42分13秒
 ************************************************************************/

#include <stdio.h>
#include <iostream>

using namespace std;

bool isTypeFiltered(unsigned int label_id)
{
  //return ((num>>24) & 0xF3) && ((num>>24) & 0xE7);
  return ( !(((label_id >> 24 & 0xFF) ^ 0x0c) == 0) && !(((label_id >> 24 & 0xFF) ^ 0x18) == 0) );
}

int main()
{
  /*j
  unsigned int a = 0xFF00FF01;
  cout << (a >> 24) << endl; 
  */
  
  unsigned int b = 0x0c00FF01;

  unsigned int c = 0x1800FF01;

  cout << isTypeFiltered(b) << endl;
  cout << isTypeFiltered(c) << endl;

  unsigned int d = 0x1900FF01;
  cout << isTypeFiltered(d) << endl;

  int e = 0x00000001;
  cout << isTypeFiltered(d) << endl;

  return 0;
}
