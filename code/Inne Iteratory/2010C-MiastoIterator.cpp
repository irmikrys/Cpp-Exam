/*Klasa Miasto jest zadeklarowana jako
 * class Miasto {public: std::string name; int population;};
 * Napisz iterator, ktory bedzie zwracal kolejne miasta  porzadku okreslonym przez liczbe mieszkancow (population)
 * (a) konstruktor Iterator(const list<Miasto>& l); //uwaga const
 * (b) operator bool()const zwracajacy true, jesli odczyt jest mozliwy
 * (c) operator++ () przesuwajacy iterator na nastepne slowo (posortowane!)
 * (d) Miasto* get() zwraca biezace miasto
 * Uwaga, do ewentualnego sortowania nalezy uzyc odpowiedniej funkcji bibliotecznej! */

#include <iostream>
#include <list>
using namespace std;

class Miasto
{
public:
    string name;
    int population;
    Miasto(){}
    Miasto(string n, int p):name(n), population(p){}

};

bool compare(const Miasto& m1, const Miasto& m2){
    if(m1.population != m2.population)
        return m1.population < m2.population;
    return m1.population == m2.population;
}

class Iterator
{
public:
    list<Miasto> lista;
    list<Miasto>::iterator current;

    Iterator(const list<Miasto>& l);
    operator bool()const;
    Iterator& operator++ ();
    Miasto* get();
};

Iterator::Iterator(const list<Miasto> &l) {
    for(list<Miasto>::const_iterator it = l.begin(); it != l.end(); it++){
        lista.push_back(*it);
        lista.sort(compare);
    }
    current = lista.begin();
}

Iterator::operator bool() const {
    return current != lista.end();
}

Iterator &Iterator::operator++() {
    current++;
    return *this;
}

Miasto *Iterator::get() {
    return &(*current);
}

int main()
{
    Miasto m1("Trzebinia", 10000); Miasto m2("Miekinia", 600); Miasto m3("Chrzanow", 20000);
    Miasto m4("Krzeszowice", 2000); Miasto m5("Filipowice", 600);
    list<Miasto> l1; l1.push_back(m1); l1.push_back(m2); l1.push_back(m3); l1.push_back(m4); l1.push_back(m5);

    for(Iterator it1(l1); it1; ++it1) cout << it1.get()->population << " " << it1.get()->name << endl;
    return 0;
}




