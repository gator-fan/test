/*************************************************************************
 * @File Name: perm.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月02日 星期日 15时37分16秒
 ************************************************************************/

#include <iostream>
using namespace std;

void swap(int* arr, int a, int b)
{
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

void PrintArray(int* arr, int n)
{
  for(int i = 0; i < n; ++i)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void perm(int* arr, int pos, int n)
{
  int i;
  if(pos == n){
    PrintArray(arr, n);
    return;
  }
  for(i = pos; i < n; ++i) 
  {
    swap(arr, i, pos);
    perm(arr, pos+1, n);
    swap(arr, i, pos);
  }
}

int main()
{
  int arr[] = {1,2,3};
  perm(arr, 0, 3);
  return 0;
}
