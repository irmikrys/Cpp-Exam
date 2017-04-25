/*[25] Bez STL. Klasa StringList jest jednokierunkowa lista przechowujaca wskazniki typu char*. Pamiec dla tekstow jest
 * dynamicznie alokowana na stercie i zarzadzana przez klase.

Zaimplementuj metody:
(a) konstruktor
(b) destruktor
(c) bool addBack(const char*) - dodawanie elementu na koncu listy
(d) konstruktor kopiujacy
(e) operator przypisania
(*)dodatkowo bool addFront, deleteFront, deleteBack, operator +

[25] Zadeklaruj i zaimplementuj klase StringListIterator (iterator dla kontenera z poprzedniego zadania) z metodami:
(a) konstruktorem
(b) bool atEnd() - czy iterator osiagnal koniec kontenera
(c) void next() - przesuwa iterator na nastepny element
(d) int get() - zwraca aktualny element
(e) podaj przyklad wywolania
(*) bool erase() - usuwa biezacy element; zwraca true jesli operacja sie powiodla
*/

#include <iostream>
using namespace std;

class StringList
{
public:
    friend class StringListIterator;

    class ListElement
    {
    public:
        ListElement*next;
        const char*text;
    };

    ListElement*start;
    ListElement*end;

    StringList(){start = end = 0;}
    ~StringList(){free();}
    bool addBack(const char*t)
    {
        ListElement*el = new ListElement();
        el->next = 0;
        el->text = t;
        if(end) end->next = el;
        end = el;
        if(!start) start = end;
        return true;
    }
    //dodatkowo
    bool addFront(const char*t)
    {
        ListElement*el = new ListElement();
        el->text = t;
        el->next = start;
        start = el;
        if(!end) end = start;
        return true;
    }
    bool deleteFront()
    {
        ListElement*p = start;
        if(p)
        {
            start = p->next;
            delete p;
        }
        return true;
    }
    bool deleteBack()
    {
        ListElement*p = start;
        if(p)
        {
            if(p->next)
            {
                while(p->next->next) p = p->next;
                delete p->next;
                p->next = 0;
            }
            else
            {
                delete p; //lista jednoelementowa
                start = end = 0;
            }
        }
        return true;
    }
    StringList(const StringList&other) {copy(other);}
    StringList& operator=(const StringList&other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    }
    friend StringList operator + (const StringList& l1, const StringList& l2)
    {
        StringList l_tmp;
        for(ListElement*el = l1.start; el; el = el->next)
        {
            l_tmp.addBack(el->text);
        }
        for(ListElement*el = l2.start; el; el = el->next)
        {
            l_tmp.addBack(el->text);
        }
        return l_tmp;
    }
    void wypisz()
    {
        ListElement*it=this->start;
        while(it!=0)
        {
            std::cout << it->text <<std::endl;
            it=it->next;
        }
        std::cout << std::endl;
    }
protected:
    void free()
    {
        for(ListElement*el = start; el; el = el->next)
        {
            deleteFront();
        }
        start = end = 0;
    }
    void copy(const StringList& other)
    {
        start = end = 0;
        for(ListElement*i = other.start; i; i = i->next)
            addBack(i->text);
    }
};


class StringListIterator
{
    const StringList&lista;
    StringList::ListElement*current;
public:
    StringListIterator(const StringList&l): lista(l), current(l.start){}
    operator bool()const{return current != 0;}
    StringListIterator&operator++()
    {
        if(current) current = current->next;
        return *this;
    }
    StringListIterator&operator++(int)
    {
        if(current->next) current = current->next;
        return *this;
    }
    bool erase()
    {
        if(!current) return false;
        else
        {
            StringListIterator it(lista);
            while(it)
            {
                if(it++ == *this) break;
                it++;
            }
            it.current->next = current->next;
            delete current->text;
            delete current;
            current = it.current->next;
        }
        return true;
    }
    bool atEnd()
    {
        if(!current) return true;
        return false;
    }
    void next()
    {
        if(current) current = current->next;
    }
    const char* get()
    {
        return current->text;
    }
};

int main()
{
    StringList lista;

    lista.addBack("jimp");
    lista.addBack("wha");
    lista.addFront("yolo");
    std::cout << "--------Po dodaniu front---------" << std::endl;
    lista.wypisz();

    StringList lista2;

    lista2.addBack("el drug lista");
    lista2.wypisz();
    std::cout << "---Teraz stane sie lista pierwsza---" << std::endl;
    lista2 = lista;
    lista2.wypisz();
    std::cout << "---Usuwam pierwszy element---" << std::endl;
    lista2.deleteFront();
    lista2.wypisz();
    std::cout << "---Usuwam ostatni element---" << std::endl;
    lista2.deleteBack();
    lista2.wypisz();
    std::cout << "---Dodaje kilka elementow do listy pierwszej---" << std::endl;
    lista.addBack("hej");
    lista.addFront("lista1");
    lista.addBack("ostatni");
    lista.wypisz();

    std::cout << "---Lista pierwsza----" << std::endl;
    lista.wypisz();

    std::cout << "---Lista druga----" << std::endl;
    lista2.wypisz();

    std::cout << "---Operator + -----" << std::endl;
    StringList lista3 = lista + lista2;
    lista3.wypisz();

    //uzycie iteratora
    StringListIterator it(lista3);
    for( ; !it.atEnd(); it.next())
        std::cout << it.get() << std::endl;

    return 0;
}
