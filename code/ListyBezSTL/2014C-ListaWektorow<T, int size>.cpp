/*[20]Bez STL. Napisz szablon kontenera parametryzowanego typem T oraz parametrem int n, ktory przechowuje grupe
 * n-elementowych wektorow elementow typu T(np. bedzie to lista punktow w przestrzeni T^n). Wektory moga byc
 * reprezentowane przez tablice lub odpowiednio zadeklarowane klasy elementow. Napisz:
 * (a) deklaracje i konstruktor
 * (b) void dodaj (const T* tab) - dodaje jako element kontenera tablice T zawierajaca domyslnie n elementow
 * (c) konstruktor kopiujacy
 * (d) operator przypisania
 *
 * [20]Napisz szablon iteratora dla listy z zadania poprzedniego:
 * (a) deklaracja i konstruktor
 * (b) T*get() - zwraca biezacy element (wektor reprezentowany jest przez wskaznik)
 * (c) operator++ - przesuwa iterator
 * (d) bool operator() - zwraca true, jesli mozliwy odczyt elementu*/

#include <iostream>
using namespace std;

template <class T, int n> class Iterator;

template <class T, int n>
class VList
{
public:
    friend class Iterator<T, n>;
    class Vector
    {
    public:
        const T*tab = new T[n];
        Vector*next;
    };
    Vector*start;
    Vector*end;

    VList(){start = end = 0;}
    VList(const VList<T, n>& other){copy(other);}
    void dodaj(const T* tab)
    {
        Vector*v = new Vector();
        v->next = 0;
        v->tab = tab;
        if(end) end->next = v;
        end = v;
        if(!start) start = end;
    }
    VList<T, n>& operator= (const VList<T, n>& other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    };
protected:
    void copy(const VList<T, n>& other)
    {
        start = end = 0;
        for(Vector*i = other.start; i; i = i->next)
            dodaj(i->tab);
    }
    void free()
    {
        while(start)
        {
            Vector*tmp = start;
            start = start->next;
            delete[] tmp->tab;
            delete tmp;
        }
        start = end = 0;
    }

};


template <class T, int n>
class Iterator
{
public:
    const VList<T, n>& list;
    typename VList<T, n>::Vector*current;

    Iterator(const VList<T, n>& l): list(l), current(l.start){}
    Iterator& operator++() //prefiksowa
    {
        if(current) current = current->next;
        return *this;
    }
    Iterator operator++(int) //postfiksowa
    {
        Iterator temp = *this;
        ++*this;
        return temp;
    }
    operator bool()const
    {
        return current != 0;
    }
    T* get()const
    {
        return (T *) current->tab;
    }
};


int main()
{
    int *t = new int[4];
    for(int i = 0; i < 4; i++) t[i] = i + 1;
    int *t1 = new int[4];
    for(int i = 0; i < 4; i++) t1[i] = i + 2;
    int *t2 = new int[4];
    for(int i = 0; i < 4; i++) t2[i] = i + 3;

    int *t3 = new int[4];
    for(int i = 0; i < 4; i++) t3[i] = i + 5;
    int *t4 = new int[4];
    for(int i = 0; i < 4; i++) t4[i] = i + 6;

    VList<int, 4> lista1;
    lista1.dodaj(t);
    lista1.dodaj(t1);
    lista1.dodaj(t2);
    lista1.dodaj(t);

    for(Iterator<int, 4> it(lista1); it; it++)
    {
        cout << *it.get() << endl;
    } cout << endl;

    VList<int, 4> lista2;
    lista2.dodaj(t3);
    lista2.dodaj(t4);

    for(Iterator<int, 4> it(lista2); it; it++)
    {
        cout << *it.get() << endl;
    } cout << endl;

    VList<int, 4> lista3(lista2);

    for(Iterator<int, 4> it(lista3); it; it++)
    {
        cout << *it.get() << endl;
    } cout << endl;

    lista1 = lista2; //r.i.p

    for(Iterator<int, 4> it(lista1); it; it++)
    {
        cout << *it.get() << endl;
    } cout << endl;

    return 0;
}



