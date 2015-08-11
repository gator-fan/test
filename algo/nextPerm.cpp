/*************************************************************************
 * @File Name: nextPerm.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月01日 星期六 20时31分05秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <iterator>
#include <stack>

using namespace std;

int search(vector<int>& v, int left, int right, int target)
{
  while(left < right)
  {
    int middle = (left+right)/2;
    if(v[middle] <= target) right = middle - 1;
    else left = middle;
  }
  if(v[left] <= target) return -1;
  else return left;
}

template<typename T>
void swap(T & a, T & b)
{
  T tmp = a;
  a = b;
  b = a;
}

template<typename T>
void reverse(T left, T right)
{
  typedef typename iterator_traits<T>::value_type Type;
  if(left < right)
  {
    swap<T>(left, right);
  }
}

void nextPerm(vector<int>& num)
{
  typedef typename iterator_traits<num.begin()>::value_type Type;
  for(int i = num.size() - 2; i >= 0; --i)
  {
    int index = search(num, i+1, num.size(), num[i]);
    if(index != -1)
    {
      swap<Type>(num[index], num[i]);
      reverse(num.begin()+i+1, num.end());
      return;
    }
  }
  reverse(num.begin(), num.end());
}

