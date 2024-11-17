#include<iostream>
#include<ctime>

using namespace std;

class Route 
{
private:
    int *city, n;

public:
    Route(int num = 0); // создает начальную перестановку по возрастанию
    Route(Route&); // конструктор копирования
    Route & operator = (Route&); // операция присваивания
    ~Route();
    int routePrice(int **); // вычисляет стоимость маршрута по матрице стоимости
    bool nextRoute(); // вычисляет следующий маршрут, используя алгоритм Дейкстры
    friend ostream & operator << (ostream&, const Route&); // вывод маршрута
};

Route::Route(int num)
{
    n = num;
    city = new int[n];
    for(int i = 0; i < n; i++)
        city[i] = i;
}

Route::Route(Route& City)
{
    n = City.n;
    city = new int[n];
    for(int i = 0; i < n; i++)
    {
        city[i] = City.city[i];
    }
}

Route::~Route()
{
    if(city)
        delete[] city;
}
Route& Route::operator=(Route& City)
{
    if(this != &City)
    {
        if(n != City.n)
        {
            if(city)
                delete [] city;
            n = City.n;
            city = new int[n];    
        }
        for(int i = 0; i < n; i++)
        {
            city[i] = City.city[i];
        }
    }
    return *this;
}

bool Route::nextRoute()
{
    int i = n - 2, j = n - 1, start = city[0];
    
    while (city[i] > city[i + 1] && i >= 0)
        i--;
    
    if (i == -1) 
        return false;
    
    while (city[i] > city[j] && j > i)
        j--;

    int tmp = city[i];
    city[i] = city[j];
    city[j] = tmp;

    int start_sort = i + 1;
    int end_sort = n - 1;
    while (start_sort < end_sort) 
    {
        int buf = city[start_sort];
        city[start_sort] = city[end_sort];
        city[end_sort] = buf;
        start_sort++;
        end_sort--;
    }
    return (city[0] == start);
}

void print_matrix(int **ma, int size)
{
    cout<<"   " << "| ";
    for(int i=0; i<size; cout<<i+1<<"   ", i++);
        cout << endl;
    for(int i=0; i<size; cout<<"-----", i++);
    for(int i=0; i<size; i++)
    {
        cout<<endl<<i+1<< "  " << "| ";
        for(int j=0; j<size; j++) 
        {
            cout << ma[i][j] << "   ";
        }
    }
}

int Route::routePrice(int **costMatrix)
{
    int price = 0;
    for (int i = 0; i < n - 1; i++) 
    {
        price = price + costMatrix[city[i]][city[i + 1]];
    }
    price = price + costMatrix[city[n - 1]][city[0]]; 
    return price;
}
ostream & operator << (ostream& Cin, const Route& City)
{
    for(int i = 0; i < City.n; i++)
    {
        cout << City.city[i] << " ";
    }
    return Cin;
}

int main()
{

    srand(time(NULL));
    cout << "Enter size of matrix: ";
    int N = 0, path = 0;
    cin >> N;
    Route A(N);

    int **matrix = new int *[N];
    for (int i = 0; i < N; ++i) 
    {
        matrix[i] = new int[N];
        for (int j = 0; j < N; j++) 
            matrix[i][j] = rand() % 9 + 1;
    }

    for(int i=0; i<N; matrix[i][i] = 0, i++);

    print_matrix(matrix, N);
    cout << endl << endl;
    int minPath = A.routePrice(matrix);  
    Route b = A;
    do{
        path = A.routePrice(matrix);
        cout<< A <<" --- "<< path<<endl;
        if(minPath > path)
        {
            minPath = path;
            b = A;
        }

    }while(A.nextRoute());

    cout<< "Advantageous path: " << endl << b << " --- " << minPath << endl;

    for (int i = 0; i < N; ++i) 
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}    