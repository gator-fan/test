#include <iostream>

using namespace std;

template<bool cond>
struct Select{};

template<>
class Select<true>{
	static void statement1(){
		cout << "statement1" << endl;
	}
	public:
		static void f(){
			statement1();
		}
};

template<>
class Select<false>{
	static void statement2(){
		cout << "statement2" << endl;
	}
	public:
		static void f(){
			statement2();
		}
};

template<bool cond>
void execute(){
	Select<cond>::f();
}

int main()
{
	execute<sizeof(int) == 4>();
	return 0;
}
