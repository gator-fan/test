#include <iostream>
#include "handle.h"

using namespace std;

Handle::Handle(){
	cout << "Handle()" << endl;
	//Handle * _succ = new Handle;
	_succ = NULL;
}

Handle::~Handle(){
	cout << "~Handle()" << endl;
	//delete _succ;
}

Handle::Handle(Handle* succ){
	cout << "Handle(Handle*) " << endl;
	this->_succ = _succ;
}

void Handle::SetSuccessor(Handle* succ){
	_succ = succ;	
}

Handle* Handle::GetSuccessor(){
	return _succ;
}

void Handle::HandleRequest(){
	cout << "Handle::Handle" << endl;
}

ConcreteHandleA::ConcreteHandleA(){
	cout << "ConcreteHandleA()" << endl;
	Handle* _succ = new Handle;
	_succ = NULL;
}

ConcreteHandleA::ConcreteHandleA(Handle *succ):Handle(succ){
	cout << "ConcrteHandleA(Handle *succ)" << endl;
}

ConcreteHandleA::~ConcreteHandleA(){
	cout << "~ConcreteHandleA()" << endl;
}

void ConcreteHandleA::HandleRequest(){
	if(this->GetSuccessor() != 0 ){
		cout << "ConcreteHandleA pass to the successor..." << this->GetSuccessor() << endl;
		this->GetSuccessor()->HandleRequest();
	} else {
		cout << "ConcreteHandleA has no successor..." << endl;
	}
}

ConcreteHandleB::ConcreteHandleB(){
	cout << "ConcreteHandleB()"	 << endl;
}

ConcreteHandleB::ConcreteHandleB(Handle *succ):Handle(succ){
	cout << "ConcreteHandleB(Handle *)" << endl;
}

ConcreteHandleB::~ConcreteHandleB(){
	cout << "~ConcreteHandleB()" << endl;
}

void ConcreteHandleB::HandleRequest(){
	if(this->GetSuccessor() != 0 ){
		cout << "ConcreteHandleB pass to the successor..." << this->GetSuccessor() << endl;
		this->GetSuccessor()->HandleRequest();
	} else {
		cout << "ConcreteHandleB has no successor..." << endl;
	}
}
