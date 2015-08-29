#include "prototype.h"
#include <iostream>

using namespace std;

Prototype::Prototype(){
	cout << "Prototype()" << endl;
}

Prototype::~Prototype(){
	cout << "~Prototype()" << endl;
}

Prototype *Prototype::Clone() const{
	return 0;
}

ConcretePrototype::ConcretePrototype(){
	cout << "ConcretePrototype()" << endl;
}

ConcretePrototype::~ConcretePrototype(){
	cout << "~ConcretePrototype()" << endl;
}

ConcretePrototype::ConcretePrototype(const ConcretePrototype &cp) {
	cout << "ConcretePrototype(const &)" <<endl;
}

Prototype * ConcretePrototype::Clone() const{
	return new ConcretePrototype(*this);
}
