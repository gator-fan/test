/*************************************************************************
 * @File Name: core.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月24日 星期三 16时06分49秒
 ************************************************************************/

#include <iostream>
using namespace std;
#include <stdio.h>

int main(void)

{

      printf("hello world! dump core for set value to NULL pointer/n");

          *(char *)0 = 0;

              return 0;

}
