/*Bez STL! Napisz wektor o przyrastajacej dlugosci przechowujacy wskazniki typu A* do obiektow klasy A, dla ktorych
 * pamiec jest przydzielona na stercie.
 * (a) konstruktor - parametrem jest wstepny rozmiar + deklaracje
 * (b) destruktor
 * (c) bool pushBack(const A& a) - dodaje element do kontenera alokujac dla niego pamiec
 * (d) konstruktor kopiujacy
 * (e) operator przypisania*/

#include <iostream>
using namespace std;

class A
{
public:
    A(){}
    virtual ~A(){}
    virtual A* clone()
    {
        return new A(*this);
    }
};

class Vector
{
public:
    A* *tab;
    int size; //ile jest elementow
    int capacity; //ile jest miejsc na elementy

    Vector(int n);
    Vector(const Vector& other);
    ~Vector();
    bool pushBack(const A& a);
    Vector&operator = (const Vector& other);

    friend ostream& operator <<(ostream& os, const Vector& v)
    {
        os << "size: " << v.size << endl;
        os << "#begin" << endl;
        for(int i = 0; i < v.size; i++)
        {
            os << typeid(*v.tab[i]).name() << "-" << i << " ";
        }
        os << endl << "#end" << endl;
        return os;
    }
protected:
    bool reserve(int newCapacity)
    {
        if(newCapacity < capacity) return false;
        A* *tmp = new A * [newCapacity];
        if(capacity)
        {
            for(int i = 0; i < size; i++)
            {
                tmp[i] = new A(*tab[i]); //tab[i]->clone();
                delete tab[i];
            }
            delete[] tab;
        }
        tab = new A * [newCapacity];
        capacity = newCapacity;
        if(size)
        {
            for(int i = 0; i < size; i++)
            {
                tab[i] = tmp[i]->clone();
                delete tmp[i];
            }
            delete[] tmp;
        }
        return true;
    }
    void copy(const Vector& other)
    {
        size = other.size;
        capacity = other.capacity;
        tab = new A * [capacity];
        for(int i = 0; i < other.size; i++)
        {
            tab[i] = other.tab[i]->clone();
        }
    }
    void free()
    {
        for(int i = 0; i < size; i++)
            delete tab[i];
        delete[] tab;
        tab = nullptr;
        size = capacity = 0;
    }
};

Vector::Vector(int n)
{
    size = 0;
    capacity = n;
    tab = new A * [capacity];
}

Vector::Vector(const Vector &other)
{
    copy(other);
}

Vector::~Vector()
{
    free();
}

bool Vector::pushBack(const A &a)
{
    if (capacity == size && !reserve(capacity + 4))return false;
    tab[size] = new A();
    *tab[size] = a;
    size++;
    return true;
}

Vector &Vector::operator=(const Vector &other)
{
    if(&other != this)
    {
        free();
        copy(other);
    }
    return *this;
}

int main()
{
    A* a = new A();
    Vector v1(2);
    v1.pushBack(*a);
    v1.pushBack(*a);
    v1.pushBack(*a);
    cout << v1;

    Vector v2(4);
    v2.pushBack(*a);
    v2.pushBack(*a);
    v2.pushBack(*a);
    v2.pushBack(*a);
    v2.pushBack(*a);
    cout << v2;

    v2 = v1;
    cout << v2;

    return 0;
}
