/*[25] Bez STL. Napisz szablon klasy Matrix<T> bedacej dwuwymiarowa tablica
 * elementow typu T. Napisz:
 * (a) konstruktor i deklaracje - konstruktor Matrix(int r, int c) ustala
 *     liczbe wierszy i kolumn
 * (b) destruktor
 * (c) bool setAt(int r, int c, T& t) - ustala wartosc t w wierszu r i
 *     kolumnie c. Funkcja ma zwrocic false w przypadku blednych wartosci
 *     indeksow
 * (d) konstruktor kopiujacy
 * (e) operator przypisania
 * */

#include <iostream>

using namespace std;


template<class T>
class Matrix
{
public:
    int rows;
    int cols;
    T**tab;

    Matrix(int r, int c)
    {
        rows = r;
        cols = c;
        tab = new T*[rows];
        for(int i = 0; i < rows; i++)
            tab[i] = new T[cols];
    }

    ~Matrix(){free();}

    bool setAt(int r, int c, T& t)
    {
        if(r < 0 || c < 0 || r >= rows || c >= cols) return false;
        else
        {
            tab[r][c] = t;
        }
        return true;
    }

    T& operator()(int r, int c)
    {
        if(r < 0 || c < 0 || r >= rows || c >= cols) throw 0;
        else
        {
            return tab[r][c];
        }
    }

    Matrix(const Matrix&other){copy(other);}

    Matrix&operator=(const Matrix&other)
    {
        if(&other != this)
        {
            free();
            copy(other);
        }
        return *this;
    }

    void show()
    {
        for(int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if(tab[i][j] >= 0 && tab[i][j] < 9) cout << " ";
                cout << tab[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    virtual void copy(const Matrix&other)
    {
        rows = other.rows;
        cols = other.cols;
        if(rows) tab = new T*[rows];
        for(int i = 0; i < rows; i++)
            tab[i] = new T[cols];
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                tab[i][j] = other.tab[i][j];
    }

    virtual void free()
    {
        if(tab)
        {
            for(int i = 0; i < rows; i++)
                delete[] tab[i];
            delete[] tab;
            rows = cols = 0;
            tab = 0;
        }
    }
};


int main()
{
    Matrix<int> mat(3, 5);
    for(int i = 0; i < mat.rows; i++)
        for(int j = 0; j < mat.cols; j++)
            mat(i, j) = 2*i - j + 2;
    mat.show();
    Matrix<int> mat2(2, 4);
    for(int i = 0; i < mat2.rows; i++)
        for(int j = 0; j < mat2.cols; j++)
            mat2(i, j) = 3*i - 2*j + 1;
    int x = 2;
    mat2.setAt(0, 0, x);
    mat2.show();

    mat = mat2;
    mat.show();

    Matrix<int> mat3(mat2);
    mat3.show();

    return 0;
}

