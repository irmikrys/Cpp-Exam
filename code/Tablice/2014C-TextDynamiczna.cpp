/*[25]Bez STL. Klasa Text jest tablica znakow o zmiennym dynamicznie rozmiarze(pamiec jest przydzielana na stercie).
 * Napisz:
 * (a) konstruktor i deklaracje
 * (b) destruktor
 * (c) operator + - laczy dwa teksty
 * (d) konstruktor kopiujacy
 * (e) operator przypisania*/

#include <iostream>
using namespace std;

class Text
{
public:
    char*tab;
    int size;

    Text(int n);
    Text(const Text& other);
    ~Text();
    friend Text operator + (const Text& t1, const Text& t2);
    Text& operator = (const Text& other);
    friend ostream& operator << (ostream& strumyk, const Text& t);
protected:
    void copy(const Text& other);
    void free();
};

Text::Text(int n)
{
    tab = new char[n];
    size = n;
}

Text::Text(const Text &other)
{
    copy(other);
}

Text::~Text()
{
    free();
}

Text operator+(const Text &t1, const Text &t2)
{
    Text txt(t1.size + t2.size);
    for(int i = 0; i < t1.size; i++) txt.tab[i] = t1.tab[i];
    for(int i = t1.size; i < txt.size; i++) txt.tab[i] = t2.tab[i - t1.size];
    return txt;
}

Text &Text::operator=(const Text &other)
{
    if(&other != this)
    {
        free();
        copy(other);
    }
    return *this;
}

void Text::copy(const Text& other)
{
    size = other.size;
    tab = new char[size];
    for(int i = 0; i < size; i++)
        tab[i] = other.tab[i];
}

void Text::free()
{
    if(tab) delete []tab;
    tab = 0;
    size = 0;
}

ostream &operator<<(ostream &strumyk, const Text &t)
{
    for(int i = 0; i < t.size; i++)
        strumyk << t.tab[i];
    strumyk << endl;
    return strumyk;
}


int main()
{
    Text t1(2);
    Text t2(4);

    t1.tab[0] = 'k'; t1.tab[1] = 'a';
    t2.tab[0] = 'c'; t2.tab[1] = 'p'; t2.tab[2] = 'e'; t2.tab[3] = 'r';

    cout << t1;
    cout << t2;

    Text t3(t1);
    cout << t3;

    t3 = t2;
    cout << t3;

    Text t5 = t1 + t2;
    cout << t5;

    t5 = t2;
    cout << t5;

    return 0;
}

