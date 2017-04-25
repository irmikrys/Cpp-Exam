/*[20] Klasa Towar ma atrybuty: string nazwa, string kategoria, double
    cena, string kod. Napisz klase LT(lista towarow).
(a) Zadeklaruj wymagane struktury danych
(b) void dodaj(const Towar&t) - dodaje towar. Jesli jednak towar
    o takim kodzie juz istnieje, to zmienia pozostale atrybuty
(c) bool usun(const char*kod) - usuwa towar o danym kodzie (zwraca true,
    jesli znaleziono i usunieto)
(d) void szukaj(const char*txt, list<Towar&result) znajduje wszystkie
    towary, ktorych pole nazwa lub kategoria zawiera (jako fragment) txt.
(*) void polacz(const LT&other) - dodaje towary z other (analogicznie do
    dodaj)
*/

#include <iostream>
#include <list>

using namespace std;

class Towar
{
public:
    string nazwa;
    string kategoria;
    double cena;
    string kod;

    Towar(string n, string kat, double c, string k)
    :
    nazwa(n), kategoria(kat), cena(c), kod(k){}

    friend ostream& operator<<(ostream&stream, const Towar&towar1)
    {
        stream << towar1.nazwa << " " << towar1.kategoria << " " <<
                  towar1.cena << " " << towar1.kod << endl;
        return stream;
    }
};

class LT
{
public:
    list<Towar> l;
    void dodaj(const Towar&t)
    {
        list<Towar>::iterator it;
        for(it = l.begin(); ; it++)
        {
            if(it == l.end())
            {
                l.push_back(t);
                break;
            }
            if(it->kod == t.kod)
            {
                it->nazwa = t.nazwa;
                it->kategoria = t.kategoria;
                it->cena = t.cena;
                break;
            }
        }
    }
    bool usun(const char*kod)
    {
        list<Towar>::iterator it;
        for(it = l.begin(); ; it++)
        {
            if(it == l.end())
            {
                cout << "Nie znaleziono kodu" << endl;
                return false;
            }
            if(it->kod == kod)
            {
                l.erase(it);
                cout << "Usunieto produkt" << endl;
                return true;
            }
        }
    }
    void szukaj(const char*txt, list<Towar>&result)
    {
        list<Towar>::iterator it;
        for(it = l.begin(); it != l.end(); it++)
        {
            //find zwraca liczbe wiec prawie zawsze true, dlatego length
            if(it->nazwa.find(txt) <= it->nazwa.length() ||
               it->kategoria.find(txt) <= it->kategoria.length())
            {
                result.push_back(*it);
            }
        }
    }
    void polacz(const LT&other)
    {
        //const_iterator bo pracujemy na obiekcie const
        list<Towar>::const_iterator it;
        for(it = other.l.begin(); it != other.l.end(); it++)
            dodaj(*it);
    }
    void wypisz()
    {
        list<Towar>::iterator it;
        for(it = l.begin(); it != l.end(); it++)
            cout << it->nazwa << " " << it->kategoria << " " <<
                 it->cena << " " << it->kod << endl;
            cout << "---------------" << endl;
    }
};

int main()
{
    Towar towar1("karma", "jedzenie", 10.99, "12A3KRT");
    cout << towar1;
    Towar towar2("royal", "kody", 12.55, "12A3KRT");
    cout << towar2;
    Towar towar3("mydlo", "dom", 1.20, "34FGR78");
    cout << towar3;
    Towar towar4("lody", "jedzenie", 11.99, "5TH9UKT");
    cout << towar4;
    Towar towar5("szynszyla", "zwierzeta", 107.99, "TUK89D3");
    Towar towar6("chomik", "zwierzeta", 34.90, "CU83KV1");
    cout << "---------------" << endl;

    LT listaTowarow;
    list<Towar> listaResult;
    listaTowarow.dodaj(towar1);
    listaTowarow.wypisz();
    listaTowarow.dodaj(towar2);
    listaTowarow.wypisz();
    listaTowarow.dodaj(towar3);
    listaTowarow.dodaj(towar4);
    listaTowarow.wypisz();

    listaTowarow.szukaj("od", listaResult);
    list<Towar>::iterator it1;
        for(it1 = listaResult.begin(); it1 != listaResult.end(); it1++)
            cout << it1->nazwa << " " << it1->kategoria << endl;
    cout << "---------------" << endl;

    LT listaOther;
    listaOther.dodaj(towar1);
    listaOther.dodaj(towar5);
    listaOther.dodaj(towar6);

    listaTowarow.polacz(listaOther);
    listaTowarow.wypisz();

    listaTowarow.usun("34FGR78");
    listaTowarow.wypisz();

    return 0;
}
