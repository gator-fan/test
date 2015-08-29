#include <iostream>
#include <string.h>

using namespace std;

class String{
	public:
		String(const char*str = NULL);
		String(const String &another);
		~String();
		String& operator = (const String&);
		friend String operator+(const String&, const String&);
		friend ostream& operator << (ostream&, const String& s);  
		friend istream& operator>>(istream& in, String& s);
	private:
		char* m_data;
};

String::String(const char*str)
{
	if(str == NULL)
		m_data = NULL;
	else
	{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
}

String::String(const String& another)
{
	m_data = new char[strlen(another.m_data)+1];
	strcpy(m_data, another.m_data);
}

String::~String()
{
	if(m_data != NULL)
	{
		delete []m_data;
		m_data = NULL;
	}
}

String& String::operator= (const String& rhs)
{
	if(*this == rhs) return *this;
	delete [] m_data;
	m_data = NULL;
	m_data = new char[strlen(rhs.m_data)+1];
	strcpy(m_data, rhs.m_data);
	return *this;
}

ostream& operator << (ostream& out, const String& s)  
{  
	if(s.m_data)  
		out << s.m_data << endl;  
	return out;  
}  
istream& operator>>(istream& in, String& s)  
{  
	char q[1000];  
		    in >> q;  
		   s.m_data = new char[strlen(q)+1];  
		   strcpy(s.m_data,q);   
		   return in;  
		}  
String operator+(const String& lhs,const String&rhs)  
{  
	String *ret = new String(lhs);  
	strcat(ret->m_data,rhs.m_data);  
	return *ret;  
}  
int main()  
{  
	String s ;  
	cin >> s;  
	String s1;  
	cin >> s1;  
	String s2 = s+s1;//this sentence has question , but i don't know why  
	cout << s2;  
}  

