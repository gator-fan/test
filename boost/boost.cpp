/*************************************************************************
 * @File Name: boost.cpp
 * @Author: wangfan
 * @Mail: wangfan@mediav.com 
 * @Created Time: 2015年05月25日 星期一 18时19分11秒
 ************************************************************************/

#include <iostream>
#include <boost/timer.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <time.h>

using namespace std;
using namespace boost;

static inline time_t GetTodayTimestamp()
{
  boost::gregorian::date d(boost::gregorian::day_clock::universal_day());
  struct tm d_tm = boost::gregorian::to_tm(d);
  return mktime(&d_tm);
}

static inline uint64_t GetTimeStamp()                                                                                                                                                                      
{
  struct timeval now;
  gettimeofday(&now, NULL);
  return (uint64_t)now.tv_sec * 1000000 + now.tv_usec;
}

static inline time_t GetTodayTimestamp2()
{
  struct tm *local;
  time_t t;
  time(&t);
  //local=localtime(&t);
  local=gmtime(&t);
  local->tm_hour = 0;
  local->tm_min = 0;
  local->tm_sec = 0;
  return mktime(local);
}

static inline time_t GetTodayTimestamp3()
{
  struct tm *local;
  time_t t;
  time(&t);
  local=localtime(&t);
  //local=gmtime(&t);
  local->tm_hour = 0;
  local->tm_min = 0;
  local->tm_sec = 0;
  return mktime(local);
}


int main()
{
  //timer t;
  //cout << "max timespan: " << t.elapsed_max() / 3600 << "h" << endl;
  //cout << "min timespan: " << t.elapsed_min() << "s" << endl;
  //GetTodayTimestamp();
  //cout << "now time elapsed: " << t.elapsed() << "s" << endl;

  //timer t1;
  //GetTimeStamp();
  //cout << "now time elapsed: " << t1.elapsed() << "s" << endl;

  timer t2;
  GetTodayTimestamp2();
  cout << "now time elapsed: " << t2.elapsed() << "s" << endl;

  timer t3;
  GetTodayTimestamp3();
  cout << "now time elapsed: " << t3.elapsed() << "s" << endl;

  //cout << "timestamp 1: " << GetTodayTimestamp() << " s" << endl;
  //cout << "timestamp 2: " << GetTodayTimestamp2() << " s" << endl;
  //cout << "now time elapsed: " << t.elapsed() << "s" << endl;

  return EXIT_SUCCESS;
}
