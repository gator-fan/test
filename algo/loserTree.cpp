#include <iostream>
#include <limits>
#include <algorithm>
#include <string.h>


using namespace std;

const int MaxInt = numeric_limits<int>::max();
const int MinInt = numeric_limits<int>::min();
const int K = 4; // K-merge

int a[][8] = {
	{0,3,5,8,MaxInt},
	{2,6,9,MaxInt},
	{1,3,8,MaxInt},
	{5,9,12,17,MaxInt},
};

int loserTree[K]; // store internal nodes, reuse it for higher level
int b[K+1];

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void adjust(int leaf)
{
	int parent = (leaf + K) >> 1; // leaf + k is leaf, /2 is parent
	int winner = leaf;
	while(parent > 0)
	{
		if(b[winner] > b[loserTree[parent]])	
		{
			swap(winner, loserTree[parent]);
		}
		parent >> 1; // level up
	}

	loserTree[0] = winner; // highest node only for winner
}

void createLoserTree()
{
	int i;
	for(i = 0; i < K; i++)
	{
		loserTree[i] = K;
	}

	for( i = K-1; i >= 0; i--)
	{
		adjust(i);
	}
}

void kMerge()
{
	int pa[K];
	memset(pa, 0, sizeof(pa));

	for(int i = 0; i < K; i++)
	{
		b[i] = a[i][pa[i]];
		++pa[i];
	}
	b[K] = MinInt;

	createLoserTree();

	while(b[loserTree[0]] != MaxInt)
	{
		cout << b[loserTree[0]]	 << " ";
		int i = loserTree[0];
		b[i] = a[i][pa[i]++];
		adjust(i);
	}
	cout << endl;
}

int main()
{
	kMerge();
}
