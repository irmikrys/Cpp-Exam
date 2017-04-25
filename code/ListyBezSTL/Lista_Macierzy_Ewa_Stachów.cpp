#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

class Macierz
{
    private:
        int rozmiar;
        int **ptr;
    public:
        Macierz();
        Macierz(int);
        Macierz(const Macierz & m);
        ~Macierz();
        Macierz & operator=(const Macierz & m);
        Macierz operator+(const Macierz & m) const;
        Macierz operator-(const Macierz & m) const;
        Macierz operator*(const Macierz & m) const;
        friend ostream & operator<<( ostream & out, const Macierz & m);
        friend istream & operator>>( istream & in, Macierz & m);
        int operator<(const Macierz & m);
        int operator>(const Macierz & m);
        int operator==(const Macierz & m);
        int operator!=(const Macierz & m);
};

template <class T>
class Element
{
    public:
		T wartosc;
		Element *nastepny;
		Element();
};

template <class T>
class Lista
{
    public:
        Element<T> *pierwszy;
		Lista();
		~Lista();
        Lista & operator=(const Lista<T> & l);
        Lista & operator+(const Lista<T> & l);
        void sortuj();
        int il_elementow();
};

Macierz::Macierz()
{
    rozmiar=0;
    ptr=NULL;
}

Macierz::Macierz(int rozmiar)
{
    ptr = new int*[rozmiar];
    for (int i = 0; i < rozmiar; i++)
        ptr[i] = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++)
            ptr[i][j]=rand()%10+0;
}

Macierz::Macierz (const Macierz & m)
    {
        int i;
        rozmiar=m.rozmiar;
        ptr = new int*[rozmiar];
        for (int i = 0; i < rozmiar; i++)
            ptr[i] = new int[rozmiar];
        for (int i = 0; i < rozmiar; i++)
            for (int j = 0; j < rozmiar; j++)
                ptr[i]=m.ptr[i];
    }

Macierz::~Macierz()
{
    for (int i = 0; i < rozmiar; i++)
    delete [] ptr[i];
    delete [] ptr;
    ptr=NULL;
    rozmiar=0;
}

ostream & operator<<( ostream & out, const Macierz & m)
{
    out << endl << endl;
    for(int i = 0; i < m.rozmiar; i++)
    {
        for(int j = 0; j < m.rozmiar; j++)
        {
            out.width(2);
            out << m.ptr[i][j];
            out << "  ";
        }
        out << endl;
    }
    return out;
}

istream & operator>>( istream & in, Macierz & m)
{
    bool if_rand;
    cout << " Podaj rozmiar ";
    cin >> m.rozmiar;
    cout << " Czy wprowadzic macierz automatycznie? 1-Tak 0-Nie  ";
    cin >> if_rand;
    cout << endl;
    if (if_rand==1)
    {
        m.ptr = new int*[m.rozmiar];
        for (int i = 0; i < m.rozmiar; i++)
            m.ptr[i] = new int[m.rozmiar];
        for (int i = 0; i < m.rozmiar; i++)
            for (int j = 0; j < m.rozmiar; j++)
                m.ptr[i][j]=rand()%10+0;
    }
    else
    {
        m.ptr = new int*[m.rozmiar];
        for (int i = 0; i < m.rozmiar; i++)
            m.ptr[i] = new int[m.rozmiar];
        for (int i = 0; i < m.rozmiar; i++)
            for (int j = 0; j < m.rozmiar; j++)
                in >> m.ptr[i][j];
    }
    return in;
}

Macierz Macierz::operator+(const Macierz & m) const
{
    int r;
    int a, b;
    if (rozmiar > m.rozmiar) r = rozmiar;
    else r = m.rozmiar;
    Macierz suma(r);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if ( (rozmiar <= i) || (rozmiar <= j) ) a = 0;
                else a = ptr[i][j];
            if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) b = 0;
                else b = m.ptr[i][j];
            suma.ptr[i][j] = a + b;
        }
    }
    return suma;
}

Macierz Macierz::operator-(const Macierz & m) const
{
    int r;
    int a, b;
    if (rozmiar > m.rozmiar) r = rozmiar;
    else r = m.rozmiar;
    Macierz roznica(r);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if ( (rozmiar <= i) || (rozmiar <= j) ) a = 0;
                else a = ptr[i][j];
            if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) b = 0;
                else b = m.ptr[i][j];
            roznica.ptr[i][j] = a - b;
        }
    }
    return roznica;
}

