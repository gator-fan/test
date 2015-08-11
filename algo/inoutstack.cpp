/*************************************************************************
 * @File Name: inoutstack.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月01日 星期六 09时48分59秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <iterator>

using namespace std;

void inoutstack(int in, int out, deque<int>&q, stack<int>&s, deque<int>& seq,
    vector<deque<int>>& result)
{
  if(!in && !out){
    result.push_back(q);
    return;
  }
  if(in > 0){
    s.push(seq.front());
    seq.pop_front();
    inoutstack(in-1, out, q,s,seq,result);
    seq.push_front(s.top());
    s.pop();
  }
  if(out > 0 && in < out){
    q.push_back(s.top());
    s.pop();
    inoutstack(in, out-1, q, s, seq, result);
    s.push(q.back());
    q.pop_back();
  }
}

void PrintResult(vector<deque<int>>& result)
{
  vector<deque<int>>::iterator iter;
  //for(auto iter = result.begin(); iter != result.end(); iter++)
  for(iter = result.begin(); iter != result.end(); iter++)
  {
    copy(iter->begin(), iter->end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
}

int main()
{
  deque<int> q;
  stack<int> s;
  deque<int> seq = {1,2,3};
  vector<deque<int>> result;
  inoutstack(3,3,q,s,seq,result);
  cout << result.size() << endl;
  cout << result[0].size() << endl;
  PrintResult(result);
  return 0;
}
