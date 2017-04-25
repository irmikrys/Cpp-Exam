/*[10] Klasy Pies, Kot i Koza dziedzicza po abstrakcyjnej klasie Zwierze.

Napisz funkcje:
void copy(vector<Zwierze*>&target, const vector<Zwierze*>src),
ktora kopiuje obiekty (tworzy nowe obiekty bedace kopia) umieszczone w
kontenerze src i wstawia je do target.*/

#include <iostream>
#include <vector>

using namespace std;

class Zwierze
{
public:
    virtual Zwierze*clone()const = 0;
};

class Pies : public Zwierze
{
public:
    Zwierze*clone()const
    {
        return new Pies(*this);
    }
};

class Kot : public Zwierze
{
public:
    Zwierze*clone()const
    {
        return new Kot(*this);
    }
};

class Koza : public Zwierze
{
public:
    Zwierze*clone()const
    {
        return new Koza(*this);
    }
};

void copy(vector<Zwierze*>&target, const vector<Zwierze*>src)
{
    vector<Zwierze*>::const_iterator it;
    for(it = src.begin(); it != src.end(); it++)
    {
        target.push_back((*it)->clone());
    }
}

int main()
{
    vector<Zwierze*> source;
    source.reserve(10);
    vector<Zwierze*> target;
    target.reserve(10);
    source.push_back((Zwierze*)new Kot);
    source.push_back((Zwierze*)new Pies);
    source.push_back((Zwierze*)new Koza);
    copy(target, source);
    return 0;
}
