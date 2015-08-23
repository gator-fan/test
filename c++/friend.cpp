template<class T>
class Friendly{
	template<class U>
		friend void f<>(const Friendly<U> &);
}
