/*************************************************************************
 * @File Name: /home/fanwang/test/price.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月30日 星期四 15时58分01秒
 ************************************************************************/

#include <iostream>
using namespace std;

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */

int main ()
{
  //std::string pricestr("20.250499725342");
  std::string pricestr("20");
  char * pEnd;
  //long int price;
  //int64_t price;
  double price;
  //price = strtol (pricestr.c_str(),&pEnd,10);
  price = strtod(pricestr.c_str(),&pEnd);
  if (pricestr.size() > 0 && pEnd != NULL && *pEnd == '\0') 
  {
    std::cout << "price is " << price << std::endl;
    std::cout << "pEnd is " << pEnd << std::endl;
    std::cout << "*pEnd is " << *pEnd << std::endl;
  }
  else
  {
    std::cout << "decode fail" << std::endl;
  }
  return 0;
}
