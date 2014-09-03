#include<iostream>
#include<string.h>

using namespace std;

class CMyString
{
public:
    CMyString(const char*pData = NULL);
    CMyString(const CMyString &str);
	CMyString & operator =(CMyString &str);
    ~CMyString();
    void swap(CMyString &str);

    void printStr() {
        cout << m_pData << endl;
    }
private:

    char* m_pData;

};

CMyString::CMyString(const char* pData)
{
    if(pData == NULL) {
        m_pData = new char[1];
        *m_pData = '\0';
    } else {
        int length = strlen(pData);
        m_pData = new char[length+1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &str)
{
    int length = strlen(str.m_pData);
    m_pData = new char[length+1];
    strcpy(m_pData, str.m_pData);
}

CMyString & CMyString::operator =(CMyString &str)
{
    CMyString tmp(str);
    swap(tmp);                 // copy and swap  
    return *this;
}

void CMyString::swap(CMyString &str)
{
    char *tmp;
    tmp = str.m_pData;
    str.m_pData = m_pData;
    m_pData = tmp;
}

CMyString::~CMyString()
{

    delete[] m_pData;
}



int main()
{
    CMyString t1("hello");
    CMyString t2("world");
    CMyString t3(t1);

    t3.printStr();
    t3 = t2;
    t3.printStr();
	t3 = t3;
    t3.printStr();

	return -1;
}
