/*************************************************************************
 * @File Name: replace.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年05月28日 星期四 17时16分27秒
 ************************************************************************/

#include <iostream>
#include <string>   
#include <iostream>   
#include <iterator>
#include <map>
#include <boost/timer.hpp>

using namespace std;   
using namespace boost;

/*
string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)   
{   
  while(true)   {   
    string::size_type   pos(0);   
    if(   (pos=str.find(old_value))!=string::npos   )   
      str.replace(pos,old_value.length(),new_value);   
    else   break;   
  }   
  return   str;   
}   

string  replace_all_distinct(const string&   str,const   string&   old_value,const   string&   new_value)   
{   
  string res(str);
  for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {   
    if(   (pos=res.find(old_value,pos))!=string::npos   )   
      res.replace(pos,old_value.length(),new_value);   
    else   break;   
  }   
  return   res;   
}   
*/

void replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)   
{   
  for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {   
    if(   (pos=str.find(old_value,pos))!=string::npos   )   
      str.replace(pos,old_value.length(),new_value);   
    else   break;   
  }   
}   

/*
string  replace_all_distinct(const string&   str,const   string&   old_value,const   string&   new_value)   
{   
  string res(str);
  for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {   
    if(   (pos=res.find(old_value,pos))!=string::npos   )   
      res.replace(pos,old_value.length(),new_value);   
    else   break;   
  }   
  return   res;   
}   
*/

string   replace_multi_distinct(const string& str, map<string, string>& dict)   
{   
  string res(str);
  /*
  for(string::size_type   pos(0);   pos!=string::npos;   pos+=dict_iter->second.length())   {   
    for(map<string,string>::iterator dict_iter = dict.begin();dict_iter != dict.end(); ++dict_iter){
      if(   (pos=res.find(dict_iter->first,pos))!=string::npos   )   
        res.replace(pos,dict_iter->first.length(),dict_iter->second);   
      else   break;   
    }
  }   
  */
  string::size_type pos(0);
  do{
    for(map<string,string>::iterator dict_iter = dict.begin(); dict_iter != dict.end(); ++dict_iter) 
    {
      if((pos = res.find(dict_iter->first, pos)) != string::npos ) 
      {
          res.replace(pos, dict_iter->first.length(), dict_iter->second);
          pos += dict_iter->second.length();
      }
      else
      {
        break; 
      }
    }
  } while(pos != string::npos);
  return   res;   
}   

int   main()   
{   
  string a("http://static.mediav.com/bjjs/dsp/icon/v_tw.png");
  string b("http://static.mediav.com/bjjs/dsp/icon/v_tw.png&url=http://material.mediav.com");
  string c("http://material.mediav.com/bjjs/dsp/icon/v_tw.png");
  string d("http://static.mediav.com/bjjs/dsp/icon/v_tw.png&url=http://material.mediav.com");

  /*
  map<string, string> dict;
  dict.insert(pair<string,string>("http://material", "https://material-ssl"));
  dict.insert(pair<string,string>("http://", "https://"));
  for(auto m : dict){
    cout << "=====" << endl;
    cout << m.first << endl;
    cout << m.second << endl;
  }
  */

  cout << "================" << endl;
  cout << a << endl;
  replace_all_distinct(a, "http://","https://");   
  cout << a << endl;

  cout << "================" << endl;
  cout << b << endl;
  replace_all_distinct(b, "http://material","https://material-ssl");   
  cout << b << endl;

  cout << "================" << endl;
  cout << c << endl;
  replace_all_distinct(c, "http://material","https://material-ssl");   
  cout << c << endl;

  cout << "================" << endl;
  cout << d << endl;
  replace_all_distinct(d, "http://material","https://material-ssl");   
  replace_all_distinct(d, "http://","https://");   
  cout << d << endl;

  /*
  cout << d << endl;
  timer t;
  cout   <<   replace_multi_distinct(d, dict)   <<   endl;   
  cout << t.elapsed() << " s" << endl;
  */

  /*
  timer t1;
  string res;
  //res = replace_all_distinct(d, "http://","https://") ;
  //cout << replace_all_distinct(res, "http://material","https://material-ssl") << endl;
  res = replace_all_distinct(d, "http://material","https://material-ssl");   
  cout << replace_all_distinct(res, "http://","https://") << endl;
  cout << t1.elapsed() << " s" << endl;
  */
}   
