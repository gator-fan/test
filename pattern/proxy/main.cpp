#include <iostream>
#include "proxy.h"

using namespace std;

int main(int argc, char *argv[])
{
	Subject *sub = new ConcreteSubject();
	Proxy *p = new Proxy(sub);
	p->Request();
	delete p;
	//delete sub;
	return 0;
}
