/*[20] Klasa Zwierze ma atrybuty string imie, string gatunek, string data_ur. Napisz klase Zoo(liste Zwierzat).
 * (a) zadeklaruj wymagane struktury danych
 * (b) napisz funkcje bool Zoo::add(const Zwierze& z) - dodaje osobnika; jesli osobnik tego samego gatunku o takim
 *     samym imieniu istnieje, zwraca false
 * (c) void Zoo::find(const char* txt, list<Zwierze>& result) - znajduje osobnikow, w ktorych polach pojawia sie txt
 * (d) napisz funkcje bool Zoo::remove(const char* im, const char* gat) - usuwa osobnika o imieniu im nalezacego do
 *     gatunku gat;
 * Uzyj dowolnego kontenera STL.
 */

#include <iostream>
#include <list>
using namespace std;

class Zwierze
{
public:
    string imie;
    string gatunek;
    string data_ur;

    Zwierze(const char* im, const char* gat, const char* ur): imie(im), gatunek(gat), data_ur(ur){}
    friend ostream& operator << (ostream& strumyk, const Zwierze& z)
    {
        strumyk << z.imie << ", " << z.gatunek << ", urodzony " << z.data_ur << endl;
        return strumyk;
    }
};

class Zoo
{
public:
    list<Zwierze> lista;

    bool add(const Zwierze& z);
    void find(const char* txt, list<Zwierze>&result);
    bool remove(const char* im, const char* gat);
    friend ostream& operator << (ostream& strumyk, const Zoo& z)
    {
        list<Zwierze>::const_iterator it;
        for(it = z.lista.begin(); it != z.lista.end(); it++)
            strumyk << *it;
        strumyk << endl;
        return strumyk;
    }
};

bool Zoo::add(const Zwierze &z)
{
    list<Zwierze>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->imie == z.imie) return false;
    }
    lista.push_back(z);
    return true;
}

void Zoo::find(const char *txt, list<Zwierze> &result)
{
    list<Zwierze>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->imie.find(txt) <= it->imie.length() || it->gatunek.find(txt) <= it->gatunek.length() ||
                it->data_ur.find(txt) <= it->data_ur.length()) result.push_back(*it);
    }
}

bool Zoo::remove(const char *im, const char *gat)
{
    list<Zwierze>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->imie == im && it->gatunek == gat)
        {
            lista.erase(it);
            return true;
        }
    }
    return false;
}


int main()
{
    Zwierze z1("Drops", "kot", "3.09.2015");
    Zwierze z2("Fayter", "pies", "12.07.2003");
    Zwierze z3("Pusia", "papuga", "23.03.2009");

    Zoo zoo1;
    zoo1.add(z1);
    zoo1.add(z2);
    zoo1.add(z3);
    cout << zoo1;

    list<Zwierze> res;
    zoo1.find("r", res);
    list<Zwierze>::const_iterator it;
    for(it = res.begin(); it != res.end(); it++) cout << *it; cout << endl;

    zoo1.remove("Fayter", "kot");
    zoo1.remove("Drops", "kot");
    cout << zoo1;

    return 0;
}


