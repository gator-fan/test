/*************************************************************************
 * @File Name: cnm.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月02日 星期日 15时43分27秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void comb(int seq[], int n, int m, vector<int>& tvec)
{
  for(int i = n-1; i >= m-1; i--)
  {
    if(m > 0){
      tvec.push_back(seq[i]);
      comb(seq, i, m-1, tvec);
      tvec.pop_back();
    } else {
      copy(tvec.begin(), tvec.end(), ostream_iterator<int>(cout, " "));
      cout << endl;
      //break;
    }
  }
}

int main()
{
  int seq[] = {1,2,3,4};
  vector<int> tvec;
  comb(seq, 4, 2, tvec);
  return 0;
}
