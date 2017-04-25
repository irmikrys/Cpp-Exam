/*[20] Klasa Miejscowosc ma atrybuty: string nazwa, string region, double mieszk, double dlugGPS, double szerGPS.
 * Napisz klase LM(lista Miejscowosci). Zaloz, ze w klasie LM zdefiniowana jest statyczna funkcja
 * double dist(double d1, double s1, double d2, double s2)
 * obliczajaca odleglosc miedzy pomiedzy dwiema wspolrzednymi GPS (d1, s1) i (d2, s2)
 *
 * (a) zadeklaruj wymagane struktury danych
 * (b) bool dodaj(const Miejscowosc &m) - dodaje miejscowosc; zwraca false jesli dla tych samych wspolrzednych
 *     (z dokladnoscia do pewnej stalej epsilon) miejscowosc byla juz zdefiniowana
 * (c) Miejscowosc* szukaj(const char* name) - znajduje miejscowosc o danej nazwie (dopasowanie nie uwzgledniajace
 *     wielkosci liter)
 * (d) void szukaj(const char* txt, list<Miejscowosc> & result) - znajduje wszystkie miejscowosci, ktorych pole nazwa
 *     lub region zawiera lancuch txt
 * Uzyj dowolnego kontenera STL. */

#include <iostream>
#include <list>
#include <cmath>
#include <locale>

using namespace std;

static double epsilon = 1.5;

class Miejscowosc
{
public:
    string nazwa;
    string region;
    double mieszk;
    double dlugGPS, szerGPS;

    Miejscowosc(string n, string r, double m, double d, double s)
            :nazwa(n), region(r), mieszk(m), dlugGPS(d), szerGPS(s){}
    friend ostream& operator<<(ostream& strumyk, const Miejscowosc& m)
    {
        strumyk << m.nazwa << " " << m.region << " " << m.mieszk << ", wsp: " << m.dlugGPS << " " << m.szerGPS << endl;
        return strumyk;
    }
};

class LM
{
public:
    list<Miejscowosc> lm;

    static double dist(double d1, double s1, double d2, double s2)
    {
        double odleglosc = 0;
        odleglosc = sqrt((d1 - d2) * (d1 - d2) + (s1 - s2) * (s1 - s2));
        return odleglosc;
    }

    bool dodaj(const Miejscowosc &m);
    Miejscowosc* szukaj(const char* name);
    void szukaj(const char* txt, list<Miejscowosc> &result);

    friend ostream& operator << (ostream& strumyk, const LM& l)
    {
        for(list<Miejscowosc>::const_iterator it = l.lm.begin(); it != l.lm.end(); it++)
        {
            strumyk << *it;
        }
        strumyk << endl;
        return strumyk;
    }
};

bool LM::dodaj(const Miejscowosc &m)
{
    list<Miejscowosc>::const_iterator it;
    for(it = lm.begin(); it != lm.end(); it++)
    {
        if(it->nazwa == m.nazwa && it->region == m.region && it->mieszk == m.mieszk)
        {
            if(dist(it->dlugGPS, it->szerGPS, m.dlugGPS, m.szerGPS) <= epsilon) return false;
        }
    }
    lm.push_back(m);
    return true;
}

Miejscowosc *LM::szukaj(const char *name)
{
    list<Miejscowosc>::iterator it;
    for(it = lm.begin(); it != lm.end(); it++)
    {
        if(it->nazwa/*tolower()*/ == name /*tolower()*/)
            return &(*it);
    }
    return nullptr;
}

void LM::szukaj(const char *txt, list<Miejscowosc> &result)
{
    list<Miejscowosc>::const_iterator it;
    for(it = lm.begin(); it != lm.end(); it++)
    {
        if(it->nazwa.find(txt) <= it->nazwa.length() || it->region.find(txt) <= it->region.length())
            result.push_back(*it);
    }
}

int main()
{
    Miejscowosc m1("Miekinia", "krakowski", 600, 21, 63);
    Miejscowosc m2("Mielec", "mielecki", 70000, 35, 68);
    Miejscowosc m3("Miekinia", "krakowski", 600, 22, 64.5);

    LM l1;
    l1.dodaj(m1);
    l1.dodaj(m2);
    cout << l1;

    cout << *l1.szukaj("Mielec");

    l1.dodaj(m3);
    cout << endl << l1;

    list<Miejscowosc> res;
    l1.szukaj("iek", res);
    for(list<Miejscowosc>::const_iterator it = res.begin(); it != res.end(); it++) cout << *it;

    return 0;
}


