/*[10] W klasie class Osoba{string imie; string nazwisko;} zaimplementuj operatory
 * ktore sa niezbedne do tego, zeby klasa mogla stac sie parametrem instancjacji
 * szablonu STL set.
 * */

#include <iostream>

using namespace std;

class Osoba
{
public:
    string imie;
    string nazwisko;

    Osoba(){imie = " "; nazwisko = " ";}
    Osoba(string im, string naz): imie(im), nazwisko(naz){}
    friend bool operator==(Osoba const & os1, Osoba const & os2);
    friend bool operator<(Osoba const & os1, Osoba const & os2);
};

bool operator==(Osoba const &os1, Osoba const &os2)
{
    if((os1.imie == os2.imie) && (os1.nazwisko == os2.nazwisko))
    {
        cout << "Te same osoby" << endl;
        return true;
    }
    else
    {
        cout << "Rozne osoby" << endl;
        return false;
    }
}

//ma sprawdzac czy imie i nazwisko sie zawieraja osobno w drugim
bool operator<(Osoba const &os1, Osoba const &os2)
{
    if(
            (os1.imie.find(os2.imie) || os2.imie.find(os1.imie)) &&
            (os1.nazwisko.find(os2.nazwisko) || os2.nazwisko.find(os1.nazwisko))
            )
    {
        cout << "Zawieraja sie" << endl;
        return true;
    }
    else
    {
        cout << "Nie zawieraja sie" << endl;
        return false;
    }

}

int main()
{
    Osoba os1("Kacper", "Szalwa");
    Osoba os2("Irmina", "Krysiak");
    Osoba os3("Kacper", "Szalwa");
    Osoba os4("Irmina", "Szalwa");
    Osoba os5("Kacp", "Szal");

    os1 == os2;
    os1 == os3;

    os1 < os2;
    os1 < os3;
    os4 < os1;
    os5 < os3;

    return 0;
}