#include <memory>
#include <iostream>

using namespace std;

int main(){
	unique_ptr<int> up1(new int(11));
	//unique_ptr<int> up2 = up1;
	cout << *up1 << endl;
	unique_ptr<int> up3 = move(up1);
	cout << *up3 << endl;
	//cout << *up1 << endl;

	up3.reset();
	up1.reset();

	//cout << *up3 << endl;

	shared_ptr<int> sp1(new int(22));
	shared_ptr<int> sp2 = sp1;

	cout << *sp1 << endl;
	cout << *sp2 << endl;

	sp1.reset();
	cout << *sp2 << endl;
	//cout << *sp1 << endl;

	return 0;
}
