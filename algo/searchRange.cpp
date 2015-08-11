/*************************************************************************
 * @File Name: searchRange.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月01日 星期六 18时26分58秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int lSearch(int A[], int n, int target);
int rSearch(int A[], int n, int target);

vector<int> searchRange(int A[], int n, int target)
{
  vector<int> res;
  if(n <= 0 ) return res;
  int leftIndex = lSearch(A, n, target);
  int rightIndex = rSearch(A, n, target);
  res.push_back(leftIndex);
  res.push_back(rightIndex);
}

int lSearch(int A[], int n, int target)
{
  int low = 0, high = n-1;
  while(low <= high)
  {
    int mid = (low+high)/2;
    if(A[mid] < target) low = mid+1;
    else high = mid - 1;
  }
  if(A[low] != target) return -1;
  return low;
}

int rSearch(int A[], int n, int target)
{
  int low = 0, high = n-1;
  while(low <= high)
  {
    int mid = (low+high)/2;
    if(A[mid] > target) high = mid-1;
    else low = mid+1;
  }
  if(A[high] != target) return -1;
  return high;
}

int main()
{
  int A[] = {1,2,3,4,4,5};
  vector<int> res = searchRange(A, 6, 4);
  copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  return 0;
}