Macierz Macierz::operator*(const Macierz & m) const
{
    int wsp, r, a, b;
    if (rozmiar == m.rozmiar)
    {
        wsp=rozmiar;
        Macierz ilocz(rozmiar);
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < m.rozmiar; j++)
            {
                ilocz.ptr[i][j] = 0;
                for (int k = 0; k < wsp; k++)
                {
                    if ( rozmiar <= k ) a = 0;
                        else a = ptr[i][k];
                    if ( m.rozmiar <= k ) b = 0;
                        else b = m.ptr[k][j];
                    ilocz.ptr[i][j] += a * b;
                }
            }
        }
        return ilocz;
    }
    else return *this;
}

Macierz & Macierz::operator=(const Macierz & m)
{
    if (this == &m) return *this;
    rozmiar = m.rozmiar;
    ptr = new int*[rozmiar];
    for (int i = 0; i < rozmiar; i++)
            ptr[i] = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++)
            for (int j = 0; j < rozmiar; j++)
                ptr[i][j] = m.ptr[i][j];
    return *this;
}

int Macierz::operator<(const Macierz & m)
{
        {
            int wart;
            int roz;
            int sum=0;
            int sum_m=0;
            if (rozmiar > m.rozmiar) roz=rozmiar;
            else roz=m.rozmiar;
            for (int i = 0; i < roz; i++)
            {
                for (int j = 0; j < roz; j++)
                {
                    if ( (rozmiar <= i) || (rozmiar <= j) ) sum += 0;
                        else sum += ptr[i][j];
                    if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) sum_m = 0;
                        else sum_m += m.ptr[i][j];
                }
            }
            if (sum<sum_m) wart=1;
                else wart = 0;
            return wart;
        }
}

int Macierz::operator>(const Macierz & m)
{
        {
            int wart;
            int roz;
            int sum=0;
            int sum_m=0;
            if (rozmiar > m.rozmiar) roz=rozmiar;
            else roz=m.rozmiar;
            for (int i = 0; i < roz; i++)
            {
                for (int j = 0; j < roz; j++)
                {
                    if ( (rozmiar <= i) || (rozmiar <= j) ) sum += 0;
                        else sum += ptr[i][j];
                    if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) sum_m = 0;
                        else sum_m += m.ptr[i][j];
                }
            }
            if (sum>sum_m) wart=1;
                else wart = 0;
            return wart;
        }
}

int Macierz::operator==(const Macierz & m)
{
        {
            int wart;
            int sum=0;
            int sum_m=0;
            for (int i = 0; i < rozmiar; i++)
            {
                for (int j = 0; j < rozmiar; j++)
                {
                    if ( (rozmiar <= i) || (rozmiar <= j) ) sum += 0;
                        else sum += ptr[i][j];
                    if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) sum_m = 0;
                        else sum_m += m.ptr[i][j];
                }
            }
            if (sum==sum_m) wart=1;
                else wart = 0;
            return wart;
        }
}

int Macierz::operator!=(const Macierz & m)
{
        {
            int wart;
            int sum=0;
            int sum_m=0;
            for (int i = 0; i < rozmiar; i++)
            {
                for (int j = 0; j < rozmiar; j++)
                {
                    if ( (rozmiar <= i) || (rozmiar <= j) ) sum += 0;
                        else sum += ptr[i][j];
                    if ( (m.rozmiar <= i) || (m.rozmiar <= j) ) sum_m = 0;
                        else sum_m += m.ptr[i][j];
                }
            }
            if (sum!=sum_m) wart=1;
                else wart = 0;
            return wart;
        }
}

template<class T>
Element<T>::Element()
{
    nastepny=NULL;
}

template<class T>
Lista<T>::Lista()
{
    pierwszy=NULL;
}

template<class T>
Lista<T>::~Lista()
{
    Element<T> *tmp;
    while(pierwszy!=NULL)
    {
        tmp=pierwszy->nastepny;
        delete pierwszy;
        pierwszy=tmp;
    }
}

template<class T>
ostream & operator<<( ostream & out, const Lista<T> & l)
{
	Element<T> *tmp;
	tmp=l.pierwszy;
	while(tmp)
	{
		out << tmp->wartosc << " ";
		tmp=tmp->nastepny;
	}
	return out;
}

