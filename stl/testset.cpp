/*************************************************************************
 * @File Name: testset.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月09日 星期二 10时45分56秒
 ************************************************************************/

#include <iostream>
#include <set>

using namespace std;

int main()
{
  set<int> si;
  if(si.find(123) == si.end())
    cout << "not found" << endl;
  else
    cout << "found" << endl;
  return 0;
}

