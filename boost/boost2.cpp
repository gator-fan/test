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
#include <vector>
#include <list>

using namespace std;
using namespace boost;

int main()
{
  vector<vector<int> > vli;
  for(int i = 0; i < 50; i++)
  {
    vector<int> li;
    for(int j = 0; j < 5; j++)
    {
      li.push_back(j);
    }
    vli.push_back(li);
  }

  vector<int> result;

  timer t2;

  bool has_data = true;
  for (int pos = 0; has_data; pos++)
  {                                                                                                                                                                                                          
    has_data = false;
    //for (int i = 0; i < wps.size(); i++) 
    for (int i = 0; i < vli.size(); i++) 
    {    
      //if (wps.at(i).words.size() > pos) 
      if (vli.at(i).size() > pos) 
      {    
        result.push_back(vli.at(i).at(pos));
        has_data = true;
      }    
    }    
  }

  cout << "now time elapsed: " << t2.elapsed() << "s" << endl;

  return EXIT_SUCCESS;
}
