/*[25]Uzyj STL. Klasa Miasto ma trzy atrybuty: nazwa(string) oraz double x, y (wspolrzedne geograficzne). Zaimplementuj
 * klase ZbiorMiast, przechowujaca unikalne instancje obiektow klasy Miasto. Napisz:
 * (a) deklaracje (Miasto i ZbiorMiast), ew. konstruktor i destruktor
 * (b) bool dodaj(const Miasto &m) - dodaje miasto do zbioru, jesli jednak miasto o takiej nazwie istnieje, to zmienia
 *     wspolrzedne geograficzne x i y
 * (c) Miasto* znajdz(const char* name) - zwraca miasto o danej nazwie lub null, jesli takiego brak
 * (d) void dodaj(const ZbiorMiast &z) - dodaje do zbioru miasta nalezace do z
 * (e) void usunSpoza(const ZbiorMiast &z) - usuwa ze zbioru wszystke miasta nie nalezace do z(sprawdzajac nazwy)*/

#include <iostream>
#include <list>
using namespace std;

class Miasto
{
public:
    string nazwa;
    double x, y;
    Miasto(){nazwa = " "; x = y = 0;}
    Miasto(string n, double _x, double _y): nazwa(n), x(_x), y(_y){}
    friend ostream& operator<<(ostream& strumyk, const Miasto& m)
    {
        strumyk << m.nazwa << ", wspolrzedne: " << m.x << ", " << m.y << endl;
        return strumyk;
    }
};

class ZbiorMiast
{
public:
    list<Miasto> zbior;

    ZbiorMiast(){}
    ~ZbiorMiast();
    bool has(const char* name)const;
    bool dodaj(const Miasto &m);
    Miasto* znajdz(const char* name);
    void dodaj(const ZbiorMiast &z);
    void usunSpoza(const ZbiorMiast &z);
    void wypisz();
};

bool ZbiorMiast::has(const char *name) const
{
    list<Miasto>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(it->nazwa == name) return true;
    }
    return false;
}

ZbiorMiast::~ZbiorMiast()
{
    list<Miasto>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
        zbior.erase(it);
}

bool ZbiorMiast::dodaj(const Miasto &m)
{
    list<Miasto>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(it->nazwa == m.nazwa)
        {
            it->x = m.x;
            it->y = m.y;
            return true;
        }
    }
    zbior.push_back(m);
    return true;
}

Miasto* ZbiorMiast::znajdz(const char *name)
{
    list<Miasto>::iterator it;
    Miasto m1;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(it->nazwa == name)
        {
            return &(*it);
        }
    }
    return nullptr;
}

void ZbiorMiast::dodaj(const ZbiorMiast &z)
{
    list<Miasto>::const_iterator it;
    for(it = z.zbior.begin(); it != z.zbior.end(); it++)
    {
        dodaj(*it);
    }
}

void ZbiorMiast::usunSpoza(const ZbiorMiast &z)
{
    list<Miasto>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(!(z.has(it->nazwa.c_str()))) zbior.erase(it);
    }
}

void ZbiorMiast::wypisz()
{
    list<Miasto>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        cout << *it;
    }
}


int main()
{
    Miasto m1("Krakow", 12, 17);
    Miasto m2("Warszawa", 14, 35);
    Miasto m3("Gdansk", 20, 44);
    Miasto m4("Lublin", 25, 23);
    Miasto m5("Jaroslaw", 28, 12);
    Miasto m6("Mielec", 24, 14);
    Miasto m7("Gdansk", 22, 43);

    ZbiorMiast zbior1;
    zbior1.dodaj(m1);
    zbior1.dodaj(m2);
    zbior1.dodaj(m3);
    zbior1.dodaj(m4);
    zbior1.dodaj(m7);
    zbior1.wypisz();

    cout << endl << *(zbior1.znajdz("Krakow")) << endl;

    ZbiorMiast zbior2;
    zbior2.dodaj(m2);
    zbior2.dodaj(m3);
    zbior2.dodaj(m5);
    zbior2.dodaj(m6);
    zbior2.wypisz();

    zbior1.usunSpoza(zbior2);
    cout << endl; zbior1.wypisz();

    zbior1.dodaj(zbior2);
    cout << endl; zbior1.wypisz();

    return 0;
}