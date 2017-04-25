/*[25] Zadeklaruj i zaimplementuj szablon klasy Array<T> zarzadzajacej tablica elementow T o zmiennym dynamicznie
 * rozmiarze.

Zaimplementuj metody:
(a) konstruktor
(b) destruktor
(c) bool add(const T&) - dodawanie elementu na koncu tablicy
(d) konstruktor kopiujacy
(e) operator przypisania
(*) dodatkowo bool del(int i) - usuwa element na danej pozycji; void show();

[25] Zadeklaruj i zaimplementuj szablon klasy ArrayIterator<T> (iterator dla klasy z poprzedniego zadania) z metodami:
(a) konstruktorem
(b) atEnd() - czy iterator osiagnal koniec kontenera
(c) next() - przesuwa iterator na nastepny element
(d) int get() - zwraca aktualny element
(e) podaj przyklad wywolania
 */

#include <iostream>

using namespace std;

template<class T> class ArrayIterator;

template<class T>
class Array
{
    T*tab;
    int aSize;
public:
    friend class ArrayIterator<T>;

    Array():tab(0), aSize(0){}
    ~Array(){free();}
    Array(const Array&other){copy(other);}
    Array&operator=(const Array&other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    }
    bool add(const T& el)
    {
        T*tmp = new T[aSize];
        for(int i = 0; i < aSize; i++) tmp[i] = tab[i];
        if(tab) delete []tab;
        tab = 0;
        tab = new T[++aSize];
        for(int j = 0; j < aSize - 1; j++) tab[j] = tmp[j];
        tab[aSize - 1] = el;
        return true;
    }
    //dodatkowo
    bool del(int i)
    {
        if(i < 0 || i > aSize)
            return false;

        for(int j = i; j < (aSize - 1); ++j) swap(tab[j], tab[j+1]);
        T *tmp = new T[aSize-1];
        for(int j = 0; j < (aSize - 1); ++j) tmp[j] = tab[j];
        if(tab) delete [] tab;
        tab = new T[--aSize];
        for(int j = 0; j < aSize; ++j) tab[j] = tmp[j];
        return true;
    }
    void show()
    {
        for(int i = 0; i < aSize; i++) cout << tab[i] << " ";
        cout << endl;
    }

    virtual void copy(const Array&other)
    {
        aSize = 0;
        if(other.aSize != 0)
        {
            T*tab = new T[other.aSize];
            aSize = other.aSize;
            for(int i = 0; i < other.aSize; i++)
                tab[i] = other.tab[i];
        }
    }
    virtual void free()
    {
        if(tab) delete []tab;
        tab = 0; aSize = 0;
    }
};

template<class T>
class ArrayIterator
{
    const Array<T>&arr;
    T*current;
public:
    ArrayIterator(const Array<T>&a): arr(a), current(a.tab){}
    operator bool() { return *current < arr.aSize;}
    bool atEnd()
    {
        return *current == arr.tab[arr.aSize];
    }
    void next()
    {
        current++;
    }
    T& get()
    {
        return *current;
    }
};

int main()
{
    Array<int> tablica;
    tablica.add(3);
    tablica.add(7);
    tablica.add(12);
    tablica.add(4);
    tablica.add(9);
    tablica.show();
    tablica.del(2);
    tablica.show();
    Array<string> tablica2;
    tablica2.add("ala");
    tablica2.add("ma");
    tablica2.add("kota");
    tablica2.show();
    Array<int> tablica1;
    tablica1.add(13);
    tablica1.show();
    tablica1 = tablica;
    tablica1.show();
    cout << "-----------------" << endl;

    ArrayIterator<int> it(tablica);

    cout << it.get() << endl;
    it.next();
    cout << it.get() << endl << endl;

    for(ArrayIterator<int> it1(tablica1); !(it1.atEnd()); it1.next())
        cout << it1.get() << " " << endl;

    return 0;
}

