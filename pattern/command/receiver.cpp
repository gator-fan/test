#include <iostream>
#include "receiver.h"

using namespace std;

Receiver::Receiver(){
	cout << "Receiver()" << endl;
}

Receiver::~Receiver(){
	cout << "~Receiver()" << endl;
}

void Receiver::Action(){
	cout << "Receiver action ...." << endl;
}
