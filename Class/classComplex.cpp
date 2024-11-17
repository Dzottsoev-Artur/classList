#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
    double re;
    double im;
public:
    int lenNum(double Number);
    Complex(double Re = 0, double Im = 0);
    double getRe();
    void setRe(double);
    double getIm();
    void setIm(double);
    bool operator == (const Complex &);
    bool operator != (const Complex &);
    double mod(); // возвращает модуль комплексного числa
    operator char*(); // преобразует комплексное число в строку
    Complex operator - (); // возвращает комплексно сопряженное число
    Complex operator + (const Complex &);
    Complex& operator += (const Complex &);
    Complex operator - (const Complex &);
    Complex& operator -= (const Complex &);
    Complex operator * (const Complex &);
    Complex& operator *= (const Complex &);
    Complex operator / (const Complex &);
    Complex& operator /= (const Complex &);
    friend istream& operator>> (istream&, Complex &);
    friend ostream& operator<< (ostream&, const Complex &);
};
Complex::Complex(double Re, double Im)
{
    re = Re;
    im = Im;
}

int Complex::lenNum(double Number)
{
    int digree = 2, len = 1, newNumber;
    if(modf(Number, nullptr) != 0)
    {
        len += Number > 1 ? 1 : 2;
        Number *= pow(10, digree);

        newNumber = Number;
        while (newNumber /= 10)
        {
            len++;
        }
        newNumber = Number;
        while(newNumber % 10 == 0)
        {
            len--;
            newNumber /= 10;
        }    
    }
    else
    {
        newNumber = Number;
        while(newNumber /= 10)
            len++;
    }
    return len;
}

Complex::operator char*()
{   
    char* complex;
    int buf, baf, len = lenNum(re) + lenNum(im) + 2;
    if(re < 0)
       len++;

    complex = new char[len + 1];
    complex[len] = '\0';
    complex[len - 1] = 'i';
    if(modf(re, nullptr) != 0)
    {
        buf = re * 100;
        if(buf % 10 == 0)
            buf = buf / 10;
    }
    else
        buf = re;

    if(modf(im, nullptr) != 0)
    {
        baf = im * 100;
        if(baf % 10 == 0)
            baf = baf / 10;
    }
    else
        baf = im;

    buf = abs(buf);
    baf = abs(baf);

    for(int i = len - 2; baf != 0; i--, baf /= 10)
        complex[i] = '0' + baf % 10;
    
    complex[len - lenNum(im) - 2] = im < 0 ?  '-' : '+';

    for(int i = len - lenNum(im) - 3; buf != 0; i--, buf /= 10)
        complex[i] = '0' + buf % 10;
    
    if(re < 0)
        complex[0] = '-';

    return complex;
}


istream& operator>> (istream& Cin, Complex& number)
{
    cout <<"Enter Re: ";       
    Cin >> number.re;
    cout <<"Enter Im: ";
    Cin >> number.im;
    return Cin;
}

ostream& operator<< (ostream& Cout, const Complex& number)
{
    number.im > 0 ? Cout << number.re << '+' << number.im << 'i' :
        Cout << number.re << number.im << 'i';
    return Cout;
}

bool Complex::operator ==(const Complex &y)
{
    if(re == y.re && im == y.im)
    {
        return true;
    }
    else return false;
}

bool Complex::operator !=(const Complex &y)
{
    if(re != y.re || im != y.im)
    {
        return true;
    }
    else return false;
}

double Complex:: mod()
{
    return sqrt(re*re + im*im);
}

double Complex::getRe()
{
    return re;
}

double Complex::getIm()
{
    return im;
}

void Complex::setRe(double Re)
{
    re = Re;
}   

void Complex::setIm(double Im)
{
    im = Im;
}

Complex Complex::operator -()//Комплексно сопряженное число
{   
    Complex z;
    z.re = re;
    z.im = -im;
    return z;
}

Complex Complex::operator +(const Complex &y)
{
    Complex z;
    z.re = re + y.re;
    z.im = im + y.im;
    return z;
}

Complex& Complex::operator +=(const Complex &y)
{
    re += y.re;
    im += y.im;
    return *this;
}    

Complex Complex::operator -(const Complex &y)
{  
    Complex z;
    z.re = re - y.re;
    z.im = im - y.im;
    return z;
}

Complex& Complex::operator -=(const Complex &y)
{
    re -= y.re;
    im -= y.im;
    return *this;
}

Complex Complex::operator *(const Complex &y)
{
    Complex z;
    z.re = (re * y.re) - (im * y.im);
    z.im = (re * y.im) + (im * y.re);
    return z;
}

Complex& Complex::operator *=(const Complex &y)
{
    double remember = (re * y.re) - (im * y.im);
    im = (re * y.im) + (im * y.re);
    re = remember;
    return *this;
}

Complex Complex::operator /(const Complex &y)
{
    Complex z;
    z.re = (re * y.re + im * y.im) / (y.re * y.re + y.im * y.im);
    z.im = (im * y.re - re * y.im) / (y.re * y.re + y.im * y.im);
    return z;
}

Complex& Complex::operator/=(const Complex &y)
{
    double remember = (re * y.re + im * y.im) / (y.re * y.re + y.im * y.im);
    im = (im * y.re - re * y.im) / (y.re * y.re + y.im * y.im);
    re = remember;
    return *this;
}


int main ()
{
    Complex a, b;
  
    return 0;
}
    