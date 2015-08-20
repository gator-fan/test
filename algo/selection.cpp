/*************************************************************************
 * @File Name: selection.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月16日 星期日 22时24分16秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void swap(int & a, int & b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

void selection(int a[], int n)
{
  int i, j, min;
  for(i = 0; i < n-1; i++)
  {
    min = i;
    for( j = i+1; j < n; j++)
    {
      if(a[j] < a[min]) min = j;
    }
    if(min != i) swap(a[i], a[min]);
  }
}

void print(int a[], int n)
{
  int i;
  for(i = 0; i < n; i++)
  {
    //cout << a[n] << " ";
    printf("%d ", a[i]);

  }
  //cout << endl;
  printf("\n");
}

int main()
{
  int a[] = {1,3,2,5,4};
  selection(a, 5);
  print(a, 5);
}
