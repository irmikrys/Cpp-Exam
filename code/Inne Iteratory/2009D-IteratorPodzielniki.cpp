/*Klasa Iterator ma
 * (a) konstruktor
 * (b) metode get() - zwraca biezacy element
 * (c) metode void next() - przesuwa iterator na nastepny element
 * (d) metode bool good() - zwraca true, jesli stan iteratora pozwala na poprawny odczyt elementu
 * Napisz iterator, ktory bedzie w konstruktorze otrzymywal liczbe calkowita i wyznaczal kolejne najmniejsze podzielniki
 * czyli np. dla liczby 36 wyznaczy ciag ( 2 2 3 3 ), natomiast dla 17 ciag ( 17 ), dla 1 ciag pusty.*/

#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

class Iterator
{
public:
    stringstream str;
    int liczba;

    Iterator(int l): liczba(l)
    {
        if (liczba == 1) str << " ";
        int sqr = (unsigned) sqrt(liczba);
        for(int i = 2; i < sqr; i++)
        {
            while(liczba % i == 0)
            {
                str << i << " ";
                liczba = liczba / i;
                if(liczba == 1) break;
            }
        }
        if(liczba > 1) str << liczba << " ";
    }

    string get()
    {
        string dzielnik;
        streampos pozycja;
        pozycja = str.tellg(); //pozycja aktualnego znaku 
        str >> dzielnik;
        str.seekg(pozycja); //ustala pozycje nowego znaku zeby rozpakowac ze strumienia
        return dzielnik;
    }

    void next()
    {
        string dzielnik;
        str >> dzielnik;
    }

    bool good()
    {
        return str.peek() != EOF; //returns the next character in the input without extracting it
    }

};

int main()
{
    for(Iterator it1(36); it1.good(); it1.next())
        cout << it1.get() << " ";

    for(Iterator it2(17); it2.good(); it2.next())
        cout << it2.get() << " ";

    for(Iterator it3(1); it3.good(); it3.next())
        cout << it3.get() << " ";

    return 0;
}



