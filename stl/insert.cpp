/*************************************************************************
 * @File Name: insert.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月05日 星期五 20时57分03秒
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);

  vector<int> vv;
  vv.insert(vv.end(), v.begin(), v.begin()+3);

  vector<int> vv2;
  vv2.insert(vv2.end(), v.begin()+3, v.end());

  for(auto iter:vv)
  {
    cout << "vv is " << iter << " " << endl;
  }

  for(auto iter:vv2)
  {
    cout << "vv2 is "<< iter << " " << endl;
  }

  return 0;
}

