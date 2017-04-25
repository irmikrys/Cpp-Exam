/*Uzyj STL. Relation<A, B> jest szablonem relacji (podzbioru iloczynu kartezjanskiego A x B). Zaloz, ze dla obu typow
 * A i B zdefiniowany jest operator ==. Napisz:
 * (a) konstruktor i deklaracje
 * (b) bool addPair(const A& a, const B& b) - dodaje pare (jesli nie istniala wczesniej zwraca true)
 * (c) bool removePair(const A& a, const B& b) - usuwa pare(jesli brak zwraca false)
 * (d) void getSucc(const A& a, list<B>& result) wypelnia result nastepnikami elementu a
 * (e) void getPred(const B& b, list<A>& result) wypelnia result poprzednikami elementu b*/

#include <iostream>
#include <list>
#include <map>
using namespace std;

template <class A, class B>
class Relation
{
public:
    class Pair
    {
    public:
        A first;
        B second;
        Pair(A a, B b): first(a), second(b){}
    };

    list<A> preds;
    list<B> sucs;
    list<Pair> pairs;

    bool isPair(const A& a, const B& b)const
    {
        for(typename list<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if(it->first == a && it->second == b) return true;
        }
        return false;
    }

    bool hasA(const A& a)const
    {
        for(typename list<A>::const_iterator it = preds.begin(); it != preds.end(); it++)
        {
            if(*it == a) return true;
        }
        return false;
    }

    bool hasB(const B& b)const
    {
        for(typename list<B>::const_iterator it = sucs.begin(); it != sucs.end(); it++)
        {
            if(*it == b) return true;
        }
        return false;
    }

    Relation();
    bool addPair(const A& a, const B& b);
    bool removePair(const A& a, const B& b);
    void getSucc(const A& a, list<B>& result);
    void getPred(const B& b, list<A>& result);

    friend ostream& operator<<(ostream& os, const Relation& r)
    {
        for(typename list<A>::const_iterator it = r.preds.begin(); it != r.preds.end(); it++) os << *it << " ";
        os << endl;
        for(typename list<B>::const_iterator it = r.sucs.begin(); it != r.sucs.end(); it++) os << *it << " ";
        os << endl;
        for(typename list<Pair>::const_iterator it = r.pairs.begin(); it != r.pairs.end(); it++)
            os << it->first << "--->" << it->second << endl;
        os << endl;
        return os;
    }
};

template <class A, class B> Relation<A, B>::Relation() {

}

template <class A, class B> bool Relation<A, B>::addPair(const A &a, const B &b)
{
    if(isPair(a, b)) return false;
    pairs.push_back(Pair(a, b));
    if(!hasA(a)) preds.push_back(a);
    if(!hasB(b)) sucs.push_back(b);
    return true;
}

template <class A, class B> bool Relation<A, B>::removePair(const A &a, const B &b)
{
    if(!isPair(a, b)) return false;
    for(typename list<Pair>::iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        if(it->first == a && it->second == b) pairs.erase(it);
    }
    return true;
}

template <class A, class B> void Relation<A, B>::getSucc(const A &a, list<B> &result)
{
    for(typename list<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        if(isPair(a, it->second))
        {
            bool isB = false;
            for(typename list<B>::const_iterator it1 = result.begin(); it1 != result.end(); it1++)
            {
                if(*it1 == it->second) {isB = true; break;}
            }
            if(!isB) result.push_back(it->second);
        }
    }
}

template <class A, class B> void Relation<A, B>::getPred(const B &b, list<A> &result)
{
    for(typename list<Pair>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    {
        if(isPair(it->first, b))
        {
            bool isA = false;
            for(typename list<A>::const_iterator it1 = result.begin(); it1 != result.end(); it1++)
            {
                if(*it1 == it->first) {isA = true; break;}
            }
            if(!isA) result.push_back(it->first);
        }
    }
}

int main()
{
    Relation<int, string> rel;

    rel.addPair(1, "Irmina");
    rel.addPair(3, "Rebecca");
    rel.addPair(7, "Anna");
    rel.addPair(1, "Janusz");
    rel.addPair(1, "Rebecca");
    rel.addPair(4, "Rebecca");

    cout << rel;

    list<int> res1;
    list<string> res2;

    rel.getPred("Rebecca", res1);
    for(list<int>::const_iterator it = res1.begin(); it != res1.end(); it++) cout << *it << endl; cout << endl;

    rel.getSucc(1, res2);
    for(list<string>::const_iterator it = res2.begin(); it != res2.end(); it++) cout << *it << endl; cout << endl;

    rel.removePair(1, "Anna");
    rel.removePair(3, "Rebecca");
    cout << rel;

    return 0;
}

