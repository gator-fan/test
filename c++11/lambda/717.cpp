#include <iostream>

using namespace std;

int main(){
	int girls = 3, boys = 4;
	auto totalChild = [](int x, int y) mutable->int{return x+y;};
	cout << totalChild(girls, boys) << endl;

	totalChild = [=]()->int{return girls+boys;};
	cout << totalChild(girls, boys) << endl;

	return 0;
}	
