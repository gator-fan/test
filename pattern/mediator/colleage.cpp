#include <iostream>
#include "mediator.h"
#include "colleage.h"

using namespace std;

Colleage::Colleage(){
	cout << "Colleage()" << endl;
}

colleage::Colleage(Mediator* mdt){
	cout << "Colleage(Mediator*)" << endl;
	this->_mdt = mdt;
}

Colleage::~Colleage(){
	cout << "~Colleage()" << endl;
}

ConcreteColleageA::ConcreteColleageA(){
	cout << "ConcreteColleageA()" << endl;
}

ConcreteColleageA::~ConcreteColleageA(){
	cout << "~ConcreteColleageA()" << endl;
}

ConcreteColleageA::ConcreteColleageA(Mediator* mdt):Colleage(mdt){
	cout << "ConcretColleageA(Mediator*)" << endl;
}

string ConcreteColleageA::GetState(){
	return _sdt;
}

void ConcreteColleageA::SetState(const string& sdt){
	_sdt = sdt;
}

void ConcreteColleageA::Action(){
	_mdt->DoActionFromAtoB();
	cout << "State of ConcreteColleageB: " << this->GetState() << endl;
}

ConcreteColleageB::ConcreteColleageB(){
	cout << "ConcreteColleageB()" << endl;
}
