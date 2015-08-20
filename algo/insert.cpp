/*************************************************************************
 * @File Name: insert.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月16日 星期日 22时37分28秒
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

void insert(int a[], int n)
{
  int i, j, key;
  for(j = 1; j < n; j++)
  {
    key = a[j];
    i = j - 1;
    while(i >= 0 && a[i] > key)
    {
      a[i+1]  = a[i];
      i--;
    }
    a[i+1] = key;
  }
}

int main()
{
  //int a[] = {1,3,2,5,4};
  int a[] = {5,4,3,2,1};
  insert(a, 5);
  print(a, 5);
}