template<class T>
istream & operator>>( istream & in, Lista<T> & l)
{
    Element<T> *tmp;
	Element<T> *tmp_2;
	tmp_2=new Element<T>;
	in >> tmp_2->wartosc;
	tmp=l.pierwszy;
	if (tmp==NULL) l.pierwszy=tmp_2;
	else
	{
		while(tmp->nastepny!=NULL)
			tmp=tmp->nastepny;
		tmp->nastepny=tmp_2;
	}
    return in;
}

template<class T>
Lista<T> & Lista<T>::operator=(const Lista<T> & l)
{
    if (this == &l) return *this;
    this->~Lista();
    Element<T> * tmp;
    Element<T> *tmp_2;
    Element<T> *nowy;
    tmp=l.pierwszy;
    while(tmp!=NULL)
    {
        nowy=new Element<T>;
        nowy->wartosc=tmp->wartosc;
        if(pierwszy==NULL)
        {
            pierwszy=nowy;
            tmp_2=nowy;
        }
        else
        {
            tmp_2->nastepny=nowy;
            tmp_2=nowy;
        }
        tmp=tmp->nastepny;
    }
    return *this;
}

template<class T>
Lista<T> & Lista<T>::operator+(const Lista<T> & l)
{
    static Lista ls;
    ls.~Lista();
    Element<T> * tmp;
    Element<T> *tmp_2;
    Element<T> *nowy;
    tmp=this->pierwszy;
    while(tmp!=NULL)
    {
        nowy=new Element<T>;
        nowy->wartosc=tmp->wartosc;
        if(ls.pierwszy==NULL)
        {
            ls.pierwszy=nowy;
            tmp_2=nowy;
        }
        else
        {
            tmp_2->nastepny=nowy;
            tmp_2=nowy;
        }
        tmp=tmp->nastepny;
    }
    tmp=l.pierwszy;
    while(tmp!=NULL)
    {
        nowy=new Element<T>;
        nowy->wartosc=tmp->wartosc;
        if(ls.pierwszy==NULL)
        {
            ls.pierwszy=nowy;
            tmp_2=nowy;
        }
        else
        {
            tmp_2->nastepny=nowy;
            tmp_2=nowy;
        }
        tmp=tmp->nastepny;
    }
    return ls;
}

template<class T>
int Lista<T>::il_elementow()
{
    int ilosc =0;
    Element<T> *tmp;
    tmp=pierwszy;
    while(tmp!=NULL)
    {
        ilosc++;
        tmp=tmp->nastepny;
    }
    return ilosc;
}

template<class T>
void Lista<T>::sortuj()
{
    int ilosc = il_elementow();
    for(int i=1;i<=ilosc;i++)
    {
        Element<T> *tmp = pierwszy;
        while((tmp != NULL) && (tmp->nastepny != NULL))
        {
        	if(tmp->wartosc > tmp->nastepny->wartosc)
        	{
            T tmp_wartosc;
            tmp_wartosc=tmp->wartosc;
            tmp->wartosc=tmp->nastepny->wartosc;
            tmp->nastepny->wartosc=tmp_wartosc;
           }
          tmp=tmp->nastepny;
        }
    }
}

int main()
{
	class Lista<Macierz> a,b,c,d;
	//cout << " Breakpoint 1 " << endl; fflush(stdout);
	cout << "Wprowadz liste a (2 elementy)" << endl;
	cin >> a >> a;
	cout << endl << "Wprowadz liste b (3 elementy)" << endl;
	cin >> b >> b >> b;
	cout << endl << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << endl;
    c = a + b;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = a + b = " << c << endl;
	d = a;
	cout << "d = a = " << d << endl;
  	cout << endl;
  	c = a + b;
  	c = a + b;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = a + b = " << c << endl;
  	cout << endl;
    d = a;
	cout << "d = a = " << d << endl;
	cout << endl << "Wprowadz kolejne elementy do listy d (4 elementy)" << endl;
    cin >> d >> d >> d >> d;
	cout << endl << "a = " << a << endl;
	cout << "d = " << d << endl;
	cout << "Ilosc elementow d = " << d.il_elementow() << endl;
	d.sortuj();
	cout << "d = " << d << endl;
	cout << "Ilosc elementow d = " << d.il_elementow() << endl;
    return 0;
}
