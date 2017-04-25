/*[20] Bez STL. Napisz szablon relacji Rel parametryzowanej typami K, V, czyli kontenera zawierajacego UN1KALNE pary
 * elementow typow K i V.
 *
 * (a) deklaracje i konstruktor
 * (b) bool dodaj(const K&k, const V&v) - dodaje jako element kontenera pare (k, v); zwraca true, jesli pary nie bylo
 *     w kontenerze i zostala dodana
 * (c) bool znajdz(const K&k, const V&v) zwraca true, jesli kontener zawiera pare (k, v); zaloz ze K i V implementuja
 *     operator ==
 * (d) operator += dodajacy zawartosc drugiej relacji
 * W (c) i (d) mozesz wykorzystac iterator z zadania 4.
 *
 * [20] Napisz szablon iteratora dla kontenera z zadania poprzedniego:
 *
 * (a) deklaracja i konstruktor
 * (b) const K&pierwszy() i const V&drugi() - funkcje zwracaja wartosci K i V biezacej pary
 * (c) operator++ - przesuwa iterator
 * (d) bool czyKoniec() - zwraca true, jesli iterator osiagnal koniec kontenera
 * */

#include <iostream>

using namespace std;

template <class K, class V> class RelIterator;

template <class K, class V>
class pary
{
public:
    K k;
    V v;
    bool operator==(const pary<K, V> & p);
};
template <class K, class V>
bool pary<K, V>::operator==(const pary<K, V> & p)
{
    if(k == p.k && v == p.v) return true;
    return false;
}

template <class K, class V>
class Rel
{
public:
    friend class RelIterator<K, V>;
    pary<K, V>*tab;
    int size;

    Rel();
    bool dodaj(const K&k, const V&v);
    bool znajdz(const K&k, const V&v);
    Rel & operator+=(const Rel & other);
    void wypisz();
};

template <class K, class V> Rel<K, V>::Rel()
{
    tab = new pary<K, V>[0];
    size = 0;
}

template <class K, class V> bool Rel<K, V>::dodaj(const K &k, const V &v)
{
    if(znajdz(k, v)) return false;
    if(size == 0)
    {
        tab = new pary<K, V>[1];
        tab[0].k = k;
        tab[0].v = v;
        size = 1;
        return true;
    }
    else
    {
        pary<K, V>*tmp = new pary<K, V>[size + 1];
        for(int i = 0; i < size; i++)
        {
            tmp[i] = tab[i];
        }
        if(tab) delete []tab;
        tab = new pary<K, V>[size + 1];
        for(int i = 0; i < size; i++)
        {
            tab[i] = tmp[i];
        }
        tab[size].k = k;
        tab[size].v = v;
        size = size + 1;
        return true;
    }
}

template <class K, class V> bool Rel<K, V>::znajdz(const K &k, const V &v)
{
    for(int i = 0; i < size; i++)
    {
        if(tab[i].k == k && tab[i].v == v) return true;
    }
    return false;
}

template <class K, class V> Rel<K, V> &Rel<K, V>::operator+=(const Rel<K, V> &other)
{
    for(int i = 0; i < other.size; i++)
    {
        this->dodaj(other.tab[i].k, other.tab[i].v);
    }
    return *this;
}

template <class K, class V> void Rel<K, V>::wypisz()
{
    for(int i = 0; i < size; i++)
    {
        cout << this->tab[i].k << "-" << this->tab[i].v << endl;
    }
    cout << endl;

}


template <class K, class V>
class RelIterator
{
    friend class pary<K, V>;
public:
    const Rel<K, V> &relacja;
    pary<K, V> *current;

    RelIterator(const Rel<K, V> &relacja);
    const K&pierwszy();
    const V&drugi();
    RelIterator & operator++();
    bool czyKoniec();
};

template <class K, class V>
RelIterator<K, V>::RelIterator(const Rel<K, V> &rel):relacja(rel), current(rel.tab)
{

}

template <class K, class V> const K &RelIterator<K, V>::pierwszy()
{
    return current->k;
}

template <class K, class V> const V &RelIterator<K, V>::drugi()
{
    return current->v;
}

template <class K, class V> RelIterator<K, V>& RelIterator<K, V>::operator++() //preinkrementacja
{
    current++;
    return *this;
}

template <class K, class V> bool RelIterator<K, V>::czyKoniec()
{
    return *current == relacja.tab[relacja.size - 1];
}


int main()
{
    Rel<int, string> relacja1;
    relacja1.dodaj(18, "Irmis");
    relacja1.dodaj(19, "Kacpi");
    relacja1.dodaj(21, "Rebi");
    relacja1.dodaj(11, "Drops");
    relacja1.wypisz();

    RelIterator<int, string> it(relacja1);

    for( ; ; ++it)
    {
        cout << it.pierwszy() << "-" << it.drugi() << endl;
        if(it.czyKoniec()) break;
    }
    Rel<int, string> relacja2;
    relacja2.dodaj(13, "Rebs");
    relacja2.dodaj(11, "Drops");
    relacja2.dodaj(17, "Anny");
    relacja2.dodaj(14, "Fayter");
    relacja2.wypisz();

    relacja1 += relacja2;
    relacja1.wypisz();

    return 0;
}



