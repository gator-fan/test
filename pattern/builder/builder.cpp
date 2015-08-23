#include "builder.h"
#include "product.h"
#include <iostream>

using namespace std;

Builder::Builder(){
	cout << "Builder()" << endl;
}

Builder::~Builder(){
	cout << "~Builder()" << endl;
}

ConcreteBuilder::ConcreteBuilder(){
	cout << "ConcreteBuilder()" << endl;
}

ConcreteBuilder::~ConcreteBuilder(){
	cout << "~ConcreteBuilder()" << endl;
}

void ConcreteBuilder::BuildPartA(const string& buildPara){
	cout << "step 1: build part A" << buildPara << endl;
}

void ConcreteBuilder::BuildPartB(const string& buildPara){
	cout << "step 2: build part B" << buildPara << endl;
}

void ConcreteBuilder::BuildPartC(const string& buildPara){
	cout << "step 3: build part C" << buildPara << endl;
}

Product * ConcreteBuilder::GetProduct(){
	BuildPartA("AAA");
	BuildPartB("BBB");
	BuildPartC("CCC");
	return new Product();
}
