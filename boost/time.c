/*************************************************************************
 * @File Name: time.cpp
 * @Author: wangfan
 * @Mail: wangfan@mediav.com 
 * @Created Time: 2015年04月17日 星期五 10时35分17秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

bool GetStrFromTime(time_t iTimeStamp, char *pszTime)
{
  tm *pTmp = localtime(&iTimeStamp);
  if (pTmp == NULL)
  {
    return false;
  }
  sprintf(pszTime, "%d-%d-%d %d:%d:%d", pTmp->tm_year + 1900, pTmp->tm_mon + 1, pTmp->tm_mday, pTmp->tm_hour, pTmp->tm_min, pTmp->tm_sec);
  printf("time is %s", pszTime);
  return true;
}


int main()
{
  time_t timep;
  struct tm *p;

  time(&timep); /*当前time_t类型UTC时间*/
  printf("time():%d\n",timep);
  p = localtime(&timep); /*转换为本地的tm结构的时间按*/
  timep = mktime(p); /*重新转换为time_t类型的UTC时间，这里有一个时区的转换*/ //by lizp 错误，没有时区转换， 将struct tm 结构的时间转换为从1970年至p的秒数
  printf("time()->localtime()->mktime(): %d\n", timep);

  char *s = new char[100];
  //GetStrFromTime(1432224000000000,s);
  GetStrFromTime(1432224000,s);
  printf("time is %s", s);

  delete s;

  return 0;
}
