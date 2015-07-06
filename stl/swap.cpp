/*************************************************************************
 * @File Name: swap.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年05月29日 星期五 17时50分46秒
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> a;
  vector<int> b;

  for(int i = 1; i < 5; i++)
  {
    a.push_back(i); 
  }

  cout << a.size() << endl;
  cout << b.size() << endl;
  //a.swap(b);
  b.swap(a);
  cout << a.size() << endl;
  cout << b.size() << endl;

  return 0;
}
