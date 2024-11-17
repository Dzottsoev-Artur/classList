#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<cmath>
typedef unsigned int BASE;
#define BASE_SIZE (sizeof(BASE)*8)

using namespace std;

class BigNumber
{
private:
    int sign, maxLen;
    vector<BASE>coeff;

public:
    BigNumber();
    BigNumber(int MaxLen);
    BigNumber(int MaxLen, bool flag);
    BigNumber(BigNumber&);
    BigNumber& operator = (BigNumber&);
    ~BigNumber();
};

BigNumber::BigNumber() : BigNumber(1)
{}
BigNumber::BigNumber(int MaxLen)
{
    maxLen = MaxLen;
    for(int i = 0; i < maxLen; i++)
        coeff.push_back(0);
}

BigNumber::BigNumber(int maxlen, bool flag)
{
    maxLen = maxlen;

    for(int i = 0; i < maxLen; i++)
        coeff.push_back(rand());

    for(int n : coeff)
        cout << n << "\t";

    cout << "\n";
    if(BASE_SIZE > 16)
    {
        for(int i = 0; i < maxLen; i++)
        {
            coeff[i] = coeff[i] << 16;
            coeff[i] = coeff[i] +  rand();
        }    
        for(int n : coeff)
            cout << n << "\t";
    }        
}
 

BigNumber::BigNumber(BigNumber& BigNumber)
{
    maxLen = BigNumber.maxLen;
    sign = BigNumber.sign;
    coeff = BigNumber.coeff;
}

BigNumber::~BigNumber()
{
    coeff.clear();
}

BigNumber& BigNumber::operator=(BigNumber& bigNumber)
{
    if(this != &bigNumber)
    {
        maxLen = bigNumber.maxLen;
        sign = bigNumber.sign;
        coeff = bigNumber.coeff;
    }
    return *this;
}

int main()
{   
    srand(time(nullptr));

    BigNumber BigNum(5, true);
}