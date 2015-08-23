#include "director.h"
#include "builder.h"

Director::Director(Builder* bld){
	_bld = bld;
}

Director::~Director(){

}

void Director::Construct(){
	_bld->BuildPartA("AAAAAA");
	_bld->BuildPartB("BBBBBB");
	_bld->BuildPartC("CCCCCC");
}
