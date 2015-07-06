/*************************************************************************
 * @File Name: vector.cpp
 * @Author: wangfan
 * @Mail: wangfan@mediav.com 
 * @Created Time: 2015年05月21日 星期四 13时59分01秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int  main()
{
  vector<int> v;
  cout << v.size() << endl;
  cout << v.capacity() << endl;
  cout << endl;

  v.push_back(1);
  cout << v.size() << endl;
  cout << v.capacity() << endl;
  cout << endl;

  v.push_back(1);
  cout << v.size() << endl;
  cout << v.capacity() << endl;
  cout << endl;

  usleep(1000000);


  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  cout << v.size() << endl;
  cout << v.capacity() << endl;

  return 0;
}
