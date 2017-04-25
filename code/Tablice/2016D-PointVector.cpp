/*[25] Bez STL. Klasa Point reprezentuje n-wymiarowy wektor w R^n. Przechowuje wartosci typu double w tablicy,
 * dla ktorej pamiec przydzielana jest na stercie w konstruktorze. Napisz:
 *
 * (a) deklarację i konstruktor Point(int n)
 * (b) double get(int i) - zwraca i-ty element tablicy; jesli i > n zwraca 0
 * (c) operator+ tworzy sume dwoch wektorow. Wynikowy obiekt ma rozmiar wiekszego ze skladnikow, brakujace elementy
 *     zastepowane są zerami
 * (d) konstruktor kopiujący
 * (e) operator przypisania
 * */

#include <iostream>

using namespace std;

class Point
{
public:
    double*tab;
    int size;

    Point();
    Point(int n);
    double get(int i);
    friend Point operator+(const Point& p1, const Point &p2);
    Point(const Point& other);
    Point& operator=(const Point& other);
    void wypisz();
protected:
    void free();
    void copy(const Point& other);
};

Point::Point()
{
    size = 0;
}

Point::Point(int n)
{
    tab = new double[n];
    size = n;
}

double Point::get(int i)
{
    return i > size ? 0 : tab[i];
}

Point operator+(const Point &p1, const Point &p2)
{
    Point p_tmp;
    if(p1.size > p2.size)
    {
        p_tmp.size = p1.size;
        p_tmp.tab = new double[p1.size];

        Point p2_tmp;
        p2_tmp.tab = new double[p1.size];
        p2_tmp.size = p1.size;
        for(int i = 0; i < p2.size; i++)
        {
            p2_tmp.tab[i] = p2.tab[i];
        }
        for(int i = p2.size; i < p1.size; i++)
        {
            p2_tmp.tab[i] = 0;
        }
        for(int i = 0; i < p_tmp.size; i++)
        {
            p_tmp.tab[i] = p1.tab[i] + p2_tmp.tab[i];
        }
    }
    else if(p1.size < p2.size)
    {
        p_tmp.size = p2.size;
        p_tmp.tab = new double[p2.size];

        Point p1_tmp;
        p1_tmp.tab = new double[p1.size];
        p1_tmp.size = p1.size;
        for(int i = 0; i < p1.size; i++)
        {
            p1_tmp.tab[i] = p1.tab[i];
        }
        for(int i = p1.size; i < p2.size; i++)
        {
            p1_tmp.tab[i] = 0;
        }
        for(int i = 0; i < p_tmp.size; i++)
        {
            p_tmp.tab[i] = p1_tmp.tab[i] + p2.tab[i];
        }
    }
    else if(p1.size == p2.size)
    {
        p_tmp.size = p1.size;
        p_tmp.tab = new double[p1.size];
        for(int i = 0; i < p_tmp.size; i++)
        {
            p_tmp.tab[i] = p1.tab[i] + p2.tab[i];
        }
    }

    return p_tmp;
}

Point::Point(const Point &other)
{
    copy(other);
}

Point &Point::operator=(const Point &other)
{
    if(&other != this)
    {
        free();
        copy(other);
    }
    return *this;
}

void Point::free()
{
    if(tab) delete[] tab;
}

void Point::copy(const Point &other)
{
    tab = new double[other.size];
    size = other.size;
    for(int i = 0; i < other.size; i++)
    {
        tab[i] = other.tab[i];
    }
}

void Point::wypisz()
{
    cout << "[ ";
    for(int i = 0; i < size; i++)
    {
        if(tab[i] >= 0 && tab[i] <= 9) cout << " ";
        cout << tab[i] << " ";
    }
    cout << "]" << endl;
}


int main()
{
    Point p1(5);
    for(int i = 0; i < p1.size; i++) p1.tab[i] = 2*i + 2;
    p1.wypisz();

    Point p2(3);
    for(int i = 0; i < p2.size; i++) p2.tab[i] = i + 4;
    p2.wypisz();

    Point p3(p1);
    p3.wypisz();

    Point p4(6);
    for(int i = 0; i < p4.size; i++) p4.tab[i] = 3*i - 6;
    p4.wypisz();
    p4 = p2;
    p4.wypisz();

    Point p5 = p2 + p1;
    p5.wypisz();

    Point p6 = p2 + p4;
    p6.wypisz();

    Point p7 = p3 + p2;
    p7.wypisz();

    cout << p7.get(4) << endl;
    cout << p7.get(5) << endl;
    cout << p7.get(6) << endl;

    return 0;
}