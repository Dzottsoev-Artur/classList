#include <iostream>
#include <cassert>

class BoolVec;

class Bit
{
    friend class BoolVec;
private:
    int index;
public:
    Bit(int);
    Bit operator=(int);

};

Bit::Bit(int ind)
{
    index = ind;
}

Bit Bit::operator=(int Index)
{
    if (Index == 1)
    {
        unsigned char mask = 1 << index;
        [bytes] = vector[bytes] | mask;
    }
}

class BoolVec
{
    friend class Bit;
private:
    unsigned char* vector;
    unsigned int bytes = 0, bits = 0;

public:
    BoolVec(int quantityBits = 0, int value = 0);
    friend std::ostream& operator << (std::ostream& Cout, BoolVec&);
    Bit operator[](int);
};


BoolVec::BoolVec(int quantityBits, int value)
{
    assert(quantityBits > 0 && (value == 1 || value == 0));
    int lenVec = (quantityBits - 1) / 8 + 1;
    vector = new unsigned char[lenVec];
    int byte = quantityBits / 8, bit;

    while (byte >= 0)
    {
        vector[byte] = 0;
        byte--;
    }

    if(value == 1)
        for (int i = 0; i < quantityBits; i++)
        {
            byte =  i / 8;
            bit = i % 8;
            unsigned char mask = 1 << (7 - bit);
            vector[byte] = vector[byte] | mask;
        }

    bits = quantityBits;
    bytes = bits / 8;

}

Bit BoolVec::operator[](int index)
{
    return
}

std::ostream& operator <<(std::ostream& Cout, BoolVec& Boolvec)
{
    for(int i = 0; i < Boolvec.bits; i++)
    {
        unsigned char mask = 1 << (7 - Boolvec.bits);
        return Boolvec[Boolvec.bytes];
    }
}

int main()
{
    BoolVec A;
}
