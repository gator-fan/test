#include <iostream>

using namespace std;

struct B{};
struct C:public B{};
struct D:public C{};

template<class I>
void func(I &p, B)
{
	cout << "B version" << endl;
}

template<class I>
void func(I &p, D)
{
	cout << "D version" << endl;
}

int main()
{
	int *p;
	func(p,B());
	func(p,C());
	func(p,D());
	return 0;
}
