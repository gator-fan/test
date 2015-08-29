#include "element.h"
#include "visitor.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	Visitor *vis = new ConcreteVisitorA();
	Element *elm = new ConcreteElementA();
	elm->Accept(vis);

	delete vis;
	delete elm;
	return 0;
}
