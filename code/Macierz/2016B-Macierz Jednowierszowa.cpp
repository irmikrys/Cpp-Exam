/*[25] Napisz szablon klasy Matrix parametryzowanej typem T. Macierz, ktora ma
 * r wierszy i c kolumn przechowuje elementy wewnatrz tablicy (dla ktorej
 * pamiec przydzielona jest na stercie) o rozmiarze r*c. Rozmiar macierzy
 * jest staly w czasie zycia obiektu. Napisz:
 *
 * (a) Deklaracje i konstruktor(ustala rozmiar macierzy), moze wyrzucac wyjatek
 *     InvalidSize, jesli dane sa bledne
 * (b) destruktor
 * (c) T&operator()(int r, int c) - zwraca referencje do elementu, moze wyrzucac
 *     wyjatek InvalidIndex, jesli dane sa bledne
 * (d) Matrix<T> submatrix(int r1, int r2, int c1, int c2) - zwraca podmacierz
 *     zaczynajaca sie w (r1, c1) o rozmiarach (r2 - r1) x (c2 - c1); moze dac
 *     wyjatek
 * (e) operator przypisania
 * */

#include <iostream>

using namespace std;


template<class T>
class Matrix
{
    int r;
    int c;
    T *tab;
public:

    Matrix(int r, int c)
    {
        this->r = r;
        this->c = c;
        tab = new T[r * c];
    }

    ~Matrix()
    {
        free();
    }

    T&operator()(int r, int c)
    {
        if(r < 0 || r >= this->r || c < 0 || c >= this->c)
            throw -1;
        else return tab[(this->c) * r + c];
    }

    Matrix<T> submatrix(int r1, int r2, int c1, int c2)
    {
        if(r1 < 0 || r2 < 0 || c1 < 0 || c2 < 0 || r1 >= r || r2 > r || c1 >= c || c2 > c)
        {
            cout << endl << "Podano zle parametry" << endl;
        }
        Matrix<T> sub((r2 - r1), (c2 - c1));
        for(int i = 0; i < r2 - r1; i++)
            for(int j = 0; j < c2 - c1; j++)
            {
                sub.tab[(c2 - c1) * i + j] = tab[r1 * c + c1 + c * i + j];
            }
        sub.wypisz();
        return sub;
    }

    Matrix<T>&operator=(const Matrix<T>&other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    }

    void wypisz()
    {
        for(int i = 0; i < r * c; i++)
        {
            if(i % c == 0) cout << endl;
            if(tab[i] >= 0 && tab[i] < 10) cout << " ";
            cout << tab[i] << " ";
        }
        cout << endl;
    }
protected:
    void free()
    {
        if(tab) delete []tab;
    }
    void copy(const Matrix<T>&other)
    {
        tab = new T [other.r * other.c];
        r = other.r;
        c = other.c;
        for(int i = 0; i < (other.r * other.c); i++)
            tab[i] = other.tab[i];
    }
};

int main()
{
    int r = 6;
    int c = 4;
    Matrix<int> macierz(r, c);
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
        {
            macierz(i, j) = 2 * i - j;
        }
    macierz(0, 0) = 2;
    macierz(3, 2) = 3;
    macierz.wypisz();

    Matrix<int> macierz2(r - 1, c - 2);
    for(int i = 0; i < r - 1; i++)
        for(int j = 0; j < c - 2; j++)
        {
            macierz2(i, j) = 2 * i - j - 3;
        }
    macierz2.wypisz();

    macierz2 = macierz;

    macierz2.wypisz();

    macierz.submatrix(2, 5, 1, 3);

    return 0;
}