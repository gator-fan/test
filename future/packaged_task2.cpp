/*************************************************************************
 * @File Name: packaged_task2.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年08月06日 星期四 10时28分13秒
 ************************************************************************/

#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

using namespace std;

int f(int x, int y) { return std::pow(x, y);}

void task_lambda()
{
  std::packaged_task<int(int, int)> task([](int a, int b){
    return std::pow(a, b);
  });

  std::future<int> result = task.get_future();

  task(2,9);

  std::cout << "task_lambda:\t" << result.get() << std::endl;
}

void task_bind()
{
  std::packaged_task<int()> task(std::bind(f, 2, 11));
  std::future<int> result = task.get_future();

  task();

  std::cout << "task_bind:\t" << result.get() << std::endl;
}

void task_thread()
{
  std::packaged_task<int(int, int)> task(f);
  std::future<int> result = task.get_future();

  std::thread task_td(std::move(task), 2, 10);
  //std::thread task_td(task, 2, 10);
  //task will lead error: packaged_task(const packaged_task&) = delete
  task_td.join();

  std::cout << "task_thread:\t" << result.get() << std::endl;
}

int main()
{
  task_lambda();
  task_bind();
  task_thread();
  return 0;
}

