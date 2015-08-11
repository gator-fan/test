/*************************************************************************
 * @File Name: future.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月06日 星期四 10时00分27秒
 ************************************************************************/

#include <iostream>
#include <future>
#include <vector>

using namespace std;

void called_from_async()
{
  std::cout << "Async call" << std::endl;
}

int twice(int m)
{
  return 2*m;
}

int main()
{
  //std::future<void> result(std::async(called_from_async));
  
  //std::future<int> result(std::async([](int m, int n){ return m+n;}, 2, 4));

  std::vector<std::future<int>> futures;

  std::cout << "Message from main." << std::endl;

  for(int i = 0; i < 10; ++i)
  {
    futures.push_back(std::async(twice, i));
  }

  //result.get();

  //std::cout << result.get() << std::endl;

  for(auto &e : futures)
  {
    std::cout << e.get() << std::endl;
  }

  return 0;
}

