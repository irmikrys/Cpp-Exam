/*[25]Bez STL. Napisz klase ListaTablic przechowujaca wartosci typu int w elementach klasy LE. LE zawiera tablice, dla
 * ktorej pamiec jest alokowana w konstruktorze i zwalniana w destruktorze. Podczas dodawania elementow typu int do
 * ListyTablic wypelniana jest tablica ostatniego elementu. Jesli zabraknie miejsca, tworzony jest nowy obiekt LE.
 * Napisz:
 * (a) konstruktor i destruktor LE
 * (b) deklaracje i konstruktor ListyTablic
 * (c) destruktor ListyTablic
 * (d) void dodaj(int v) - dodaje wartosc v umieszcajac na pierwszym wolnym miejscu w tablicy, jesli trzeba dodaje nowy
 *     element LE
 * (e) int pobierz(int n) - zwraca n-ty element*/

#include<iostream>
using namespace std;

class LE
{
public:
    int*tablica; //tablica na dane
    int rozmiar; //rozmiar tablicy
    int licznik; //ile miejsc zajetych
    LE*next;

    LE(int rozm)
    {
        tablica = new int[rozm];
        rozmiar = rozm;
        licznik = 0;
    }
    ~LE()
    {
        if(tablica) delete[] tablica;
    }
};

class ListaTablic
{
public:
    int ilosc; //ile elementow LE zostalo dodanych
    LE*start;
    LE*end;

    ListaTablic()
    {
        start = end = 0;
        ilosc = 0;
    }
    ~ListaTablic()
    {
        while(start)
        {
            LE*tmp = start;
            start = start->next;
            delete tmp->next;
            delete tmp;
        }
        start = end = 0;
    }
    void dodajLE(int rozm)
    {
        LE*tmp = new LE(rozm);
        tmp->next = 0;
        if(end) end->next = tmp;
        //tmp = end; <- tak mialas a ma byc na odwrot przeciez tak jak zrobilem nizej xd
        end = tmp;
        if(!start) start = end;
    }
    void dodaj(int v)
    {
        int rozm = 4;
        if(start == 0 || end->licznik == end->rozmiar)
            // tu start nie mozesz sprawdzac z == end bo to bd prawda dla 0 = 0 jak nie ma nic i 1 = 1
            // jak dodasz cokolwiek stad wysyp pamieci byl
        {
            dodajLE(rozm);
            ilosc++;
        }
        end->tablica[end->licznik] = v;
        end->licznik++;
    }
    int pobierz(int n)
    {
        int value = 0;
        int j = 0;
        while(start)
        {
            LE *tmp = start;
            for (int i = 0; i < tmp->rozmiar; i++)
            {
                if (j + i == n) value = tmp->tablica[i];
            }
            j = j + tmp->rozmiar;
            start = start->next;
        }
        return value;
    }
};


int main()
{
    ListaTablic lista1;
    lista1.dodaj(2);
    lista1.dodaj(4);
    lista1.dodaj(1);
    lista1.dodaj(7);
    lista1.dodaj(6);
    lista1.dodaj(3);
    lista1.dodaj(5);
    cout << lista1.pobierz(5) << endl;
    return 0;
}

