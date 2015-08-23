#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void nextPerm(vector<int>& num, int N)
{
	int pivot = -1;
	for(int i = N - 1; i > 0; i--)
	{
		if(num[i] > num[i-1])	
		{
			//pivot = i - 1;	
			pivot = i ;	
			//break;
		}
	}
	//cout << "pivot is " << pivot << endl;
	if(pivot >= 0 )
	{
		int i;
		for(i = N - 1; i > pivot; i--)
		{
			if(num[i] > num[pivot])
			{
				cout << "i is " << i << endl;
				swap(num[i], num[pivot]);
	copy(num.begin(), num.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
				sort(num.begin()+pivot+1, num.end());
	copy(num.begin(), num.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
				return;
			}
		}
	}
	else
	{
		sort(num.begin(), num.end());
	}
}

int main()
{
	vector<int> a = {1, 2, 5, 4, 3};
	//swap(a[1], a[4]);

	nextPerm(a, 5);
	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

}
