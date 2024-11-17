#include<iostream>
#include<cassert>

class List;

class Node
{
    friend class List;
private:
    int value = 0;
    Node* prev = nullptr, * next = nullptr;
public:
    Node(int val = 0)
    {
        value = val;
    }
    friend std::ostream& operator << (std::ostream&, const List&);
    friend std::istream& operator >> (std::istream&, List&);
};

class List
{
private:
    int size = 0;
    Node* head = nullptr, * tail = nullptr;
public:
    List(int size = 0);
    List(int*, int);
    List(List&);
    ~List();
    bool isEmpty() const;
    int searchValue(int) const;
    int findMax() const;
    int findMin() const;
    List& clear();
    List& add(int);
    List& addByIndex(int, int);
    List& deleteByIndex(int);
    List& deleteOneElem(int);
    List& deleteAllElem(int);
    List operator +(const List&);
    List& operator +=(const List&);
    List& operator =(const List&);
    List& operator --(int);
    List& operator --();
    List& operator ++(int);
    List& operator ++();
    int& operator [](int);
    bool operator !=(const List&) const;
    bool operator ==(const List&) const;
    friend std::ostream& operator << (std::ostream&, const List&);
    friend std::istream& operator >> (std::istream&, List&);
};

List::List(int Size)
{
    if (Size > 0)
    {
        size = Size;
        head = new Node(0);

        Node* lefght = head, * right = nullptr;
        for (int i = 1; i < size; i++)
        {
            right = new Node(0);
            lefght->next = right;
            right->prev = lefght;
            lefght = right;
        }
        tail = lefght;
    }
}

List::List(int* arr, int lenght)
{
    if (lenght > 0 && arr != nullptr)
    {
        size = lenght;
        head = new Node(arr[0]);

        Node* lefght = head, * right = nullptr;
        for (int i = 1; i < size; i++)
        {
            right = new Node(arr[i]);
            lefght->next = right;
            right->prev = lefght;
            lefght = right;
        }
        tail = lefght;
    }

}

List::List(List& list)
{
    if (list.isEmpty())
        return;

    size = list.size;
    head = new Node(list.head->value);
    Node* lefght = head, * right = nullptr, * temp = list.head->next;
    while (temp != nullptr)
    {
        right = new Node(temp->value);
        lefght->next = right;
        right->prev = lefght;
        lefght = right;
        temp = temp->next;
    }
    tail = lefght;

}

List::~List()
{
    clear();
}

List& List::clear()
{
    if (!isEmpty())
    {
        while (size > 0)
        {
            if (head->next != nullptr && tail->prev != nullptr && head->next != tail)
            {
                head = head->next;
                tail = tail->prev;
                delete head->prev;
                delete tail->next;
                head->prev = nullptr;
                tail->next = nullptr;
                size = size - 2;
            }
            else if (head == tail)
            {
                delete head;
                head = nullptr;
                size--;
            }
            else
            {
                delete head;
                delete tail;
                head = nullptr;
                tail = nullptr;
                size = size - 2;
            }

        }
    }
    return *this;
}

bool List::isEmpty() const
{
    return size == 0;
}

int List::searchValue(int Value) const
{
    if (isEmpty())
        return -1;

    Node* tmp = head;
    for (int index = 0; index < size; tmp = tmp->next, index++)
        if (tmp->value == Value)
            return index;

    return -1;
}

int List::findMin() const
{
    if (isEmpty())
        return -1;

    int min = head->value;
    for (Node* tmp = head->next; tmp; tmp = tmp->next)
        if (tmp->value < min)
            min = tmp->value;

    return min;
}

int List::findMax() const
{
    if (isEmpty())
        return -1;

    int max = head->value;

    for (Node* tmp = head->next; tmp; tmp = tmp->next)
        if (tmp->value > max)
            max = tmp->value;

    return max;
}

List& List::add(int value)
{
    if (isEmpty())
    {
        head = new Node(0);
        size = 1;
        tail = head;
    }
    tail->next = new Node(0);
    tail->next->prev = tail;
    tail = tail->next;
    size++;
    return *this;
}


List& List::addByIndex(int index, int value)
{
    if (index < 0 || index > size || isEmpty())
        return *this;


    if (index == 0)
    {
        head->prev = new Node(value);
        head->prev->next = head;
        head = head->prev;
        size++;
    }
    else if (index == size)
    {

        tail->next = new Node(value);
        tail->next->prev = tail;
        tail = tail->next;
        size++;
    }
    else
    {
        Node* tmp = head->next;
        for (int i = 1; i < size; i++)
        {
            if (i == index)
            {
                tmp->prev->next = new Node(value);
                tmp->prev->next->next = tmp;
                tmp->prev->next->prev = tmp->prev;
                tmp->prev = tmp->prev->next;
                size++;
                return *this;
            }
            tmp = tmp->next;
        }
    }
    return *this;
}

