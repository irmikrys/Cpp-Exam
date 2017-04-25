/*[20] Uzyj STL. Klasy Kot, Pies i Kura dziedzicza po abstrakcyjnej klasie Zwierze. Klasa Zagroda jest kontenerem,
 * w ktorym umieszczane sa wskazniki typu Zwierze* do obiektow typu Kot, Pies lub Kura. Pamiec dla obiektow jest
 * przydzielana na stercie i zarzadzana przez klase Zagroda.
 * Zadeklaruj i zaimplementuj:
 * (a) wymagane klasy Zwierze, Kot, Pies, Kura, Zagroda
 * (b) destruktor dla Zagroda
 * (c) konstruktor kopiujacy dla Zagroda
 * (d) operator przypisania dla Zagroda*/

#include <iostream>
#include <vector>
using namespace std;

class Zwierze
{
public:
    virtual ~Zwierze(){}
    virtual Zwierze* clone()const = 0;
};

class Kot: public Zwierze
{
public:
    Zwierze* clone()const {
        return new Kot(*this);
    }
};

class Pies: public Zwierze
{
public:
    Zwierze* clone()const {
        return new Pies(*this);
    }
};

class Kura: public Zwierze
{
public:
    Zwierze* clone()const{
        return new Kura(*this);
    }
};


class Zagroda
{
public:
    vector<Zwierze*> zbior;

    Zagroda(){}
    ~Zagroda(){free();}
    Zagroda(const Zagroda& other){copy(other);}
    Zagroda& operator= (const Zagroda& other){if(&other != this){free(); copy(other);} return *this;}

    void dodaj(Zwierze* z)
    {
        zbior.push_back(z->clone());
    }
    friend ostream&operator<<(ostream& ostream1, const Zagroda& z)
    {
        for(int i = 0; i < z.zbior.size(); i++)
        {
            ostream1 << typeid(*z.zbior[i]).name() << " "; //wypisuje razem z dlugoscia :<
        }
        ostream1 << endl;
        return ostream1;
    }
protected:
    void copy(const Zagroda& other)
    {
        for(int i = 0; i < other.zbior.size(); i++)
        {
            dodaj(other.zbior[i]);
        }
    }
    void free()
    {
        vector<Zwierze*>::iterator it1 = zbior.begin(), it2 = zbior.end();
            //zbior.erase(it); -> tak nie mozna zrobic, bo traca waznosc iteratory po kazdym erase()
            zbior.erase(it1, it2); //usuwa ciag elementow, rozmiar tablicy zmniejszony o liczbe usunietych elementow
    }
};


int main()
{
    Zwierze* p = new Pies();
    Zwierze* c = new Kot();
    Zwierze* k = new Kura();

    Zagroda zagroda1;
    zagroda1.dodaj(p); zagroda1.dodaj(c); zagroda1.dodaj(c); zagroda1.dodaj(k); zagroda1.dodaj(k); zagroda1.dodaj(p);
    cout << zagroda1;

    Zagroda zagroda2;
    zagroda2.dodaj(c); zagroda2.dodaj(c); zagroda2.dodaj(p); zagroda2.dodaj(p);
    cout << zagroda2;

    Zagroda zagroda3(zagroda1);
    cout << zagroda3;

    zagroda3 = zagroda2;
    cout << zagroda3;

}

