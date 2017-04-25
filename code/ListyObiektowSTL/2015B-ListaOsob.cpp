/*[25]Uzyj STL. Klasa Osoba jest zdefiniowana jako:
 * class Osoba{public: string imie, string nazw, string pesel;};
 * Napisz klase LO (lista Osob) z funkcjami:
 * (a) konstruktor i deklaracje
 * (b) void dodaj(const Osoba& os) - dodaje osobe do zbioru. Jezeli osoba o numerze pesel istnieje, to zmienia pola
 *     imie i nazwisko; inaczej dodaje obiekt os;
 * (c) void szukaj(LO& wynik, const char* txt) - wybiera osoby, ktorych pola (imie, nazwisko lub pesel) zawieraja txt
 *     i umieszcza w wynik
 * (d) operator == porownuje listy
 * (e) operator* - zwraca liste osob, ktore wystepuja na obu listach bedacych argumentami(przykladowo c = a * b)*/

#include <iostream>
#include <list>
#include <cctype>
using namespace std;

class Osoba
{
public:
    string imie;
    string nazw;
    string pesel;

    Osoba(string im, string naz, string pes): imie(im), nazw(naz), pesel(pes){}
    friend ostream& operator<< (ostream& strumyk, const Osoba& os)
    {
        strumyk << os.imie << " " << os.nazw << " " << os.pesel << endl;
        return strumyk;
    }
};

class LO
{
public:
    list<Osoba> lista;
    int ilosc;

    LO(): ilosc(0){}
    ~LO(){};
    bool has(const Osoba& os)const;
    void dodaj(const Osoba& os);
    void szukaj(LO& wynik, const char* txt);
    bool operator == (const LO& other);
    friend LO operator * (const LO& l1, const LO& l2);
    friend ostream& operator << (ostream& strumyk, const LO& z);
};

bool LO::has(const Osoba &os) const
{
    list<Osoba>::const_iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->imie == os.imie && it->nazw == os.nazw && it->pesel == os.pesel) return true;
    }
    return false;
}

void LO::dodaj(const Osoba& os)
{
    list<Osoba>::iterator it;
    for(it = lista.begin(); it!= lista.end(); it++)
    {
        if(it->pesel == os.pesel)
        {
            it->imie = os.imie;
            it->nazw = os.nazw;
            return;
        }
    }
    lista.push_back(os);
    ilosc++;
}

void LO::szukaj(LO &wynik, const char *txt)
{
    list<Osoba>::const_iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->imie.find(txt) <= it->imie.length() || it->nazw.find(txt) <= it->nazw.length()
           || it->pesel.find(txt) <= it->pesel.length()) wynik.dodaj(*it);
    }
}

bool LO::operator==(const LO &other)
{
    if(ilosc != other.ilosc)
    {
        cout << "Nie rowne" << endl << endl;
        return false;
    }
    list<Osoba>::const_iterator it1, it2;
    for(it1 = lista.begin(); it1 != lista.end(); it1++)
    {
        if(!other.has(*it1))
        {
            cout << "Nie rowne" << endl << endl;
            return false;
        }
    }
    for(it2 = other.lista.begin(); it2 != other.lista.end(); it2++)
    {
        if(!has(*it2))
        {
            cout << "Nie rowne" << endl << endl;
            return false;
        }
    }
    cout << "Rowne" << endl << endl;
    return true;
}

LO operator*(const LO &l1, const LO &l2)
{
    LO l_tmp;
    list<Osoba>::const_iterator it;
    for(it = l1.lista.begin(); it != l1.lista.end(); it++)
    {
        if(l1.has(*it) && l2.has(*it)) l_tmp.dodaj(*it);
    }
    return l_tmp;
}

ostream &operator<<(ostream &strumyk, const LO &l)
{
    list<Osoba>::const_iterator it;
    for(it = l.lista.begin(); it != l.lista.end(); it++)
    {
        strumyk << *it;
    }
    strumyk << endl;
    return strumyk;
}


int main()
{
    Osoba os1("Irmina", "Krysiak", "97090306761");
    Osoba os2("Rebecca", "Krysiak", "96022812400");
    Osoba os3("Anka", "Zajac", "68072542000");
    Osoba os4("Anna", "Krysiak", "68072542000");
    Osoba os5("Kacper", "Szalwa", "96091124001");
    Osoba os6("Janusz", "Krysiak", "65031134871");

    LO lista1;
    lista1.dodaj(os1);
    lista1.dodaj(os5);
    lista1.dodaj(os3);
    lista1.dodaj(os4);
    cout << lista1;

    LO lista2;
    lista2.dodaj(os4);
    lista2.dodaj(os1);
    lista2.dodaj(os5);
    cout << lista2;

    lista1 == lista2;

    LO lista3;
    lista3.dodaj(os1);
    lista3.dodaj(os6);
    lista3.dodaj(os2);
    cout << lista3;

    LO lista4 = lista1 * lista3;
    cout << lista4;

    LO lista5;
    lista1.szukaj(lista5, "00");
    cout << lista5;


    return 0;
}



