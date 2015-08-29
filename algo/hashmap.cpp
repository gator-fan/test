#include <iostream>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

int main()
{
	hash_map<int, string> hm(3);
	hm.insert(make_pair(0, "hello"));
	hm.insert(make_pair(1, "ok"));
	hm.insert(make_pair(2, "bye"));
	hm.insert(make_pair(3, "world"));
	cout << hm.size() << endl;
	cout << hm.bucket_count() << endl;
	return 0;
}
