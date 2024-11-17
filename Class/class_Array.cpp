#include<iostream>
#include<ctime>
#include<cassert>

using namespace std;

class Array
{
private: 
    int *array, length;
    void Hoar_sort(int left, int right);
    void Screening(int i, int high);
    void Build_heap();
    bool check() const;
public:
 // len – число элементов в массиве
 // t = 1 – неупорядоченный массив
 // t = 2 – массив, упорядоченный по неубыванию
 // t = 3 – массив, упорядоченный по невозрастанию
 // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10);
    Array(int* arr, int len);
    Array(Array& );
    ~Array();
    int &operator [](int);
    bool operator == (Array &);
    Array& operator=(Array &);
    Array& Reverse();
    Array& Shell_sort();
    Array& Insert_sort();
    Array& Heap_sort();
    Array& Quick_sort();
    bool Test_Quick_sort();
    bool Test_Shell_sort();
    bool Test_Heap_sort();
    bool Test_Insert_sort();
    friend istream & operator >> (istream &, Array &);
    friend ostream & operator << (ostream &, const Array &);
};


Array::Array(int len, int t, int d)
{
    length = len < 1 ? 0 : len;
    array = new int[length];
    switch (t)
    {
        case 1:
        {   
            srand(time(nullptr));
            array = new int[length];

            for(int i = 0; i < length; i++)
                array[i] = rand() % d + 1;

            break; 
        }
        case 2:
        {
            srand(time(nullptr));
            array = new int[length];

            for(int i = 0; i < length; i++)
                array[i] = rand() % (d + 1);


            Hoar_sort(0, length - 1);
            break;
        }
        case 3:
        {   
            srand(time(nullptr));
            array = new int[length];
            for(int i = 0; i < length; i++)
                array[i] = rand() % (d + 1);

            Hoar_sort(0, length - 1); 
            Reverse();
            break;
        }
        default:
        {
            length = 0;
            array = new int[length]; 
        }
    }
}

Array::Array(int* arr, int len)
{
    length = len;
    array = new int[length];

    for(int i = 0; i < length; i++)
        array[i] = arr[i]; 
}

Array::Array(Array& arr)
{
    length = arr.length;
    array = new int[length];

    for(int i = 0; i < length; i++)
        array[i] = arr.array[i];
}

Array::~Array()
{
    if(array) 
        delete[] array;
}

bool Array::check() const
{
    for (int i = 0; i < length - 1; i++)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

//Операторы
int& Array::operator []( int index)
{
    assert(index > 0 && index < length - 1);

    return array[index];
}

bool Array::operator==(Array& arr)
{
    if(length == arr.length)
    {
        Array Copy(*this);
        Copy.Insert_sort();
        Array Copyarr(arr);
        Copy.Insert_sort();
        for(int i = 0; i < length; i++)
            if(Copy[i] != Copyarr[i])
                return false;
        return true;    
        
    }
    
    return false;
}

Array& Array::operator=(Array& arr)
{
    if(this != &arr)
    {
        if(length != arr.length)
        {
            if (array != nullptr)
                delete []array;
            length = arr.length;
            array = new int[length];
        }
        for(int i = 0; i < length; i++)
            array[i] = arr.array[i];
    }
    
    return *this;
}   
//Сортировки
Array& Array::Reverse()
{
    for(int i = 0; i < length/2; i++)
    {
        int buf = array[i];
        array[i] = array[length - i - 1];
        array[length - i - 1] = buf;
    } 
    return *this; 
}

Array& Array::Shell_sort()
{
    int step = length / 2;

    while (step > 0) 
    {
        for (int i = step; i < length; ++i) 
        {
            int temp = array[i];
            int j = i;

            while (j >= step && array[j - step] > temp) 
            {
                array[j] = array[j - step];
                j -= step;
            }
            array[j] = temp;
        }
        step /= 2;
    }
    return *this;    
}
Array& Array::Insert_sort()
{
    for(int i = 1; i < length; i++)
    {
        int k = i;
        while(k > 0 && array[k - 1] > array [k])
        {
            int buf = array[k - 1];
            array[k -1] = array[k];
            array[k] = buf;
            k--;
        }
    }
    return *this;
}

void Array::Screening(int i, int high)
{
    int x = array[i];
    int j = 2 * i + 1;

    while (j < high)
    {
        if (j + 1 < high && array[j + 1] > array[j])
            ++j;

        if (array[j] <= x)
            break;

        array[i] = array[j];
        i = j;
        j = 2 * i + 1;
    }

    array[i] = x;
}

void Array::Build_heap()
{
    for(int i = length/2 - 1; i >= 0; --i)
        Screening(i, length);
}

Array& Array::Heap_sort()
{  
    (*this).Build_heap();
    for(int k = length - 1; k > 0; --k)
    {   
        int tmp = array[0];
        array[0] = array[k];
        array[k] = tmp;
        Screening(0, k);
    }
    return *this;
}


void Array::Hoar_sort(int left, int right)
{
    if(left >= right) 
        return ;
    int middle = array[(left + right) / 2];
    int i = left, j = right;
    while(i <= j)
    {
        while (array[i] < middle)
            i++;
        while (array[j] > middle)
            j--;
        if(i <= j)
        {
            int buf = array[i];
            array[i] = array[j];
            array[j] = buf;
            i++;
            j--;
        }
    }
    Hoar_sort(left, j);
    Hoar_sort(i, right);
}

Array& Array::Quick_sort()
{
    Hoar_sort(0, length - 1);
    return *this;
}

bool Array::Test_Insert_sort()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    (*this).Insert_sort();
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << time_spent << " ";
    return check();
}

bool Array::Test_Quick_sort()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    (*this).Quick_sort();
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << time_spent << " ";
    return check();
}

bool Array::Test_Shell_sort()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    Shell_sort();
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << time_spent << " ";
    return check();
}

bool Array::Test_Heap_sort()
{
    double time_spent = 0.0;
    clock_t begin = clock();
    Heap_sort();
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << time_spent << " ";
    return check();
}


ostream & operator << (ostream& Cout, const Array& arr)
{
    for(int i = 0; i < arr.length; i++)
        Cout << arr.array[i] << " ";

    return Cout;
}

istream & operator >>(istream& Cin, Array& arr)
{
    cout << "Enter lenght" << endl;
    Cin >> arr.length;
    delete [] arr.array;
    arr.length < 1 ? arr.array = new int[0] : arr.array = new int[arr.length];
    for(int i = 0; i < arr.length; i++)
        Cin >> arr.array[i];

    return Cin;
}

int main()
{
    Array B(5, 2, 10);
    Array A(5, 3, 10);
    cout << B << endl << B[-1];
}