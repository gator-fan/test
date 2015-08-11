/*************************************************************************
 * @File Name: packaged_task.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月06日 星期四 10时21分00秒
 ************************************************************************/

#include <iostream>
#include <future>
#include <thread>

using namespace std;

int main()
{
  std:;packaged_task<int()> task([](){return 7;});
  std::future<int> f1 = task.get_future();
  std::thread(std::move(task)).detach();

  std::future<int> f2 = std::async(std::launch::async, [](){ return 8;});

  std::promise<int> p;
  std::future<int> f3 = p.get_future();
  // unfortunately not supported by gcc 4.9 now
  //std::thread([](std::promise<int> p){ p.set_value_at_thread_exit(9);}, std::move(p)).detach();
  std::thread([](std::promise<int> p){ p.set_value(9);}, std::move(p)).detach();

  std::cout << "Waiting... " << std::flush;

  f1.wait();
  f2.wait();
  f3.wait();

  std::cout << "Done!\nResults are: "
            << f1.get() << " "
            << f2.get() << " "
            << f3.get() << std::endl;
  return 0;
}

