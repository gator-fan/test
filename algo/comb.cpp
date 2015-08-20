/*************************************************************************
 * @File Name: comb.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月17日 星期一 22时06分20秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

void comb(int a[], int pos, int N, vector<int>& cand, std::vector<std::vector<int> >& res)
{
  int i;
  if(pos > N) return;
  res.push_back(cand);
  for(i = 0; i < N; i++)
  {
    cand.push_back(a[i]);
    comb(a, pos+1, N, cand, res);
    cand.pop_back();
  }
}

void print(std::vector<std::vector<int> >& res)
{
  std::vector<std::vector<int> >::iterator it;
  for(it = res.begin(); it != res.end(); it++)
  {
    copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
}

void comb2(int a[], int N, int cur, vector<int>& res)
{
  if(cur == N)
  {
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  else
  {
    res.push_back(a[cur]); 
    comb2(a, N, cur+1, res);
    res.pop_back();
    comb2(a, N, cur+1, res);
  }
}

int main()
{
  int a[] = {1,2,3};
  std::vector<int> cand;
  //std::vector<std::vector<int> > res;
  //comb(a, 0, 3, cand, res);
  comb2(a, 3, 0, cand);
  /*
  cand.push_back(0);
  cand.push_back(1);
  std::vector<int> cand2;
  cand2.push_back(1);
  cand2.push_back(2);
  res.push_back(cand);
  res.push_back(cand2);
  */
  //print(res);
  return 0;
}
