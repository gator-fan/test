/*************************************************************************
 * @File Name: test.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月23日 星期四 15时19分32秒
 ************************************************************************/

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <thread>
#include <future>

using namespace std;

class B;

class A
{
  public:
    A(){ cout << "A()" << std::this_thread::get_id() << endl; }
   ~A(){ cout << "~A()" << std::this_thread::get_id() << endl; }
   void run();
   void run2(){ 
     //boost::shared_ptr<B> spb = boost::make_shared<B>(spb_);
     cout << "use_count is " << spb_.use_count() << endl; 
   };
   boost::shared_ptr<B> spb_;

};

class B
{
  public:
    B(){ cout << "B()" << std::this_thread::get_id() << endl; }
    ~B(){ cout << "~B()" << std::this_thread::get_id() << endl; }
    void runB() { cout << "runB()" << std::this_thread::get_id() << endl; }
private:
    int data;
};

void A::run()
{
  //spb_ = boost::shared_ptr<B>(new B());
  spb_ = boost::shared_ptr<B>();
}

int main(int argc, char** argv)
{
  A a;
  a.run();
  //std::thread t1(&A::run2, &a);
  std::future<void> fut = std::async (&A::run2, &a);
  //sleep(2);
  //std::thread t2(&A::run2, &a);
  //std::future<void> fut = std::async (&A::run2, &a);
  fut.get();
  a.spb_->runB();
  sleep(10);
  //t1.join();
  //t2.join();
  return 0;
}
