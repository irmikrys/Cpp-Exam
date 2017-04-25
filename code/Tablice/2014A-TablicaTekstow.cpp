/*[25]Bez STL. Klasa TablicaTekstow przechowuje wskazniki do tekstow (tablic znakow), dla ktorych pamiec jest
 * przechowywana na stercie (klasa odpowiada za alokacje i zwalnianie pamieci). Napisz:
 * (a) konstruktor i deklaracje
 * (b) destruktor
 * (c) void dodaj(const char* t) - dodaje tekst na koncu, jesli trzeba poszerza tablice
 * (d) konstruktor kopiujacy
 * (e) operator przypisania */

#include <iostream>
#include <cstring>
using namespace std;

class TablicaTekstow
{
public:
    char* *tab;
    int size;

    TablicaTekstow();
    TablicaTekstow(int n);
    TablicaTekstow(const TablicaTekstow& other);
    ~TablicaTekstow();
    void dodaj(const char* t);
    TablicaTekstow& operator = (const TablicaTekstow& other);

    friend ostream& operator << (ostream& strumyk, const TablicaTekstow& t)
    {
        for(int i = 0; i < t.size; i++)
        {
            for (int j = 0; j < strlen(t.tab[i]); j++)
                strumyk << t.tab[i][j];
            strumyk << endl;
        }
        return strumyk;
    }
protected:
    void copy(const TablicaTekstow& other)
    {
        size = other.size;
        tab = new char * [size];
        for(int i = 0; i < size; i++)
        {
            tab[i] = new char[strlen(other.tab[i])];
        }
        for(int i = 0; i < size; i++)
            for(int j = 0; j < strlen(other.tab[i]); j++)
                tab[i][j] = other.tab[i][j];
    }
    void free()
    {
        if(tab)
        {
            for(int i = 0; i < size; i++)
                delete[] tab[i];
            delete[] tab;
        }
        size = 0;
        tab = 0;
    }

};

TablicaTekstow::TablicaTekstow()
{
    size = 0;
    tab = 0;
}

TablicaTekstow::TablicaTekstow(int n)
{
    size = n;
    tab = new char*[size];
}

TablicaTekstow::TablicaTekstow(const TablicaTekstow &other)
{
    copy(other);
}

TablicaTekstow::~TablicaTekstow()
{
    free();
}

void TablicaTekstow::dodaj(const char *t)
{
    if(size == 0)
    {
        size = 1;
        tab = new char * [size];
    }
    else
    {
        int tmp_size = size;
        char* * tmp = new char*[tmp_size];
        for(int i = 0; i < tmp_size; i++) tmp[i] = new char[strlen(tab[i])];

        for(int i = 0; i < tmp_size; i++) strcpy(tmp[i], tab[i]);
            //for(int j = 0; j < strlen(tab[i]); j++)
                //tmp[i][j] = tab[i][j];
        free();
        size = tmp_size + 1;
        tab = new char*[size];
        for(int i = 0; i < size; i++) tab[i] = new char[strlen(tmp[i])];

        for(int i = 0; i < tmp_size; i++) strcpy(tab[i], tmp[i]);
            //for(int j = 0; j < strlen(tab[i]); j++)
                //tab[i][j] = tmp[i][j];

    }
    tab[size - 1] = new char [strlen(t)];
    strcpy(tab[size - 1], t);
}

TablicaTekstow &TablicaTekstow::operator=(const TablicaTekstow &other)
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
    TablicaTekstow t1;
    t1.dodaj("mam");
    t1.dodaj("kotek");
    cout << t1;

    return 0;
}


