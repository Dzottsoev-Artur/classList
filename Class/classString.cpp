#include <iostream>
#include <cstring>

using namespace std;
class String
{
private:
    char* str;
    int len;
public:
    String(int l = 0);
    String(const char *std);
    String(String &);
    ~String();
    int Len();
    int BM_search(String &);
    char &operator [](int );
    bool operator == (String &);
    bool operator != (String &);
    String & operator = (const String &);
    String operator + (const String &);
    String & operator += (const String &);
    friend istream & operator >> (istream &, String &);
    friend ostream & operator << (ostream &, String &);
};

String::String(int l)
{
    len = l;
    str =  new char[l + 1];
    str[len] = '\0';
}

String::String(const char* st )
{
    len = strlen(st);
    str =  new char[len + 1];

    for(int i = 0; i < len; i++)
        str[i] = st[i];
    str[len] ='\0';
}

String::String(String& S)
{
    len = strlen(S.str);
    str =  new char[len + 1];

    for(int i = 0; i < len; i++)
        str[i]= S.str[i];
    str[len]= '\0';
}

String::~String()
{
    if(str) 
        delete []str; 
    str = NULL; 
}
int String::Len()
{
    return len;
}
String& String::operator=(const String& S)
{
    if(this != &S)
    {
        if(len !=S.len)
        {
            if(str != nullptr)
                delete[] str;
            len = strlen(S.str);
            str =  new char[len + 1];
        }    
        for(int i = 0; i < len; i++)
            str[i] = S.str[i];
        str[len] ='\0';
    } 
    return *this;
}

char& String::operator[](int index)
{
    return (index < 0 || index > len - 1) ? str[len] : str[index];
} 

bool String::operator==(String& S)
{
    if(len == S.len)
    {
        for(int i = 0; i < strlen(str); i++)   
            if (str[i] != S.str[i])
                return false;
        return true;
    }  
    return false;
}
bool String::operator!=(String& S)
{
    return !(*this == S); 
}
String String::operator+(const String& S)
{ 
    String newS;
    int lenStr = strlen(str);
    int lenS = strlen(S.str);
    newS.str = new char[lenStr + lenS + 1];
    int i = 0;
    for(; i < lenStr; i++)
        newS.str[i] = str[i];

    for(int j = 0; j < lenS ; i++, j++)
        newS.str[i] = S.str[j];

    newS.str[lenStr + lenS] ='\0';
    
    return newS;
}
String& String::operator+=(const String& S)
{   
    String newS;
    int lenStr = strlen(str);
    int lenS = strlen(S.str);
    newS.str = new char[lenStr + lenS + 1];
    int i = 0;

    for(; i < lenStr; i++)
        newS.str[i] = str[i];

    for(int j = 0; j < lenS ; i++, j++)
        newS.str[i] = S.str[j];

    int lenstr = lenS + lenStr;
    delete [] str;
    str = new char[lenstr + 1];

    for(int i = 0; i < lenstr; i++)
        str[i] = newS.str[i];
    str[lenstr] = '\0';

    return *this;
}


ostream & operator<<(ostream& Cout, String& S)
{
    Cout << S.str;
    return Cout;
}
istream & operator>>(istream& Cin, String& S)
{
    char temp[50];
    Cin.get(temp, 50);
    int Len = strlen(temp);
    if (Cin)
        S = String(temp);    

    return Cin;
}

int String::BM_search(String& S)
{
    //Таблица формирования
    int *arr = new int[256];
    int lenSubstring = strlen(S.str);

    for (int i = 0; i < 256;i++)
        arr[i]= lenSubstring ;
        
    for(int i = 0; i < lenSubstring - 1;i++)
        arr[S.str[i]] = lenSubstring - 1 - i;
    //БМ - поиск

    int lenString = strlen(str);
    for(int i = lenSubstring - 1, j = lenSubstring - 1, k = i;i < lenString && j >=0; k = i)
    {
        while (j >= 0 && S.str [j] == str [k])
        {
            j--;
            k--;
        }
        if(j < 0)
            return i + 1 - lenSubstring;

        i += arr[str[i]];
        j = lenSubstring - 1;

    }
    return -1;

}

int main()
{
    String s("FFFOWGOM");
    String A("GOM");
    //A = A;
    //cout << (s = A);
    //cout << (s += A);
    //cout << s[-1];
    //String B(s);
    //cout << B;
    //cout << B.Len();
    //cout << (s == A);
    String K = s + A;
    //cin >> K;
    cout << K;
    //cout << (s.BM_search(A));
    return 0;
}