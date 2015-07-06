/*************************************************************************
 * @File Name: map.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月02日 星期二 14时58分19秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <boost/timer.hpp>
#include <algorithm>

using namespace std;
using namespace boost;

static const int NUM = 1000000;

int main()
{
  timer t1;
  vector<int> v;
  v.reserve(NUM);
  for(int i = 0; i < NUM; i++)
    v.push_back(i);
  sort(v.begin(), v.end());
  cout << "t1 is " << t1.elapsed() << endl;
  
  timer t2;
  unordered_map<int, int> um;
  for(int i = 0; i < NUM; i++)
    um.insert(pair<int,int>(i,i));
  cout << "t2 is " << t2.elapsed() << endl;

  timer t3;
  map<int, int> m;
  for(int i = 0; i < NUM; i++)
    m.insert(pair<int,int>(i,i));
  cout << "t3 is " << t3.elapsed() << endl;

  return 0;
}
