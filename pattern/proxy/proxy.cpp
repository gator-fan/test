#include <iostream>
#include "proxy.h"

using namespace std;

Subject::Subject(){
	cout << "Subject()" << endl;
}

Subject::~Subject(){
	cout << "~Subject()" << endl;
}

ConcreteSubject::ConcreteSubject(){
	cout << "ConcreteSubject()" << endl;
}

ConcreteSubject::~ConcreteSubject(){
	cout << "~ConcreteSubject()" << endl;
}

void ConcreteSubject::Request(){
	cout << "ConcretSubject ...Requst()..." << endl;
}

Proxy::Proxy(){
	cout << "Proxy()" << endl;
}

Proxy::Proxy(Subject * sub){
	cout << "Proxy(Subject*)" << endl;
	_sub = sub;
}

Proxy::~Proxy(){
	cout << "~Proxy()" << endl;
	delete _sub;
}

void Proxy::Request(){
	cout << "Proxy...Request()..." << endl;
	_sub->Request();
}

