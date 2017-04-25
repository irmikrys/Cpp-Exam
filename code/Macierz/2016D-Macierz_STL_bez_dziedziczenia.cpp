/*[30] Uzyj STL. DataTable jest dwuwymiarowa tablica przechowujaca elementy typu
 * double. Tablica ma n kolumn (wymiar ustalany przy jej tworzeniu). Pojedynczy
 * wiersz tablicy reprezentuje rekord danych. Rekordy moga byc dynamicznie
 * dodawane. Napisz:
 * (a) deklaracje i konstruktor (ustala liczbe kolumn tablicy)
 * (b) void add(double*tab, int size) - dodaje wiersz wypelniajac danymi z tab.
 *     Jesli size < n wypelnia reszte zerami. Jesli size > n obcina dane
 * (c) double& at(int r, int c, double value) - zwraca referencje do elementu w
 *     komorce [r, c]. Moze wyrzucac wyjatek InvalidIndex
 * (d) vector<double> getRow(int idx) - zwraca dane umieszczone w wierszu w
 *     postaci wektora
 * (e) double dist(int k, int j) - traktuje wiersze k oraz j jako punkty w R^n
 *     i oblicza dlugosc euklidesowska miedzy nimi. Morze wyrzucac InvalidIndex
 * (f) DataTable select(list<int> cols) - zwraca obiekt DataTable powstaly przez
 *     wybranie ze zrodlowej tabeli danych w kolumnach, ktorych numery sa na
 *     liscie cols
 * */

#include <iostream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

class DataTable
{
public:
    list< vector<double> > rows;
    int n;

    DataTable(int col)
    {
        n = col;
    }

    void add(double*tab, int size)
    {
        vector<double> tmp;
        tmp.resize(n, 0);
        if(size >= n)
        {
            for(int i = 0; i < n; i++) tmp[i] = tab[i];
            rows.push_back(tmp);
        }
        else if(size < n)
        {
            for(int j = 0; j < size; j++) tmp[j] = tab[j];
            rows.push_back(tmp);
        }
    }

    double& at(int r, int c, double value)
    {
        list< vector<double> >::iterator it;
        int counter = 0;
        for(it = rows.begin(); it != rows.end(); it++)
        {
            if(counter == r)
            {
                for(int i = 0; i < n; i++)
                {
                    if(i == c)
                    {
                        value = it->at(i);
                        break;
                    }
                }
            }
            else counter++;
        }
        return value;
    }

    vector<double> getRow(int idx)
    {
        vector<double> tmp;
        tmp.resize(n, 0);
        list< vector<double> >::iterator it;
        int counter = 0;
        for(it = rows.begin(); it != rows.end(); it++)
        {
            if(counter == idx)
            {
                for(int i = 0; i < n; i++) tmp[i] = it->at(i);
                break;
            }
            else counter++;
        }
        return tmp;
    }

    double dist(int k, int j)
    {
        double distance = 0;
        double suma = 0;
        vector<double> kwadrat;
        vector<double> pierwszy = getRow(k);
        vector<double> drugi = getRow(j);
        kwadrat.reserve(n);
        for(int i = 0; i < n; i++)
            kwadrat[i] = (pierwszy[i] - drugi[i]) * (pierwszy[i] - drugi[i]);
        for(int i = 0; i < n; i++)
            suma += kwadrat[i];
        distance = sqrt(suma);
        return distance;
    }

    DataTable select(list<int> cols)
    {
        int rozm = cols.size();

        list<int>::iterator it1;
        list< vector<double> >::iterator it;

        DataTable sub(rozm);
        for(it = rows.begin(); it != rows.end(); it++)
        {
            vector<double> tmp;
            double*tab = new double[rozm];
            for(it1 = cols.begin(); it1 != cols.end(); it1++)
            {
                tmp.push_back(it->at(*it1));
            }
            for(int i = 0; i < rozm; i++)
                tab[i] = tmp[i];
            sub.add(tab, rozm);
        }
        sub.wypisz();
        return sub;
    }

    void wypisz()
    {
        list< vector<double> >::iterator it;
        for(it = rows.begin(); it != rows.end(); it++)
        {
            for(int i = 0; i < n; i++)
                cout << it->at(i) << " ";
            cout << endl;
        }
    }
};


int main()
{
    double tab1[5] = {2, 5, 1, 7, 5};
    double tab2[7] = {3, 4, 1, 9, 2, 5, 7};
    double tab3[6] = {6, 0, 2, 7, 5, 4};

    list<int> cols;
    cols.push_back(1);
    cols.push_back(3);
    cols.push_back(4);

    DataTable tablica1(6);
    tablica1.add(tab1, 5);
    tablica1.add(tab2, 7);
    tablica1.add(tab3, 6);

    tablica1.wypisz();

    tablica1.getRow(2);

    cout << endl << tablica1.at(2, 2, 0) << endl << endl;

    tablica1.select(cols);

    cout << endl << tablica1.dist(2, 1) << endl << endl;


    return 0;
}
