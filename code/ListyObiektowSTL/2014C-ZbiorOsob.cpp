/*[20]Uzyj STL. Klasa Osoba ma atrybuty string imie, string nazw, string pesel. Napisz klase ZbiorOsob (przechowuje
 * un1kalne instancje osob).
 * (a) zadeklaruj wymagane struktury danych
 * (b) void dodaj(const char* imie, const char* nazw, const char* pesel) - dodaje osobe do zbioru. Jezeli osoba o
 *     numerze pesel istnieje, to zmienia pozostale atrybuty
 * (c) bool find(const char* pesel) - sprawdza, czy osoba identyfikowana przez pesel nalezy do zbioru
 * (d) operator < , ktory sprawdza czy zbiory zawieraja sie w sobie
 * Uzyj dowolnego kontenera STL.*/

#include <iostream>
#include <list>
using namespace std;

class Osoba
{
public:
    string imie;
    string nazw;
    string pesel;

    Osoba(string im, string naz, string pes): imie(im), nazw(naz), pesel(pes){}
    friend ostream& operator<< (ostream& strumyk, const Osoba& os)
    {
        strumyk << os.imie << " " << os.nazw << " " << os.pesel << endl;
        return strumyk;
    }
};

class ZbiorOsob
{
public:
    list<Osoba> zbior;
    int ilosc;

    ZbiorOsob(): ilosc(0){};
    ~ZbiorOsob(){};
    bool has(const Osoba& os)const;
    void dodaj(const char* imie, const char* nazw, const char* pesel);
    bool find(const char* pesel);
    bool operator < (const ZbiorOsob& z);
    friend ostream& operator << (ostream& strumyk, const ZbiorOsob& z);
};

bool ZbiorOsob::has(const Osoba &os) const
{
    list<Osoba>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(it->imie == os.imie && it->nazw == os.nazw && it->pesel == os.pesel) return true;
    }
    return false;
}

void ZbiorOsob::dodaj(const char *imie, const char *nazw, const char *pesel)
{
    list<Osoba>::iterator it;
    for(it = zbior.begin(); it!= zbior.end(); it++)
    {
        if(it->pesel == pesel)
        {
            it->imie = imie;
            it->nazw = nazw;
            return;
        }
    }
    Osoba os(imie, nazw, pesel);
    zbior.push_back(os);
    ilosc++;
}

bool ZbiorOsob::find(const char *pesel)
{
    list<Osoba>::const_iterator it;
    for(it = zbior.begin(); it!= zbior.end(); it++)
    {
        if(it->pesel == pesel)
        {
            return true;
        }
    }
    return false;
}

bool ZbiorOsob::operator<(const ZbiorOsob &z)
{
    if(ilosc > z.ilosc)
    {
        cout << "Nie zawieraja sie" << endl;
        return false;
    }
    list<Osoba>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(!z.has(*it))
        {
            cout << "Nie zawieraja sie" << endl;
            return false;
        }
    }
    cout << "Zawieraja sie" << endl;
    return true;
}

ostream &operator<<(ostream &strumyk, const ZbiorOsob &z)
{
    list<Osoba>::const_iterator it;
    for(it = z.zbior.begin(); it != z.zbior.end(); it++)
    {
        strumyk << *it;
    }
    strumyk << endl;
    return strumyk;
}


int main()
{
    ZbiorOsob zbior1;
    zbior1.dodaj("Irmina", "Krysiak", "97090306761");
    zbior1.dodaj("Rebecca", "Krysiak", "96022812400");
    zbior1.dodaj("Anka", "Zajac", "68072542000");
    cout << zbior1;
    zbior1.dodaj("Anna", "Krysiak", "68072542000");
    cout << zbior1;

    ZbiorOsob zbior2;
    zbior2.dodaj("Kacper", "Szalwa", "96091124001");
    zbior2.dodaj("Janusz", "Krysiak", "65031134871");
    zbior2.dodaj("Irmina", "Krysiak", "97090306761");
    zbior2.dodaj("Rebecca", "Krysiak", "96022812400");
    cout << zbior2;

    zbior1 < zbior2;

    return 0;
}



