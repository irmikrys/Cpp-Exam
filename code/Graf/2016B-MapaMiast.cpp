/*[25] Napisz klase Mapa przechowujaca informacje o miastach i drogach pomiedzy miastami. Do zrealizowania:
 * (a) zadeklaruj klase Mapa i, jesli to bedzie przydatne, dodatkowe struktury danych
 * (b) int dodajMiasto(const char* nazwa, double x, double y) - dodaje Miasto i zwraca jego calkowitoliczbowy
 *     identyfikator (numer). Zmienne x i y to wspolrzedne kartezjanskie srodka miasta
 * (c) bool dodajDroge(int m1, int m2, double dl) - dodaje droge o dlugosci dl pomiedzy miastami m1 i m2. Zwraca false,
 *     jesli takich miast nie ma
 * (d) void sasiedzi(int m, list<int>&sa) - umieszcza w sa wszystkie miasta sasiadujace z miastem m (polaczone droga)
 * (e) double odleglosc(int m1, int m2) - zwraca odleglosc pomiedzy miastami m1 i m2 (euklidesowska, nie drogowa)*/

#include <iostream>
#include <list>
#include <cmath>
using namespace std;

class Mapa
{
public:
    struct Miasto
    {
        const char* nazwa;
        double x, y;
        int numer;
        Miasto(const char* n, double _x, double _y, int nr):nazwa(n), x(_x), y(_y), numer(nr){}
        friend ostream& operator<<(ostream& ostream1, const Miasto& m)
        {
            ostream1 << m.nazwa << ", wspolrzedne: " << m.x << ", " << m.y << ", nr: " << m.numer << endl;
            return ostream1;
        }
    };

    struct Droga
    {
        int m1;
        int m2;
        double dl;
        Droga(int _m1, int _m2, double _dl): m1(_m1), m2(_m2), dl(_dl){}
        friend ostream& operator<<(ostream& ostream1, const Droga& d)
        {
            ostream1 << d.m1 << "---" << d.m2 << ", dlugosc: " << d.dl <<endl;
            return ostream1;
        }
    };

    list<Miasto> miasta;
    list<Droga> drogi;

    int ileMiast;

    Mapa() {ileMiast = 0;}
    bool has(int m)const {
        list<Miasto>::const_iterator it;
        for(it = miasta.begin(); it != miasta.end(); it++)
        {
            if(it->numer == m) return true;
        }
        return false;
    }
    bool jestDroga(int m1, int m2)const {
        for(list<Droga>::const_iterator it = drogi.begin(); it != drogi.end(); it++)
        {
            if((it->m1 == m1 && it->m2 == m2) || (it->m1 == m2 && it->m2 == m1)) return true;
        }
        return false;
    }
    int dodajMiasto(const char* nazwa, double x, double y);
    bool dodajDroge(int m1, int m2, double dl);
    void sasiedzi(int m, list<int>&sa);
    double odleglosc(int m1, int m2);

    friend ostream& operator<<(ostream& ostream1, const Mapa& m)
    {
        for(list<Miasto>::const_iterator it = m.miasta.begin(); it != m.miasta.end(); it++)
            ostream1 << *it << " ";
        ostream1 << endl;
        for(list<Droga>::const_iterator it = m.drogi.begin(); it != m.drogi.end(); it++)
            ostream1 << *it;
        ostream1 << endl;
        return ostream1;
    }
};

int Mapa::dodajMiasto(const char *nazwa, double x, double y)
{
    Miasto m1(nazwa, x, y, ileMiast);
    miasta.push_back(m1);
    ileMiast++;
    return m1.numer;
}

bool Mapa::dodajDroge(int m1, int m2, double dl)
{
    if(!(has(m1) && has(m2)) || jestDroga(m1, m2)) return false;
    Droga d1(m1, m2, dl);
    drogi.push_back(d1);
    return true;
}

void Mapa::sasiedzi(int m, list<int> &sa)
{
    for(list<Miasto>::iterator it = miasta.begin(); it != miasta.end(); it++)
    {
        if(jestDroga(m, it->numer)) sa.push_back(it->numer);
    }
}

double Mapa::odleglosc(int m1, int m2)
{
    if(!has(m1) || !has(m2)) return 1;

    list<Miasto>::iterator it, it1 = miasta.end(), it2 = miasta.end();
    for(it = miasta.begin(); it != miasta.end(); it++)
    {
        if(it->numer == m1) it1 = it;
        if(it->numer == m2) it2 = it;
        if(it1 != miasta.end() && it2 != miasta.end()) break;
    }
    double dist = 0;
    dist = sqrt(((it1->x - it2->x)*(it1->x - it2->x))+((it1->y - it2->y)*(it1->y - it2->y)));
    return dist;
}

int main()
{
    Mapa mapa;
    mapa.dodajMiasto("Krakow", 22, 78);
    mapa.dodajMiasto("Wawa", 24, 93);
    mapa.dodajMiasto("Poznan", 19, 87);
    mapa.dodajMiasto("Krzeszo", 20, 80);
    mapa.dodajMiasto("Kielce", 16, 65);

    mapa.dodajDroge(2, 3, 250);
    mapa.dodajDroge(0, 3, 27);
    mapa.dodajDroge(1, 2, 170);
    mapa.dodajDroge(3, 4, 80);
    mapa.dodajDroge(0, 5, 213);

    cout << mapa;

    list<int> sasiedzi;
    mapa.sasiedzi(3, sasiedzi);
    for(list<int>::const_iterator it = sasiedzi.begin(); it != sasiedzi.end(); it++) cout << *it << " "; cout << endl;

    cout << mapa.odleglosc(2, 4) << endl;

    return 0;
}



