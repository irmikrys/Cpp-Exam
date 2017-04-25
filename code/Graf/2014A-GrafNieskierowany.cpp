/*[20] Uzyj STL. Klasa GN reprezentuje graf nieskierowany. Zawiera on ponumerowane wierzcholki oraz krawedzie, ktorym
 * przypisana jest wartosc typu double, np. dlugosc. Dwa wierzcholki moga byc polaczone tylko jedna krawedzia.
 * (a) zadeklaruj wymagane struktury danych
 * (b) napisz funkcje void dodajKrawedz(int w1, int w2, double d1) - dodaje krawedz lub zmienia wage juz istniejacej
 * (c) bool usunKrawedz(int w1, int w2) - zwraca true, jesli krawedz zostala odnaleziona i usunieta
 * (d) void sasiedzi (int w, list<int>& r) - wypelnia r wierzcholkami sasiadujacymi z wierzcholkiem w */

#include <iostream>
#include <list>
using namespace std;

class GN
{
public:
    class Edge
    {
    public:
        int w1, w2;
        double d;
        friend ostream& operator << (ostream& strumyk, const Edge& e)
        {
            strumyk << e.w1 << "---" << e.w2 << ", " << e.d << endl;
            return strumyk;
        }
    };
    list<Edge> edges;
    list<int> vertex;

    GN();
    bool istniejeKrawedz(int w1, int w2)const;
    bool istniejeW(int w)const;
    void dodajKrawedz(int w1, int w2, double d1);
    bool usunKrawedz(int w1, int w2);
    void sasiedzi(int w, list<int>& r);

    friend ostream& operator<< (ostream& strumyk, const GN& g)
    {
        for(list<Edge>::const_iterator it = g.edges.begin(); it != g.edges.end(); it++)
            strumyk << *it;
        strumyk << endl;
        return strumyk;
    }
};

GN::GN()
{

}

bool GN::istniejeKrawedz(int w1, int w2) const
{
    list<Edge>::const_iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if((it->w1 == w1 && it->w2 == w2) || (it->w1 == w2 && it->w2 == w1)) return true;
    }
    return false;
}

bool GN::istniejeW(int w)const
{
    list<int>::const_iterator it;
    for(it = vertex.begin(); it != vertex.end(); it++)
    {
        if(*it == w) return true;
    }
    return false;
}

void GN::dodajKrawedz(int w1, int w2, double d1)
{
    list<Edge>::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if((it->w1 == w1 && it->w2 == w2) || (it->w1 == w2 && it->w2 == w1)) {it->d = d1; return;}
    }
    Edge ed;
    ed.w1 = w1;
    ed.w2 = w2;
    ed.d = d1;
    edges.push_back(ed);
    if(!istniejeW(w1)) vertex.push_back(w1);
    if(!istniejeW(w2)) vertex.push_back(w2);
}

bool GN::usunKrawedz(int w1, int w2)
{
    if(!istniejeKrawedz(w1, w2)) return false;
    list<Edge>::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if((it->w1 == w1 && it->w2 == w2) || (it->w1 == w2 && it->w2 == w1))
        {
            edges.erase(it);
        }
    }
    return true;
}

void GN::sasiedzi(int w, list<int> &r)
{
    list<int>::const_iterator it;
    for(it = vertex.begin(); it != vertex.end(); it++)
        if(istniejeKrawedz(*it, w)) r.push_back(*it);
}


int main()
{
    GN g1;
    g1.dodajKrawedz(3, 1, 2.2);
    cout << g1;
    g1.dodajKrawedz(1, 3, 2.4);
    g1.dodajKrawedz(2, 3, 1.5);
    g1.dodajKrawedz(4, 5, 1.7);
    g1.dodajKrawedz(3, 4, 2.8);
    g1.dodajKrawedz(6, 3, 2.9);
    cout << g1;

    g1.usunKrawedz(3, 2);
    cout << g1;

    list<int> neigh;
    g1.sasiedzi(3, neigh);
    for(list<int>::const_iterator it = neigh.begin(); it != neigh.end(); it++) cout << *it << " ";
    cout << endl;

    return 0;
}


