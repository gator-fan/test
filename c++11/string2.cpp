#include <iostream>
#include <string.h>

using namespace std;

class String{
	    friend ostream& operator<< (ostream&, String&);
	public:
		    String(const char* str = NULL);
			    String(const String &other);
				    String& operator=(const String& other);
					    String operator+(const String &other)const;
						    bool operator == (const String&);
							    char& operator[](unsigned int);
								    size_t size(){return strlen(m_data);}
									    ~String(void){delete[] m_data;}
	private:
										    char* m_data;
};

inline String::String(const char* str)
{
	    if(!str) m_data = 0;
		    else{
				        m_data = new char[strlen(str)+1];
						        strcpy(m_data, str);
								    }
}

inline String::String(const String &other)
{
	    if(!other.m_data) m_data = 0;
		    else{
				        m_data = new char[strlen(other.m_data)+1];
						        strcpy(m_data, other.m_data);
								    }
}

inline String& String::operator=(const String& other)
{
	    if(*this == other) return *this;
		    else {
				        delete[] m_data;
						        if(!other.m_data) m_data = 0;
								        else{
											            m_data = new char[strlen(other.m_data)+1];
														            strcpy(m_data, other.m_data);
																	        }
										    }
}

inline String String::operator+(const String& other) const
{
	    String newString;
		    if(!other.m_data)
				        newString = *this;
			    else if(!m_data)
					        newString = other;
				    else{
						        newString.m_data = new char[strlen(other.m_data)+strlen(m_data)+1];
								        strcpy(newString.m_data, m_data);
										        strcat(newString.m_data, other.m_data);
												    }
					    return newString;
}

inline bool String::operator == (const String& other)
{
	    if(strlen(m_data) != strlen(other.m_data))
			        return false;
		    return strcmp(m_data, other.m_data)?false:true;
}

inline char& String::operator[](unsigned int e)
{
	    if(e >= 0 && e <= strlen(m_data))
			        return m_data[e];
}

ostream& operator<<(ostream& os, String& str)
{
	    os << str.m_data;
		    return os;
}


int main()
{
	    String str1 = "Hello";
		    String str2 = "Fan";
			    String str3 = str1 + str2;
				    cout << "str3 is " << str3 << endl;
					    cout << "str3.size() is " << str3.size() << endl;
						    return 0;
}

