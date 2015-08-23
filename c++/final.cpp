#include <iostream>

using namespace std;

template<typename T>
class MakeSealed
{
	friend T;
	private:
		MakeSealed(){cout << "MakeSealed()" << endl;}
		~MakeSealed(){}
};

//class SealedClass:public MakeSealed<SealedClass>
class SealedClass:virtual public MakeSealed<SealedClass>
{
	public:
		SealedClass(){cout << "SealedClass" << endl;}
		~SealedClass(){}
};

class Try:public SealedClass
{
	public:
		Try(){cout << "Try()" << endl;}
		~Try(){}
};

int main()
{
	SealedClass s;
	Try t;
	return 0;
}
