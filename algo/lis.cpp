#include <iostream>

using namespace std;

int LIS(int arr[], int len)
{
	for(int j = 0; j < len; j++){
		cout << arr[j] << " ";
	}
	cout << endl;
	int longest[len];
	for(int j = 0; j < len; j++){
		longest[j] = 1;
		for(int i = 0; i < j; i++){
			if(arr[j] >= arr[i]){
				longest[j] = (longest[j] > longest[i]+1) ? longest[j]:longest[i]+1;
			}
		}
	}

	int max = 0;
	for(int j = 0; j < len; j++){
		if(longest[j] > max) max = longest[j];
	}
	return max;
}

int main()
{
	int a[] = {5, 6, 7, 1, 2, 8};
	int res = LIS(a, 6);
	cout << "res is " << res << endl;
	return 0;
}
