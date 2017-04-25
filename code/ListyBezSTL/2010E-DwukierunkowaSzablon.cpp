/*[25] Bez STL. Napisz szablon template<class T> class List<T>{} klasy przechowujacej elementy typu T na liscie
 * dwukierunkowej. Napisz:
 * (a) deklaracje klasy i pomocniczych danych oraz zaimplementuj konstruktor
 * (b) destruktor
 * (c) bool pushBack(const T&t) - dodaje element na koncu;
 * (d) void deleteFront();
 * (e) konstruktor kopiujacy;
 * (*) operator przypisania;
 * (*) operator== - porownuje dwie listy
 * (*) operator* - wyznacza czesc wspolna list
 * (*) pushFront(const T&t) - dodaje element na poczatku
 * (*) void deleteBack();
*/

#include <iostream>

using namespace std;

template<class T> class ListIterator;

template<class T>
class List
{
public:
    friend class ListIterator<T>;

    class ListElement
    {
    public:
        ListElement*next;
        ListElement*prev;
        T object;
    };

    ListElement*start;
    ListElement*end;
    int count;

    List()
    {
        start = end = 0;
        count = 0;
    }

    ~List(){free();}

    bool hasEl(T& t)const
    {
        for(ListElement* el = start; el; el = el->next)
        {
            if(el->object == t) return true;
        }
        return false;
    }

    bool pushBack(const T&t)
    {
        ListElement * tmp = new ListElement;

        tmp->object = t;
        tmp->next = 0;
        tmp->prev = end;
        end = tmp;
        count++;
        if(tmp->prev) tmp->prev->next = tmp;
        else start = tmp;
        return true;
    }

    bool pushFront(const T&t)
    {
        ListElement * tmp = new ListElement;

        tmp->object = t;
        tmp->prev = 0;
        tmp->next = start;
        start = tmp;
        count++;
        if(tmp->prev) tmp->prev->next = tmp;
        else end = tmp;
        return true;
    }

    void deleteEl(ListElement * e)
    {
        count--;
        if(e->prev) e->prev->next = e->next;
        else start = e->next;
        if(e->next) e->next->prev = e->prev;
        else end = e->prev;
        delete e;
    }

    void deleteBack()
    {
        if(count) deleteEl(end);
    }

    void deleteFront()
    {
        if(count) deleteEl(start);
    }

    List(const List<T>&other) {copy(other);}

    List& operator=(const List&other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    }

    bool operator == (const List& other)
    {
        if(count != other.count) { cout << "nie rowne" << endl; return false;}
        for(ListElement* el = start; el; el = el->next)
        {
            if(!other.hasEl(el->object)) { cout << "nie rowne" << endl; return false;}
        }
        cout << "rowne" << endl;
        return true;
    }

    friend List operator * (const List& l1, const List& l2)
    {
        List both;
        for(ListElement* el = l1.start; el; el = el->next)
        {
            if(l2.hasEl(el->object)) both.pushBack(el->object);
        }
        return both;
    }

    void wypisz()
    {
        ListElement*it=this->start;
        while(it!=0)
        {
            cout << it->object << endl;
            it = it->next;
        }
        cout << endl;
    }

protected:
    virtual void free()
    {
        ListElement*tmp = start;
        while(tmp)
        {
            deleteEl(tmp);
            tmp = tmp->next;
        }
        start = end = 0;
    }

    virtual void copy(const List& other)
    {
        start = end = 0;
        for(ListElement * it = other.start; it; it = it->next)
            pushBack(it->object);
    }
};

template<class T>
class ListIterator
{
    const List<T>&lista;
    typename List<T>::ListElement*current;
public:
    ListIterator(const List<T>&l): lista(l), current(l.start){}
    operator bool()const{return current != 0;}
    bool atEnd()
    {
        if(!current)
            return true;
        return false;
    }
    void next()
    {
        if(current) current = current->next;
    }
    void prev()
    {
        if(current) current = current->prev;
    }
    T& get()
    {
        return current->object;
    }
};

int main()
{
    List<int> lista1;
    lista1.pushFront(3); lista1.pushFront(5); lista1.pushFront(4); lista1.pushFront(7); lista1.pushFront(8);
    lista1.pushFront(1);
    lista1.wypisz();

    List<int> lista2;
    lista2.pushFront(1);
    lista2.wypisz();

    lista1.deleteFront();
    lista1.wypisz();

    lista2 = lista1;
    lista2.wypisz();

    lista2 == lista1;

    lista2.deleteBack();
    lista2.pushFront(2);

    lista1 == lista2;

    List<int> lista3 = lista1 * lista2;
    lista3.wypisz();

    return 0;
}
