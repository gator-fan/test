/*************************************************************************
 * @File Name: bubble.c
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月15日 星期六 22时44分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

using namespace std;

void swap(int & p1, int & p2)
{
  int tmp = p1;
  p1 = p2;
  p2 = tmp;
}

void bubble1(int a[], int n)
{
  int i,j;
  for(i = 0; i < n-1; i++)
  {
    for(j = 0; j < n-i-1; j++)
    {
      if(a[j] > a[i])
        swap(a[j], a[i]);
    }
  }
}

void bubble2(int a[], int n)
{
  int i,j;
  //for(i = 0; i < n-1; i++)
  for(i = 0; i < n-1; i++)
  {
    for(j = 0; j < n-i-1; j++)
    {
      if(a[j] > a[j+1])
        swap(a[j], a[j+1]);
    }
  }
}

void print(int data[], int n)
{
  int i;
  for(i = 0; i < n; i++)
  {
    printf("data[%d] is %d\n", i, data[i]);
  }
}

int main()
{
  int a = 1, b = 2;
  swap(a, b);
  printf("a is %d, b is %d\n", a, b);
  int data1[] = {5,4,3,2,1};
  int data2[] = {5,2,1,3,4};
  printf("\\\\\\\\\\\\\\\n");
  bubble1(data1, 5);
  print(data1, 5);
  printf("\\\\\\\\\\\\\\\n");
  bubble2(data1, 5);
  print(data1, 5);

  printf("\\\\\\\\\\\\\\\n");
  bubble1(data2, 5);
  print(data2, 5);
  printf("\\\\\\\\\\\\\\\n");
  bubble2(data2, 5);
  print(data2, 5);
  printf("\\\\\\\\\\\\\\\n");

  return 0;
}
