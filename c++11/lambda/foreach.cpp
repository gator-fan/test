#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nums;
vector<int> largeNums;

const int ubound = 10;

inline void LargeNumsFunc(int i){
	if( i > ubound)
		largeNums.push_back(i);
}

void Above(){
	for(auto iter = nums.begin(); iter != nums.end(); ++iter){
		if(*iter >= ubound)
			largeNums.push_back(*iter);
	}
	
	for_each(nums.begin(), nums.end(), LargeNumsFunc);

	for_each(nums.begin(), nums.end(), [=](int i) {
				if(i > ubound)
					largeNums.push_back(i);
			});
}
