#include <iostream>

using namespace std;

class Test{
	public:
	int c;
};

int main()
{
	Test* t = new Test;
	cout << t->c << endl;
	return 0;
}
