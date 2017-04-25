/*[20] Graf skierowany zawiera n wierzcholkow ponumerowanych od 0 do n-1 oraz pewna liczbe krawedzi przechowywanych
 * w kontenerze STL jako pary (start, end) gdzie start, end naleza do [0, n-1]. Z danego wierzcholka moze wychodzic
 * wiecej niz jedna krawedz, dwa wierzcholki moga byc polaczone tylko jedna skierowana krawedzia.
 * Droga w grafie jest sekwencja wierzcholkow, z ktorych kazde dwa kolejne sa polaczone krawedziami.

Zadeklaruj i zaimplementuj klase Graf z:
(a) Konstruktorem Graf(int _n) - ustala liczbe wierzcholkow
(b) metoda bool dodajKrawedz(int s, int e)
(c) operator< - sprawdza czy jeden graf jest podgrafem drugiego (podgraf moze zawierac mniejsza liczbe wierzcholkow
    i czesc krawedzi)
(d) bool jestDroga(const vector<int>&d) - metode ktora sprawdza czy d jest droga w grafie

[10] Zawartosc klasy Graf jest zapisywana w pliku w formacie:
    liczba_wierzcholkow liczba_krawedzi *[start end],
    czyli np.: ciag liczb 3 2 0 2 2 1 definiuje graf z 3 wierzcholkami numerow od 0 do 2 i dwoma krawedziami laczacymi
    wierzcholki 0 z 2 oraz 2 z 1.
(a) napisz operator <<, ktory zapisuje graf w tym formacie
(b) napisz operator >>, ktory wczytuje graf
 */

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Graf
{
public:
    struct Edge
    {
        int start;
        int end;
    };

    int n;
    vector<int> vertex;
    vector<Edge> edges;

    Graf(){}
    Graf(int _n);
    bool istnieje(int s, int e)const;
    bool dodajKrawedz(int s, int e);
    bool operator<(const Graf &g);
    bool jestDroga(const vector<int> &d);
    friend ostream& operator<<(ostream& strumyk, const Graf & g);
    friend ofstream& operator<<(ofstream& zapis, const Graf & g);
    friend istream& operator>>(istream& strumyk, Graf & g);
    friend ifstream& operator>>(ifstream& odczyt, Graf & g);

};

Graf::Graf(int _n) : n(_n)
{
    vertex.reserve((unsigned long) n);
    for(int i = 0; i < n; i++)
    {
        vertex[i] = i;
    }
}

bool Graf::istnieje(int s, int e)const
{
    vector<Edge>::const_iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if((it->start == s) && (it->end == e)) return true;
    }
    return false;
}

bool Graf::dodajKrawedz(int s, int e)
{
    if(istnieje(s, e) || istnieje(e, s) || e < 0 || s < 0 || e > n - 1 || s > n - 1)
        return false;

    Edge ed;
    ed.start = s;
    ed.end = e;
    edges.push_back(ed);

    return true;
}

bool Graf::operator<(const Graf &g)
{
    if(n > g.n || edges.size() > g.edges.size())
    {
        cout << "Nie jest podgrafem" << endl;
        return false;
    }

    vector<Edge>::const_iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        if(!g.istnieje(it->start, it->end))
        {
            cout << "Nie jest podgrafem" << endl;
            return false;
        }
    }
    cout << "Jest podgrafem" << endl;
    return true;
}

bool Graf::jestDroga(const vector<int> &d)
{
    for(int i = 0; i < d.size() - 1; i++)
    {
        if(!istnieje(d[i], d[i + 1]))
        {
            cout << "Nie jest droga w grafie" << endl;
            return false;
        }
    }
    cout << "Jest droga w grafie" << endl;
    return true;
}

ostream &operator<<(ostream &strumyk, const Graf &g)
{
    strumyk << g.n << " " << g.edges.size() << " *";
    for(int i = 0; i < g.edges.size(); i++)
    {
        strumyk << "[" << g.edges[i].start << " " << g.edges[i].end << "]";
    }
    strumyk << endl;
    return strumyk;
}

ofstream& operator<<(ofstream& zapis, const Graf & g)
{
    zapis << g.n;
    zapis << " " << g.edges.size() << " *";
    for(int i = 0; i < g.edges.size(); i++)
    {
        zapis << "[" << g.edges[i].start << " " << g.edges[i].end << "]";
    }
    zapis.close();
    return zapis;
}

istream &operator>>(istream &strumyk, Graf &g)
{
    int w, k;
    cout << "Ile wierzcholkow: ";
    strumyk >> w;
    g.n = w;
    cout << "Ile krawedzi: ";
    strumyk >> k;
    for(int i = 0; i < k; i++)
    {
        int s, e;
        strumyk >> s >> e;
        g.dodajKrawedz(s, e);
    }
    return strumyk;
}

ifstream &operator>>(ifstream &odczyt, Graf &g)
{
    int w, k;
    odczyt >> w;
    g.n = w;
    odczyt >> k;
    odczyt.seekg(6);
    for(int i = 0; i < k; i++)
    {
        int s, e;
        odczyt >> s >> e;
        odczyt.seekg(2, ios::cur); // tylko to zmienilem trzeba przesuwac co 2 wzgledem biezacej pozycji bo sa tam te nawiasy []
        g.dodajKrawedz(s, e);
    }
    return odczyt;
}


int main()
{
    Graf g1(6);
    g1.dodajKrawedz(0, 3);
    g1.dodajKrawedz(3, 2);
    g1.dodajKrawedz(2, 1);
    cout << g1;

    Graf g2(4);
    g2.dodajKrawedz(0, 3);
    g2.dodajKrawedz(0, 1);
    cout << g2;

    g2 < g1;

    vector<int> droga;
    droga.push_back(0);
    droga.push_back(3);
    droga.push_back(2);
    for(int i = 0; i < droga.size(); i++) cout << droga[i] << " "; cout << endl;

    g1.jestDroga(droga);

    Graf g3;
    cin >> g3;
    cout << g3;

    ofstream zapis("graf.txt");
    zapis << g3;

    ifstream odczyt("graf.txt");
    Graf g4;
    odczyt >> g4;
    cout << g4;


    return 0;
}
