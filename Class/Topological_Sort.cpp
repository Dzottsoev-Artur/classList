#include "D:\VS\Vs_Second_course\Class\classBoolV.cpp"
#include <fstream>
#include <ctime>

using namespace std;

void input(BoolMat& graph, int& tops)
{
    ifstream file("graf.txt");
    file >> tops;
    graph = BoolMat(tops, tops);
    int a = 0, b = 0;
    do{
        file >> a >> b;
        if(a || b)
            graph[a - 1].Set1(b - 1);    
    } while (a != 0 || b != 0); 
    cout << "Original matrix " << endl <<graph << endl; 
    file.close();  
}

int* sort(BoolMat graph, int tops)
{
    int* arr = new int[tops], j = 0;
    BoolV v0(tops), v1(tops), v2(tops);
    do
    {
        v1 = ~graph.disjunctionAll();
        v2 = v1 & (~v0);
    
        for(int i  = 0; i < tops && j < tops; i++)
            if(v2[i])
            {
                arr[j++] = i + 1;
                for(int k = 0; k<tops; graph[i].Set0(k), k++);
                for(int k = 0; k<tops; graph[k].Set0(i), k++);
            }
        v0 = v0 | v2;
    }while(v2.weight() > 0);

    if(v0.weight() !=tops)
    {
        cout << "Error cycle" << endl;
        for(int i = 0; i < tops; i++ )
            arr[i] = 0;
    }

    return arr;
}

void test()
{
	int* arr = nullptr;
	int tops = 0;
	BoolMat graph;
	input(graph, tops);
	arr = sort(graph, tops);
		for (int i = 0; i < tops; ++i)
			cout << arr[i] << ' ';
	delete[] arr;
}

int main()
{
    test();
    return 0;
}
