#include <iostream>
using namespace std;

///////////////////////////////////////////////////////

template<class T>
class Array
{
    T *tab;
    int n;
public:
    Array();
    Array(const Array<T> &t);
    virtual ~Array();
    void dodaj(const T &t);
    bool usun(int i);
    void wypisz();
    Array<T> & operator=(const Array & x);
};

////////////////////////////////////////////////////////

template<class T>
Array<T>::Array()
{
    tab = NULL;
    n = 0;
}

/////////////////////////////////////////////////////////

template<class T>
Array<T>::Array(const Array & t)
{
    n = t.n;
    tab = new T [n];
    for(int i=0; i<n; i++)
        tab[i] = t.tab[i];
}

/////////////////////////////////////////////////////////

template<class T>
Array<T>::~Array()
{
    if(tab)
        delete [] tab; // jqk wskaznik to by byla petla
    tab = NULL;
}

//////////////////////////////////////////////////////////

template<class T>
void Array<T>::dodaj(const T &t)
{
    T *tmp = new T[n];
    for(int i = 0; i < n; ++i) tmp[i] = tab[i];
    if(tab) delete [] tab;
    tab = NULL;
    tab = new T[++n];
    for(int i = 0; i < (n - 1); ++i) tab[i] = tmp[i];
    tab[n - 1] = t;
}

//////////////////////////////////////////////////////////

template<class T>
bool Array<T>::usun(int i)
{
    if(i < 0 || i > n) return false;

    for(int j = i; j < (n - 1); ++j)
    {
        swap(tab[j], tab[j+1]);
    }

    T *tmp = new T[n-1];

    for(int j = 0; j < (n - 1); ++j)
    {
        tmp[j] = tab[j];
    }

    if(tab) delete [] tab;
    tab = new T[--n];
    for(int j = 0; j < n; ++j)
        tab[j] = tmp[j];

    return true;
}

///////////////////////////////////////////////////////////

template<class T>
void Array<T>::wypisz()
{
    for(int i = 0; i < n; ++i) cout << tab[i] << " ";
    cout << endl;
}

///////////////////////////////////////////////////////////

template<class T>
Array<T> & Array<T>::operator=(const Array & x)
{
    if(&x == this) return *this;
    if(n == x.n)
    {
        for(int i = 0; i < n; ++i) tab[i] = x.tab[i];
    }
    else
    {
        if(tab) delete [] tab;
        tab = NULL;
        n = x.n;
        tab = new T [n];
        for(int i = 0; i < n; ++i)
        {
            tab[i] = x.tab[i];
        }
    }
    return *this;
}

////////////////////////////////////////////////////////////

int main()
{
    Array<int> tab;
    tab.dodaj(10);
    tab.dodaj(20);
    tab.dodaj(30);
    tab.wypisz();
    tab.usun(2);
    tab.wypisz();
    tab.dodaj(40);
    tab.dodaj(50);
    tab.usun(0);
    tab.dodaj(60);
    tab.wypisz();
    Array<int> tab2;
    tab2 = tab;
    tab2.wypisz();
    return 0;
}
