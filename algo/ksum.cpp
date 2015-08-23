#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

vector<vector<int> > ans;

void kSum(vector<int>& a, int target, int k, int index, vector<int>& helper)
{
	int sz = a.size();
	if(k > sz-indx) return;
	if(k == 1){
		int pos = binarySearch(a, index, sz-1, target);
		if(pos != -1)
	}
}

vector<vector<int> > threeSum2(vector<int>& num)
{
	vector<int> helper;
	ksum(num, 0, 3, 0, helper);
}


vector<vector<int> > threeSum(vector<int>& num)
{
	sort(num.begin(), num.end());

	vector<vector<int> > ans;

	for(int i = 0; i < num.size(); ++i)
	{
		if(i != 0 && num[i] == num[i-1]) continue;
		int left = i+1;
		int right = num.size()-1;

		vector<int> triple(3);
		while(left < right)
		{
			int sum = num[left]+num[right]+num[i];
			if(sum > 0) right--;
			else if (sum < 0) left++;
			else {
				triple[0] = num[i];
				triple[1] = left;
				triple[2] = right;
				ans.push_back(triple);
				left++;

				/*
				int oldLeftNum = num[left];
				while(left < num.size() && num[left] == oldLeftNum)
					left++;
					*/
			}
		}
	}
	return ans;
}

int main()
{
	vector<int> a = {1,-1,2,-2, 3, 9, -7};
	vector<vector<int> > res = threeSum(a);
	vector<vector<int> >::iterator it;
	it = res.begin();
	for(;it != res.end(); ++it){
		copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	return 0;
}
