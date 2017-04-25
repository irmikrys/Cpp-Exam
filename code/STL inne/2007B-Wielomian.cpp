/*[20] Wielomian a_0 x^0 + a_1 x^1 + ... + a_n x^n przechowywany w klasie
Wielomian w postaci ciagu wspolczynnikow a0, a1, a2,...,an (uwaga na
odwrotna kolejnosc!) zapisanego jako sekwencja liczb double umieszczonych
w kontenerze STL.

Zaimplementuj dla klasy wielomian:
(a) void ustawWspolczynnik(int n, double value) - ustala wartosc wsp an
(b) double wartosc(double x) - oblicza wartosc wielomianu dla wartosci x
(c) operator+ - wyznacza wielomian bedacy suma dwoch wielomianow
(d) operator* - wyznacza wielomian bedacy iloczynem dwoch wielomianow

[10] Zawartosc klasy Wielomian z poprzedniego zadania jest zapisywana w
pliku w formacie:
stopien_wielomianu *[wspolczynniki],
czyli np. ciag liczb 3 2 1 3 definiuje wielomian 2 + x + 3x^2

(a) napisz operator <<, ktory zapisuje wielomian w tym formacie
(b) napisz operator >>, ktory wczytuje wielomian*/

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

class Wielomian
{
public:
    vector<double> tab;

    Wielomian(){}
    Wielomian(vector<double> tab){this->tab = tab;}
    void ustawWspolczynnik(int n, double value);
    double wartosc(double x);
    friend Wielomian operator+(const Wielomian & w1, const Wielomian & w2);
    friend Wielomian operator*(const Wielomian & w1, const Wielomian & w2);
    friend ostream & operator<<(ostream & str, const Wielomian & w);
    friend istream & operator>>(istream & str, Wielomian & w);
    friend ofstream & operator<<(ofstream& zapis, const Wielomian & w);
    friend ifstream & operator>>(ifstream& zapis, Wielomian & w);
};

int main()
{
    vector<double> tab(1, 0);

    /*Wielomian w1(tab);
    w1.ustawWspolczynnik(3, 2);
    w1.ustawWspolczynnik(0, 1);
    w1.ustawWspolczynnik(2, 4);
    //cout << w1;

    Wielomian w2(tab);
    w2.ustawWspolczynnik(0, 2);
    w2.ustawWspolczynnik(1, 1);
    w2.ustawWspolczynnik(2, 1);
    cout << w2;
    cout << w2.wartosc(3) << endl;

    Wielomian w3 = w1 + w2;
    cout << w3;
    cout << w3.wartosc(2) << endl;

    Wielomian w4 = w1 * w2;
    cout << w4;

    ofstream zapis("wielomian.txt");
    zapis << w4;

    Wielomian w5(tab);
    cin >> w5;

    cout << w5;*/
    // Kacper
    ifstream odczyt("wielomian.txt");
    Wielomian w6(tab);
    odczyt >> w6;
    cout << w6;
    //Kacper
    return 0;
}

void Wielomian::ustawWspolczynnik(int n, double value)
{
    if(n < 0) return;
    if(n > tab.size() - 1)
    {
        tab.resize((unsigned long) (n + 1), 0);
    }
    tab[n] = value;
}

double Wielomian::wartosc(double x)
{
    double result = 0;
    int i = 0;
    vector<double>::const_iterator it;
    for(it = tab.begin(); it != tab.end(); ++it, ++i)
    {
        result += (*it) * pow(x, i);
    }
    return result;
}

Wielomian operator+(const Wielomian & w1, const Wielomian & w2)
{
    Wielomian w_tmp;
    vector<double>::const_iterator it1 = w1.tab.begin(), it2 = w2.tab.begin();
    while(it1 != w1.tab.end() || it2 != w2.tab.end())
    {
        if(it1 != w1.tab.end() && it2 != w2.tab.end())
        {
            w_tmp.tab.push_back((*it1) + (*it2));
            ++it1;
            ++it2;
        }
        else if(it1 == w1.tab.end())
        {
            w_tmp.tab.push_back(*it2);
            ++it2;
        }
        else
        {
            w_tmp.tab.push_back(*it1);
            ++it1;
        }
    }
    return w_tmp;
}

Wielomian operator*(const Wielomian &w1, const Wielomian &w2)
{
    Wielomian w_tmp;
    int size1 = (int) w1.tab.size() - 1;
    int size2 = (int) w2.tab.size() - 1;
    w_tmp.tab.resize((unsigned long) (size1 * size2), 0);

    vector<double>::const_iterator it1, it2;
    int i = 0;
    int j = 0;

    for(it1 = w1.tab.begin(); it1 != w1.tab.end(); it1++, i++)
    {
        j = 0;
        for(it2 = w2.tab.begin(); it2 != w2.tab.end(); it2++, j++)
        {
            w_tmp.tab[i + j] += (*it1) * (*it2);
        }
    }
    return w_tmp;
}

ostream &operator<<(ostream &str, const Wielomian &w)
{
    str << w.tab.size() << " * [ ";
    for(int i = 0; i < w.tab.size(); i++)
    {
        str << w.tab[i] << " ";
    }
    str << "]" << endl;
    return str;
}

ofstream &operator<<(ofstream &zapis, const Wielomian &w)
{

    zapis << w.tab.size() << " * [";
    for(int i = 0; i < w.tab.size(); i++)
    {
        zapis << w.tab[i] << " ";
    }
    zapis << "]";
    zapis.close();
    return zapis;
}

istream &operator>>(istream &str, Wielomian &w)
{
    int s;
    cout << "Podaj stopien wielomianu: ";
    str >> s;
    for(int i = 0; i < s; i++)
    {
        cout << "Podaj wspolczynnik nr " << i << ": ";
        double a; // Kacper bo tu mialas int zmienilem na double
        str >> a;
        w.ustawWspolczynnik(i, a);
    }
    return str;
}
//Kacper
ifstream &operator>>(ifstream &zapis, Wielomian &w)
{
    int x;
    double d;
    zapis >> x;
    zapis.seekg(5);
    for(int i = 0; i < x; ++i) {
        zapis >> d;
        w.ustawWspolczynnik(i, d);
    }
    return zapis;
}
//Kacper


