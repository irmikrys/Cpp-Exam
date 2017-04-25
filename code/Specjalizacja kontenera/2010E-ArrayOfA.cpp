/*[25] Klasy B, C i D dziedzicza po klasie class A{public: virtual ~A();}. Klasa ArrayOfA przechowuje w tablicy
 * wskazniki typu A* do obiektow klas A, B, C, D, dla ktorych pamiec przydzielona jest na strecie. Zaimplementuj klase
 * ArrayOfA:
 * (a) deklaracje i konstruktor, konstruktor ustala rozmiar tablicy
 * (b) destruktor
 * (c) operator przypisania
 * (d) konstruktor kopiujacy
 * (e) operator +
 * (*) bool dodaj(const A* a) - dodaje element na pierwszym wolnym miejscu
 * */

#include <iostream>
#include <typeinfo>
using namespace std;

class A
{
public:
    virtual ~A() {}
    virtual A* clone()const
    {
        return new A(*this);
    }
};

class B: public A
{
public:
    A* clone()const
    {
        return new B(*this);
    }
};

class C: public A
{
public:
    A* clone()const
    {
        return new C(*this);
    }
};

class D: public A
{
public:
    A* clone()const
    {
        return new D(*this);
    }
};

class ArrayOfA
{
public:
    A* *tab;
    int size;
    int zaj;

    ArrayOfA():zaj(0), size(0){}
    ArrayOfA(int n);
    ArrayOfA(const ArrayOfA& other);
    ~ArrayOfA();
    ArrayOfA&operator=(const ArrayOfA& other);
    friend ArrayOfA operator + (const ArrayOfA & a1, const ArrayOfA & a2);

    bool dodaj(const A* a)
    {
        if(zaj == size) return false;
        tab[zaj] = a->clone();
        zaj++;
        return true;
    }
    friend ostream&operator<<(ostream& strumyk, const ArrayOfA arr)
    {
        for(int i = 0; i < arr.size; i++)
        {
            if(arr.tab[i] == nullptr) strumyk << "nullptr ";
            else strumyk << typeid(*arr.tab[i]).name() << " ";
        }
        strumyk << endl;
        return strumyk;
    }
protected:
    void copy(const ArrayOfA& other)
    {
        zaj = other.zaj;
        size = other.size;
        tab = new A * [size];
        for(int i = 0; i < size; i++) tab[i] = nullptr;
        for(int i = 0; i < zaj; i++)
        {
            tab[i] = other.tab[i]->clone();
        }
    }
    void free()
    {
        if(tab)
        {
            for(int i = 0; i < size; i++)
            {
                delete tab[i];
            }
            delete [] tab;
        }
        tab = 0;
        size = 0;
        zaj = 0;
    }
};

ArrayOfA::ArrayOfA(int n)
{
    size = n;
    tab = new A * [size];
    for(int i = 0; i < size; i++) tab[i] = nullptr;
    zaj = 0;
}

ArrayOfA::ArrayOfA(const ArrayOfA &other)
{
    copy(other);
}

ArrayOfA::~ArrayOfA()
{
    free();
}

ArrayOfA &ArrayOfA::operator=(const ArrayOfA &other)
{
    if(&other != this)
    {
        free();
        copy(other);
    }
    return *this;
}

ArrayOfA operator+(const ArrayOfA &a1, const ArrayOfA &a2)
{
    ArrayOfA a_tmp(a1.size + a2.size);
    for(int i = 0; i < a1.zaj; i++) a_tmp.dodaj(a1.tab[i]->clone());
    for(int i = a1.zaj; i < a1.size; i++) {a_tmp.tab[i] = nullptr; a_tmp.zaj++;}
    for(int i = a1.size; i < a1.size + a2.zaj; i++) a_tmp.dodaj(a2.tab[i - a1.size]->clone());
    for(int i = a1.size + a2.zaj; i < a_tmp.size; i++) {a_tmp.tab[i] = nullptr; a_tmp.zaj++;}
    return a_tmp;
}

int main()
{
    ArrayOfA arr1(5);
    ArrayOfA arr2(7);

    A * a1 = new A();
    A * a2 = new B();
    A * a3 = new C();
    A * a4 = new D();

    arr1.dodaj(a3);
    arr1.dodaj(a1);
    arr1.dodaj(a4);
    arr1.dodaj(a2);
    arr1.dodaj(a1);
    cout << arr1;

    arr2.dodaj(a2);
    arr2.dodaj(a2);
    arr2.dodaj(a1);
    arr2.dodaj(a3);
    arr2.dodaj(a2);
    arr2.dodaj(a3);
    arr2.dodaj(a4);
    arr2.dodaj(a1);
    cout << arr2;

    ArrayOfA arr3(arr2);
    cout << arr3;

    arr2 = arr1;
    cout << arr2;

    ArrayOfA arr4 = arr3 + arr1; // nie dziala jak ktoras z tablic jest niepelna :<
    cout << arr4;


    return 0;
}
