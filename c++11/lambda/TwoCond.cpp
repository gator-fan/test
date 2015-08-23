#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

extern vector<int> nums;

void TwoCond(int low, int high){
	for(auto i = nums.begin(); i != nums.end(); i++)
		if(*i >= low && *i < high) break;

	find_if(nums.begin(), nums.end(), 
				compose2(logical_and<bool>(), 
						bind2nd(less<int>(), high),
						bind2nd(greater<int>(), low)));
	
	find_if(nums.begin(), nums.end(), [=](int i)->bool{
				return i>= low && i < high;	
			});
}
