#include<iostream>
#include<cstring>

using namespace std;
class BoolV
{ 
private:    
    unsigned char *vector;
    int len; // len – количество бит вектора
public:
    BoolV(int size = 1); // формируется булев вектор из nn бит; все биты со значениями 0
    BoolV(const char*); // формируется булев вектор по строке из нулей и единиц
    BoolV(BoolV &);
    ~BoolV();


    void Set1(int); // устанавливает указанный бит в 1
    void Set0(int); // устанавливает указанный бит в 0
    unsigned char operator[](int) const;
    bool operator == (const BoolV &);// равенство векторов
    int weight();
    BoolV& operator = (const BoolV &);
    BoolV operator | (const BoolV &);
    BoolV operator & (const BoolV &);
    BoolV& operator &=(const BoolV &);
    BoolV operator ~ ();
    friend ostream & operator << (ostream &, const BoolV &);
    friend istream & operator >> (istream &, BoolV &);
};

BoolV::BoolV(int size)
{
    len = size;
    vector = new unsigned char[len + 1];
    for(int i = 0; i < len; i++)
        vector[i] = 0;
    vector[len] = '\0';
}

BoolV::BoolV(const char* vec)
{
    len = strlen(vec);
    vector = new unsigned char[len + 1];
    for(int i = 0; i < len; i++)
    {
        vector[i] = vec[i];
    }
    vector[len] = '\0';
}

BoolV::BoolV(BoolV& vec)
{
    len = vec.len;
    vector = new unsigned char[len + 1];
    for(int i = 0; i < len; i++)
    {
        vector[i] = vec.vector[i];
    }
    vector[len] = '\0';
}

BoolV::~BoolV()
{
    if(vector)
        delete[] vector;
}

void BoolV::Set1(int index)
{
    vector[index] = 1;
}

void BoolV::Set0(int index)
{
    vector[index] = 0;
}

unsigned char BoolV::operator[](int index) const
{
    if(index < 0 || index > len - 1)
    {
        return '\0';
    }
    return vector[index];
}

bool BoolV::operator==(const BoolV& vec)
{
    if(len == vec.len)
    {
        for(int i = 0; i < len; i++)   
            if (vector[i] != vec.vector[i])
                return false;
        return true;
    }
    return false;
}

int BoolV::weight()
{
    int weight = 0;
    for(int i = 0; i < len; i++)
        if(vector[i] == 1)
            weight++;
    return weight;
}

BoolV& BoolV::operator=(const BoolV& vec)
{
    if(this != &vec)
    {
        if(len != vec.len)
        {
            if(vector)
                delete[] vector;
            len = vec.len;
            vector =  new unsigned char[len + 1];
        }
  
        for(int i = 0; i < len; i++)
        {
            vector[i] = vec.vector[i];
        }
        vector[len] = '\0';
    } 
    return *this;
}

BoolV BoolV:: operator |(const BoolV& vec)
{
    BoolV Vec;
    
    if(len == vec.len)
    {
        if (Vec.vector) 
        {
            delete[] Vec.vector;
        }
        Vec.len = len;
        Vec.vector = new unsigned char[len + 1];
        for(int i = 0; i < len; i++)
        {
            if(vec[i] == 1 || vector[i] == 1)
                Vec.vector[i] = 1;
            else
                Vec.vector[i] = 0;
        }
        Vec.vector[len] = '\0'; 
    }
    else
        cout << "Error";
    return Vec;
}

BoolV BoolV::operator&(const BoolV& vec)
{
    BoolV Vec;
    if(len == vec.len)
    {
        Vec.len = len;
        Vec.vector = new unsigned char[Vec.len+ 1];
        for(int i = 0; i < len; i++)
        {
            if(vec[i] == 1 && vector[i] == 1)
                Vec.vector[i] = 1;
            else
                Vec.vector[i] = 0;
        }
        Vec.vector[len] = '\0';
    }
    else
        cout << "Error different length";
    return Vec;
}

BoolV& BoolV::operator&=(const BoolV& vec) 
{
    if (len == vec.len) 
    {
        for (int i = 0; i < len; ++i) 
        {
            if (vec[i] == 1 && vector[i] == 1) 
                vector[i] = 1;
            else
                vector[i] = 0;
        }
    } 
    else 
        cout << "Error: different lengths";
    return *this;
}

 

BoolV BoolV::operator~() 
{
    BoolV local = *this;
    for (int i = 0; i < len; ++i) 
    {
        if(vector[i] == 1)
            local.Set0(i);
        else
            local.Set1(i);
    }
    return local;
}

ostream & operator <<(ostream& Cout, const BoolV& vec)
{
    for(int i=0; i <vec.len; Cout<<char(vec.vector[i]+48), i++);
    return Cout;
}

istream & operator >>(istream& Cin, BoolV& vec)
{
    char temp[50];
    Cin.get(temp, 50);
    if (Cin)
    {
        vec = BoolV(temp);
    }    
    return Cin;
}

class BoolMat
{
public:
    BoolV *vectors;
    int colums, rows; // m – количество строк, n – количество столбцов
public:
    BoolMat(int col, int row); // формируется нулевая булева матрица размера k*l
    BoolMat(BoolMat&);
    BoolMat();

    BoolV& operator[] (int);
    BoolMat& operator = (const BoolMat &);
    BoolV disjunctionAll();
    friend ostream & operator << (ostream &, BoolMat &);
};

BoolMat::BoolMat(int col, int row)
{
    colums = col;
    rows = row;
    vectors = new BoolV[row];
    for(int i = 0; i < row; i++)
        vectors[i] = BoolV(col);
}

BoolMat::BoolMat(BoolMat & Mat)
{
    colums = Mat.colums;
    rows = Mat.rows;
    vectors = new BoolV[rows];
    for(int i = 0; i < rows; i++)
        vectors[i] = BoolV(colums);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < colums; j++)
           Mat[i][j] == 1 ? vectors[i].Set1(j) : vectors[i].Set0(j);
}

BoolMat::BoolMat()
{
    vectors = nullptr;
    colums = 0;
    rows = 0;
}
BoolV& BoolMat::operator[] (int index)
{
    return vectors[index];
}

BoolMat& BoolMat::operator=(const BoolMat& mat)
{
    if(this != &mat)
    {
            if(colums != mat.colums || rows != mat.rows)
            {
                if(vectors)
                    delete[] vectors;
                rows = mat.rows;
                colums = mat.colums;
                vectors =  new BoolV[rows];
            }
    
            for(int i = 0; i < rows; i++)
            {
                vectors[i] = mat.vectors[i];
            }
    } 
    
    return *this;
}

BoolV BoolMat::disjunctionAll()
{
    BoolV vec = vectors[0];
    for(int i = 1; i < rows; i++)
        vec = vec | vectors[i];
    return vec;
}

ostream & operator<< (ostream &Cout, BoolMat & Mat)
{
    for(int i = 0; i < Mat.rows; i++)
    {
        for(int j = 0; j < Mat.colums; j++)
            Cout << char(Mat[i][j]+48) << ' ';
        cout << endl;    
    }
    return Cout;        
}


/*int main()
{
    BoolV A("1010"), B("0100"), C;
    cout << (C = A | B);
    return 0;
}*/