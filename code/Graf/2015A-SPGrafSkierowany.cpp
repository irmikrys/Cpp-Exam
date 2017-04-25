/*[25] Uzyj STL. Klasa SP jest garfem. Mozesz wyobrazic sobie, ze modeluje ona na przyklad spolecznosc. Wierzcholki sa
 * napisami (np. nazwiska osob), krawedzie skierowane modeluja relacje pomiedzy osobami. Podaj implementacje:
 * (a) konstruktor i deklaracje
 * (b) void dodaj(const char* v) - dodaje wierzcholek
 * (c) void usun(const char * v) - usuwa wierzcholek i wszystkie krawedzie
 * (d) void dodajKrawedz(const char* os1, const char* os2) - jesli os1 i os2 nie sa polaczone - dodaje krawedz od os1
 *     do os2
 * (e) void zlacz(const char* os1, const char* os2) - zastepuje dwa wezly grafu jednym o nazwie os1. Przy okazji scala
 *     tez krawedzie*/

#include <iostream>
#include <list>
using namespace std;

class SP
{
public:
    struct Edge
    {
        const char* v1;
        const char* v2;
    };

    list<Edge> edges;
    list<string> vertex;

    SP();
    bool hasV(const char* v)const
    {
        list<string>::const_iterator it;
        for(it = vertex.begin(); it != vertex.end(); it++)
        {
            if(*it == v) return true;
        }
        return false;
    }
    void dodaj(const char* v);
    void usun(const char* v);
    void dodajKrawedz(const char* os1, const char* os2);
    void usunKrawedz(const char* os1, const char* os2);
    void zlacz(const char* os1, const char* os2);

    friend ostream &operator << (ostream& ostream1, const SP& g)
    {
        for(list<string>::const_iterator it = g.vertex.begin(); it != g.vertex.end(); it++)
            ostream1 << *it << " ";
        ostream1 << endl;
        for(list<Edge>::const_iterator it = g.edges.begin(); it != g.edges.end(); it++)
            ostream1 << it->v1 << "--->" << it->v2 << endl;
        ostream1 << endl;
        return ostream1;
    }
};

SP::SP()
{

}

void SP::dodaj(const char *v)
{
    list<string>::const_iterator it;
    for(it = vertex.begin(); it != vertex.end(); it++)
    {
        if(*it == v) return;
    }
    vertex.push_back(v);
}

void SP::usun(const char *v)
{
    list<string>::iterator itV;
    list<Edge>::iterator itE;
    for(itE = edges.begin(); itE != edges.end(); itE++)
    {
        if(itE->v1 == v) usunKrawedz(v, itE->v2);
        if(itE->v2 == v) usunKrawedz(itE->v1, v);
    }
    for(itV = vertex.begin(); itV != vertex.end(); itV++)
    {
        if(*itV == v)
        {
            vertex.erase(itV);
        }
    }
}

void SP::dodajKrawedz(const char *os1, const char *os2)
{
    list<Edge>::const_iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if(it->v1 == os1 && it->v2 == os2) return;
    }
    if(hasV(os1) && hasV(os2))
    {
        Edge ed;
        ed.v1 = os1;
        ed.v2 = os2;
        edges.push_back(ed);
    }
}

void SP::usunKrawedz(const char *os1, const char *os2)
{
    list<Edge>::const_iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if(it->v1 == os1 && it->v2 == os2)
        {
            edges.erase(it);
            return;
        }
    }
}

void SP::zlacz(const char *os1, const char *os2)
{
    list<Edge>::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if((it->v1 == os1 && it->v2 == os2) || (it->v2 == os1 && it->v1 == os2))
        {
            edges.erase(it);
        }
        if(it->v1 == os2 && it->v2 != os1)
        {
            usunKrawedz(os2, it->v2);
            dodajKrawedz(os1, it->v2);
        }
        if(it->v2 == os2 && it->v1 != os1)
        {
            usunKrawedz(it->v1, os2);
            dodajKrawedz(it->v1, os1);
        }
    }
    usun(os2);
}


int main()
{
    SP graf;
    graf.dodaj("Irmina"); graf.dodaj("Rebecca"); graf.dodaj("Kacper"); graf.dodaj("Anna"); graf.dodaj("Michal");

    graf.dodajKrawedz("Irmina", "Kacper"); graf.dodajKrawedz("Rebecca", "Irmina"); graf.dodajKrawedz("Anna", "Irmina");
    graf.dodajKrawedz("Anna", "Rebecca"); graf.dodajKrawedz("Michal", "Irmina");

    cout << graf;

    graf.zlacz("Irmina", "Rebecca");
    cout << graf;

    return 0;
}


