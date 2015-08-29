#include "template.h"
#include <iostream>

using namespace std;

AbstractClass::AbstractClass(){
	cout << "AbstractClass()" << endl;
}

AbstractClass::~AbstractClass(){
	cout << "~AbstractClass()" << endl;
}

void AbstractClass::TemplateMethod(){
	this->PrimitiveOperation1();
	this->PrimitiveOperation2();
}

ConcreteClass1::ConcreteClass1(){
	cout << "ConcreteClass1()" << endl;
}

ConcreteClass1::~ConcreteClass1(){
	cout << "~ConcreteClass1()" << endl;
}

void ConcreteClass1::PrimitiveOperation1(){
	cout << "ConcreteClass1::PrimitiveOperation1()" << endl;
}

void ConcreteClass1::PrimitiveOperation2(){
	cout << "ConcreteClass1::PrimitiveOperation2()" << endl;
}

ConcreteClass2::ConcreteClass2(){
	cout << "ConcreteClass2()" << endl;
}

ConcreteClass2::~ConcreteClass2(){
	cout << "~ConcreteClass2()" << endl;
}

void ConcreteClass2::PrimitiveOperation1(){
	cout << "ConcreteClass2::PrimitiveOperation1" << endl;
}

void ConcreteClass2::PrimitiveOperation2(){
	cout << "ConcreteClass2::PrimitiveOperation2" << endl;
}
