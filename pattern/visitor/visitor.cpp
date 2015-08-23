#include <iostream>
#include "visitor.h"
#include "element.h"

using namespace std;

Visitor::Visitor(){
	cout << "Visitor()" << endl;
}

Visitor::~Visitor(){
	cout << "~Visitor()" << endl;
}

ConcreteVisitorA::ConcreteVisitorA(){
	cout << "ConcreteVisitorA()" << endl;
}

ConcreteVisitorA::~ConcreteVisitorA(){
	cout << "~ConcreteVisitorA()" << endl;
}

void ConcreteVisitorA::VisitConcreteElementA(Element* elm){
	cout << "I will visit ConcreteElementA from visitor A" << endl;
}

void ConcreteVisitorA::VisitConcreteElementB(Element* elm){
	cout << "I will visit ConcreteElementB from visitor A" << endl;
}

ConcreteVisitorB::ConcreteVisitorB(){
	cout << "ConcreteVisitorB()" << endl;
}

ConcreteVisitorB::~ConcreteVisitorB(){
	cout << "~ConcreteVisitorB()" << endl;
}

void ConcreteVisitorB::VisitConcreteElementA(Element* elm){
	cout << "I will visit ConcreteElementA from visitor B" << endl;
}

void ConcreteVisitorB::VisitConcreteElementB(Element* elm){
	cout << "I will visit ConcreteElementB from visitor B" << endl;
}
