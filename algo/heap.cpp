#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	  int ia[9]={0,1,2,3,4,8,9,3,5};
	    vector<int> ivec(ia,ia+9);  //底层我们使用vector来实现，可以动态添加元素。 
		  
		  make_heap(ivec.begin(),ivec.end());
		    for(int i=0;i!=ivec.size();i++)cout<<ivec[i]<<" ";
			  cout<<endl;
			    
			    ivec.push_back(7);
				  push_heap(ivec.begin(),ivec.end());//这里可以用make_heap替换。 
				    for(int i=0;i!=ivec.size();i++)cout<<ivec[i]<<" ";
					  cout<<endl;
					    
					    pop_heap(ivec.begin(),ivec.end());
						  cout<<ivec.back()<<endl;
						    ivec.pop_back();
							  for(int i=0;i!=ivec.size();i++)cout<<ivec[i]<<" ";
							    cout<<endl;
								  
								  sort_heap(ivec.begin(),ivec.end());
								    for(int i=0;i!=ivec.size();i++)cout<<ivec[i]<<" ";
									  cout<<endl;

}
