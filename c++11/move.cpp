#include <iostream>

using namespace std;

class HasPtrMem{
	public:
		HasPtrMem():d(new int(3)){
			cout << "HasPtrMem()" << endl;
		}
		HasPtrMem(HasPtrMem & h):d(new int(*h.d)){
			cout << "HasPtrMem(&)" << endl;
		}
		HasPtrMem(HasPtrMem &&h):d(h.d){
			h.d = nullptr;
			cout << "HasPtrMem(&&)" << endl;
		}
		~HasPtrMem(){
			delete d;
			cout << "~HasPtrMem()" << endl;
		}
		int * d;
};

HasPtrMem GetTmp(){
	HasPtrMem h;
	cout << "Resouce from " << __func__ << ":" << hex << h.d << endl;
	return h;
}

int main(){
	HasPtrMem a = GetTmp();
	cout << "Resouce from " << __func__ << ":" << hex << a.d << endl;
	return 0;
}
