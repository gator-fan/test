#include <iostream>

using namespace std;

class HasPtrMem{
	public:
		HasPtrMem():d(new int(5)){cout << "defult" << endl;}
		HasPtrMem(HasPtrMem& h):d(new int(*h.d)){cout << "copy" << endl;}
		~HasPtrMem(){delete d; cout << "delete" << endl;}
		int * d;
};

int main()
{
	HasPtrMem a;
	HasPtrMem b(a);
	cout << *a.d << endl;
	cout << *b.d << endl;
	return 0;
}
