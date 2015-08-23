#include <iostream>

using namespace std;

int main(){
	int ten = 10;
	int *a = &ten;
	int *& b = a;
	cout << hex << a << endl;
	cout << hex << b << endl;
}
