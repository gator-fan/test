#include <iostream>
using namespace std;

class HasPtrMem{
	public:
		HasPtrMem():d(new int(0)){
			cout << "HasPtrMem()" << endl;
		}
		// temp must use const
		HasPtrMem(const HasPtrMem& h):d(new int(*h.d)){
			cout << "HasPtrMem(&)" << endl;
		}
		~HasPtrMem(){
			cout << "~HasPtrMem()" << endl;
		}
		int *d;
};

HasPtrMem GetTmp(){
	return HasPtrMem();
}

int main(){
	HasPtrMem a = GetTmp();
	return 0;
}
