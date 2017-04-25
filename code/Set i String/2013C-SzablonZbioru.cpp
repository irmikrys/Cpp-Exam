/*[25] Uzyj STL. Set<A> jest szablonem zbioru. Zaloz, ze dla A jest zdefiniowany jedynie operator == i !=.
 * Zaimplementuj:
 * (a) konstruktor i deklaracje
 * (b) bool insert(const A& a) - dodaje element do zbioru; zwraca false jesli element byl obecny
 * (c) bool remove(const A& a) - usuwa element ze zbioru; zwraca true jesli byl obecny
 * (d) operator < - sprawdza zawieranie zbiorow
 * (e) operator * - wyznacza przeciecie zbiorow*/

#include <iostream>
#include <list>
using namespace std;

class Typ
{
public:
    string imie;
    int wiek;

    Typ(string i, int w): imie(i), wiek(w){}
    bool operator == (const Typ& t)const // tu musisz dac const bo inaczej w 47 wywala blad ze probujesz uzyc funkcji
                                         // na obiekcie const, gdzie funkcja nie zapewnia const :D
    {
        return imie == t.imie && wiek == t.wiek;
    }
    bool operator != (const Typ& t)
    {
        return imie != t.imie || wiek != t.wiek;
    }
    friend ostream& operator << (ostream& stream, const Typ& t)
    {
        stream << t.imie << ", " << t.wiek << endl;
        return stream;
    }
};

// te 2 linijki dodalem bo tak trzeba jak chcesz funkcje friend definiowac poza klasa jako nie inline !!!
template <class A> class Set; // ta mowi ze istnieje sb jakas klasa Set sparametryzowana parametrem A
template <class A> Set<A> operator * (const Set<A> &s1, const Set<A> &s2); //  ta mowi ze bd istniec taka funkcja

template <class A>
class Set
{
public:
    list<A> zbior;

    Set();
    bool has(const A& a)const
    {
        typename list<A>::const_iterator it;
        for(it = zbior.begin(); it != zbior.end(); it++)
        {
            if(*it == a) return true;
        }
        return false;
    }
    bool insert(const A& a);
    bool remove(const A& a);
    bool operator < (const Set<A> &s);
    friend Set<A> operator * <> (const Set<A> &s1, const Set<A> &s2); // teraz mozemy ta funkcje o ktorej jest wczesniej
                                                // info dac jako zaprzyjazniona UWAGA NA ZAPIS <> po operator * WAZNE!!!
    void wypisz()
    {
        typename list<A>::const_iterator it;
        for(it = zbior.begin(); it != zbior.end(); it++)
        {
            cout << *it;
        }
        cout << endl;
    }
};

template <class A> Set<A>::Set()
{
    zbior.clear();
}

template <class A> bool Set<A>::insert(const A &a)
{
    typename list<A>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(*it == a) return false;
    }
    zbior.push_back(a);
    return true;
}

template <class A> bool Set<A>::remove(const A &a)
{
    typename list<A>::iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(*it == a)
        {
            zbior.erase(it);
            return true;
        }
    }
    return false;
}

template <class A> bool Set<A>::operator<(const Set<A> &s)
{
    if(this->zbior.size() > s.zbior.size()) return false;
    typename list<A>::const_iterator it1, it2;
    for(it1 = zbior.begin(); it1 != zbior.end(); it1++)
    {
        for(it2 = s.zbior.begin(); it2 != s.zbior.end(); it2++)
        {
            if(!s.has(*it1)) return false;
        }
        return true;
    }
    return false;
}

template <class A> Set<A> operator*(const Set<A> &s1, const Set<A> &s2) // a tu mozemy ja zdefiniowac
{
    Set<A> s_tmp;
    typename list<A>::const_iterator it; // tu const_iterator bo dzialasz na obiektach const
    for(it = s1.zbior.begin(); it != s1.zbior.end(); it++)
    {
        if(s2.has(*it)) s_tmp.insert(*it);
    }
    return s_tmp;
}


int main()
{
    Typ t1("Irmina", 18);
    Typ t2("Drops", 1);
    Typ t3("Rebsi", 20);
    Typ t4("Kacper", 19);

    Set<Typ> set1;
    set1.insert(t1);
    set1.insert(t2);
    set1.insert(t3);
    set1.insert(t2);
    set1.wypisz();

    Set<Typ> set2;
    set2.insert(t2);
    set2.insert(t1);
    set2.insert(t3);
    set2.insert(t4);
    set2.wypisz();

    if(set1 < set2) cout << "Zawiera" << endl << endl; else cout << "Nie zawiera" << endl << endl;

    Set<Typ> set3 = set1 * set2;
    set3.wypisz();

    set1.remove(t2);
    set1.wypisz();

    return 0;
}