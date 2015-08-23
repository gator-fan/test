#include "product.h"
#include <iostream>

using namespace std;

Product::Product(){
	cout << "Product()" << endl;
}

Product::~Product(){
	cout << "~Product()" << endl;
}

void Product::ProducePart(){
	cout << "ProductPart()" << endl;
}

ProductPart::ProductPart(){
	cout << "ProductPart()" << endl;
}

ProductPart::~ProductPart(){
	cout << "~ProductPart()" << endl;
}

ProductPart *BuildPart(){
	cout << "BuildPart()" << endl;
	return new ProductPart;
}
