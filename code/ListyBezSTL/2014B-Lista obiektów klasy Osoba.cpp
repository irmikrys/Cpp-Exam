/*[25]Bez STL. Zaimplementuj liste jednokierunkowa przechowujaca obiekty
klasy class Osoba {char imie[32]; char nazw[32];}; Jezeli uznasz to za
przydatne, do klasy Osoba mozesz dodac dodatkowe skladowe...

Zaimplementuj:
(a) konstruktor i deklaracje
(b) destruktor
(c) bool dodaj(const char*imie, const char*nazw) - dodaje osobe na koncu
(d) konstruktor kopiujacy
(e) operator przypisania */

#include <iostream>
#include <cstring>

using namespace std;

class Osoba
{
    char imie[32];
    char nazw[32];
public:
    Osoba() = default;
    Osoba(const char*im, const char*naz)
    {
        strcpy(imie, im);
        strcpy(nazw, naz);
    }
    const char* getImie()const{return imie;}
    const char* getNazw()const{return nazw;}
    void wypisz()
    {
        cout << this->getImie() << " " << this->getNazw() << endl;
    }
};

struct Element
{
    Element*next;
    Osoba os;
};

class LO
{
public:
    Element*start;
    Element*end;

    LO(){start = end = 0;}
    ~LO(){free();}
    bool dodaj(const char*imie, const char*nazw)
    {
        Element*tmp = new Element();
        tmp->next = 0;
        tmp->os = Osoba(imie, nazw);
        if(end) end->next = tmp;
        tmp = end;
        if(!start) start = end;
        cout << "Dodano nowy element" << endl;
        return true;
    }
    LO(const LO&other) {copy(other);}
    LO&operator=(const LO&other)
    {
        if(&other!=this)
        {
            free();
            copy(other);
        }
        return *this;
    }
    void pokaz()
    {

    }
protected:
    void copy(const LO&other)
    {
        start = end = 0;
        for(Element*i = other.start; i; i++)
            dodaj(i->os.getImie(), i->os.getNazw());
    }
    void free()
    {
        while(start)
        {
            Element*tmp = start;
            start = start->next;
            delete tmp->next;
            delete tmp;
        }
        start = end = 0;
    }
};

int main()
{
    Osoba person1("Irmina", "Krysiak");
    person1.wypisz();
    Osoba person3("Rebecca", "Krysiak");
    Osoba person4("Przemek","Wojtasik");
    cout << "-----------------" << endl;

    LO lista1;
    lista1.dodaj("Kacper", "Szalwa");

    return 0;
}