List& List::deleteByIndex(int index)
{
    if (index < 0 || index >= size || isEmpty())
        return *this;

    if (index == 0)
    {
        head = head->next;
        head->prev = nullptr;
        size--;
        delete head->prev;
    }
    else if (index == size - 1)
    {
        tail = tail->prev;
        tail->next = nullptr;
        size--;
        delete tail->next;
    }
    else
    {
        Node* tmp = head->next;
        for (int i = 1; i < size; i++, tmp = tmp->next)
        {
            if (i == index)
            {
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                size--;
                delete tmp;
                return *this;
            }
        }
    }
    return *this;
}

List& List::deleteOneElem(int Value)
{
    if (isEmpty())
        return *this;

    if (Value == head->value)
    {
        head = head->next;
        head->prev = nullptr;
        size--;
        delete head->prev;
    }
    else if (Value == tail->value)
    {
        tail = tail->prev;
        tail->next = nullptr;
        size--;
        delete tail->next;
    }
    else
    {
        Node* tmp = head->next;
        for (int index = 1; index < size; tmp = tmp->next, index++)
            if (tmp->value == Value)
            {
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                size--;
                delete tmp;
                return *this;
            }
    }

    return *this;
}

List& List::deleteAllElem(int Value)
{
    if (isEmpty())
        return *this;

    while (Value == head->value)
    {
        head = head->next;
        head->prev = nullptr;
        size--;
        delete head->prev;
    }

    while (Value == tail->value)
    {
        tail = tail->prev;
        tail->next = nullptr;
        size--;
        delete tail->next;
    }

    Node* tmp = head->next;
    for (int index = 1; index < size; tmp = tmp->next, index++)
    {
        if (tmp->value == Value)
        {
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            size--;
            delete tmp;
        }
    }
    return *this;
}

List List::operator+(const List& list)
{
    List tmp(size + list.size);
    Node* TmpBufHead = tmp.head, * thisTemp = head;

    for (; thisTemp != nullptr; TmpBufHead = TmpBufHead->next, thisTemp = thisTemp->next)
        TmpBufHead->value = thisTemp->value;

    for (thisTemp = list.head; thisTemp != nullptr && TmpBufHead != nullptr; thisTemp = thisTemp->next, TmpBufHead = TmpBufHead->next)
        TmpBufHead->value = thisTemp->value;
    return tmp;
}

List& List::operator+=(const List& list)
{
    *this = *this + list;
    return *this;
}

List& List::operator--(int)
{
    deleteByIndex(size - 1);
    return *this;
}

List& List::operator--()
{
    deleteByIndex(0);
    return *this;
}

List& List::operator++(int)
{
    add(0);
    return *this;
}

List& List::operator++()
{
    addByIndex(0, 0);
    return *this;
}

List& List::operator=(const List& list)
{
    if (size != list.size)
    {
        while (size < list.size)
            (*this)++;

        while (size > list.size)
            (*this)--;
    }

    for (Node* tmp = head, *buf = list.head; tmp != nullptr; tmp = tmp->next, buf = buf->next)
        tmp->value = buf->value;

    return *this;
}

int& List::operator[](int index)
{
    assert(index > 0 && index < size);

    Node* tmp = head;
    for (int ind = 0; ind < size; tmp = tmp->next, ind++)
        if (ind == index)
            return tmp->value;

    return head->value;

}

bool List::operator!=(const List& list) const
{
    return !(*this == list);
}

bool List::operator==(const List& list) const
{
    if (size == list.size)
    {
        for (Node* tmp = head, *buf = list.head; tmp->next != nullptr; tmp = tmp->next, buf = buf->next)
            if (tmp->value != buf->value)
                return false;

        return true;
    }
    return false;
}

std::ostream& operator <<(std::ostream& Cout, const List& list)
{
    for (Node* node = list.head; node != nullptr; node = node->next)
        Cout << node->value << " ";

    return Cout;
}

std::istream& operator>>(std::istream& Cin, List& list)
{
    int length;
    Cin >> length;
    if (length < 0)
        return Cin;

    int* arr = new int[length];

    for (int i = 0; i < length; i++)
        Cin >> arr[i];

    List tmp(arr, length);
    list = tmp;
    delete[] arr;
    return Cin;
}

int main()
{
    using namespace std;
    int* arr{ new int[2] { 1, 4} };
    int* Frr{ new int[2] { 5, 9} };
    List B(Frr, 2);
    List A(arr, 2);
    cout << (A + B);
}