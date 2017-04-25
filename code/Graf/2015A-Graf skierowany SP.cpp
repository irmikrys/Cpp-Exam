#include <iostream>
#include <list>

using namespace std;

class Vertex
{
public:
    const char * s;
    Vertex() : s(NULL) {}
    Vertex(const char * s)
    {
        this->s = s;
    }

    friend ostream & operator<<(ostream & strumyk, list<Vertex>::iterator v); // pomoczniczo
};

class Edge
{
public:
    list<Vertex>::iterator p;
    list<Vertex>::iterator k;
    Edge() : p(), k() {}
    Edge(list<Vertex>::iterator p, list<Vertex>::iterator k)
    {
        this->p = p;
        this->k = k;
    }

    friend ostream & operator<<(ostream & strumyk, list<Edge>::iterator e); // pomoczniczo
};

class SP
{
    list<Vertex> vertex;
    list<Edge> edges;
public:
    SP();
    void dodaj(const char *v);
    void usun(const char *v);
    void dodajKrawedz(const char *os1, const char *os2);
    void zlacz(const char *os1, const char *os2);
    void wypisz() //pomoczniczo
    {
        for(list<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
        {
            cout << it << endl;
        }
        cout << endl;
        for(list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            cout << it << endl;
        }
    }
};


SP::SP()
{

}

void SP::dodaj(const char *v)
{
    Vertex tmp(v);
    vertex.push_back(tmp);
}

void SP::usun(const char *v)
{

    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) //end za koncem listy
    {
        if(it->p->s == v || it->k->s == v)
        {
            it = edges.erase(it);  //bez it = usuwa obiekt pod iteratorem wiec musi byc
        }
    }

    for(list<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
    {
        if(it->s == v)
        {
            vertex.erase(it);
            break; // bo po usunieciu nie ma juz
        }
    }

}

void SP::dodajKrawedz(const char *os1, const char *os2)
{
    bool connected = false;
    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        if((it->p->s == os1) && (it->k->s == os2))
        {
            connected = true;
            break;
        }
    }
    if(!connected)
    {
        list<Vertex>::iterator it1 = vertex.end(), it2 = vertex.end(); //bo zakoniec do ostatniego
        for(list<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
        {
            if(it->s == os1)
            {
                it1 = it;
            }
            if(it->s == os2)
            {
                it2 = it;
            }
            if(it1 != vertex.end() && it2 != vertex.end()) break;
        }

        if(it1 != vertex.end() && it2 != vertex.end())
            edges.push_back(Edge(it1, it2));
            //tworzymy ta krawedz, uzywamy kosntruktora spraremtyrzowanego bo tylko uzupelnia
    }
}

void SP::zlacz(const char *os1, const char *os2)
{
    list<Vertex>::iterator it1 = vertex.end(), it2 = vertex.end();
    for(list<Vertex>::iterator it = vertex.begin(); it != vertex.end(); ++it)
    {
        if(it->s == os1)
        {
            it1 = it;
        }
        if(it->s == os2)
        {
            it2 = it;
        }
        if(it1 != vertex.end() && it2 != vertex.end()) break;
    }

    for(list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        if(it->p == it2)
        {
            it->p = it1;
        }
        if(it->k == it2)
        {
            it->k = it1;
        }
    }

    vertex.erase(it2);

}

//////////////////////////////////////////////////////////////////////////////

ostream & operator<<(ostream & strumyk, list<Vertex>::iterator v)
{
    strumyk << v->s;
    return strumyk;
}

//////////////////////////////////////////////////////////////////////////////

ostream & operator<<(ostream & strumyk, list<Edge>::iterator e)
{
    strumyk << e->p << " i " << e->k;
    return strumyk;
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
    SP obj;
    obj.dodaj("Kacper Szalwa");
    obj.dodaj("Irmina Krysiak");
    obj.dodaj("Ewa Stachow");
    obj.dodaj("Werka");
    obj.dodaj("Maciej Szymkat");
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.usun("Irmina Krysiak");
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.dodajKrawedz("Ewa Stachow", "Maciej Szymkat");
    obj.dodajKrawedz("Werka", "Kacper Szalwa");
    obj.dodajKrawedz("Maciej Szymkat", "Werka");
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.usun("Maciej Szymkat");
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.dodajKrawedz("Maciej Szymkat", "xxxxxxxxxxxxx"); // dodaje cos co nie istnieje, dziala git
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.dodaj("Maciej Szymkat");
    obj.dodaj("Irmina Krysiak");
    obj.dodajKrawedz("Ewa Stachow", "Maciej Szymkat");
    obj.dodajKrawedz("Maciej Szymkat", "Werka");
    obj.dodajKrawedz("Werka", "Kacper Szalwa"); // dodaje krawedz ktora istnieje, dziala git
    obj.dodajKrawedz("Irmina Krysiak", "Ewa Stachow");
    obj.wypisz();
    cout << "----------------------" << endl;
    obj.zlacz("Ewa Stachow", "Maciej Szymkat");
    obj.wypisz();
    return 0;
}



