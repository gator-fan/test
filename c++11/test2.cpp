#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Widget{
	public:
		Widget(){ i = 0;}
		Widget(int ii):i(ii){}
		~Widget(){}
		int getI(){return i;}
	private:
		int i;
};


class BadPredicate:public unary_function<Widget, bool>{
	public:
		BadPredicate():timesCalled(0){ }
		bool operator()(const Widget & w){
			return ++timesCalled == 0;
		}
	private:
		size_t timesCalled;
};

ostream& operator << (ostream & out, Widget w){
	out << w.getI() << " ";
	return out;
}


int main(){
	vector<Widget> vw;
	for(int i = 0; i < 10; i++)
		vw.push_back(Widget(i));

	copy(vw.begin(), vw.end(), ostream_iterator<Widget>(cout, "\n"));
	cout << endl;

	//vw.erase(vw.begin()+vw.size()/2, vw.end());
	//copy(vw.begin(), vw.end(), ostream_iterator<Widget>(cout, "\n"));
	//cout << endl;

	vw.erase(remove_if(vw.begin(), vw.end(), BadPredicate()), vw.end());
	copy(vw.begin(), vw.end(), ostream_iterator<Widget>(cout, "\n"));
	cout << endl;
	return 0;
}
