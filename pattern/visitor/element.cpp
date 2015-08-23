#include <iostream>
#include "element.h"
#include "visitor.h"

using namespace std;

Element::Element(){
	cout << "Element()" << endl;
}

Element::~Element(){
	cout << "~Element()" << endl;
}

void Element::Accept(Visitor* vis){

}

ConcreteElementA::ConcreteElementA(){
	cout << "ConcreteElementA()" << endl;
}

ConcreteElementA::~ConcreteElementA(){
	cout << "~ConcreteElementA()" << endl;
}

void ConcreteElementA::Accept(Visitor* vis){
	vis->VisitConcreteElementA(this);
	cout << "Visiting ConcreteElementA..." << endl;
}

ConcreteElementB::ConcreteElementB(){
	cout << "ConcreteElementB()" << endl;
}

ConcreteElementB::~ConcreteElementB(){
	cout << "~ConcreteElementB()" << endl;
}

void ConcreteElementB::Accept(Visitor* vis){
	vis->VisitConcreteElementB(this);
	cout << "Visiting ConcreteElementB..." << endl;
}
