#include <iostream>
using namespace std;

struct Rational1{
	Rational1(int n = 0, int d = 1):num(n), den(d){
		cout << __func__ << "(" << num << "/" << den << ")" << endl;
	}
	int num;
	int den;
};

struct Rational2{
	Rational2(int n = 0, int d = 1):num(n), den(d){
		cout << __func__ << "(" << num << "/" << den << ")" << endl;
	}
	int num;
	int den;
};

void Display1(Rational1 ra){
	cout << "Numerator: " << ra.num << "Denominator: " << ra.den << endl;
}

void Display2(Rational2 ra){
	cout << "Numerator: " << ra.num << "Denominator: " << ra.den << endl;
}

int main(){
	Rational1 r1_1 = 11;
	Rational1 r1_2(11);

	Rational2 r2_1 = 11; //fail
	Rational2 r2_2(11);

	Display1(1);
	Display2(2); //fail
	Display2(Rational2(2));

	return 0;
}
