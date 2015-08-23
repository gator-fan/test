#include <iostream>
#include <stack>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;



int height[] = {2,1, 5, 6, 2, 3};

int maxArea(int height[], int n)
{
	int max = 0;
	stack<int> bars;
	bars.push(-1);
	for(int i = 0; i < n; ++i){
		int prev = bars.top();
		if(prev < 0 || height[i] >= height[prev]){
			cout << "[push]i is " << i << endl;
			bars.push(i);
		} else {
			prev = bars.top();
			bars.pop();
			max = MAX(max, height[prev]*(i-bars.top() - 1));
			cout << "max is " << max << ", prev is " << prev << ", i is " << i << endl;
			i--;
			cout << "i is " << i << endl;
		}
	}
	/*
	while(bars.top() != -1){
		int prev = bars.top();
		bars.pop();
		max = MAX(max, height[prev]*(n - bars.top() - 1));
	}
	*/
	return max;
}

int main()
{
	int max = maxArea(height, 6);
	cout << "max is " << max << endl;
	return 0;
}
