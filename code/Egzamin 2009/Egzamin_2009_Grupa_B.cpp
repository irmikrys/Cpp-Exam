#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// ------------------------------ [ Zadanie 1 ] ------------------------------

class VectorOfIntArray
{
	private:
	vector<pair<int *, int> > tabl;

	public:
	VectorOfIntArray(void) {}
	void add(int *, int);
	int getSize(int) const;
	int * get(int) const;
	~VectorOfIntArray(void);
	VectorOfIntArray(VectorOfIntArray const &);
};

void VectorOfIntArray::add(int * tab, int size)
{
	pair<int *, int> nowy;
	nowy.first = new int[size];
	for (int i = 0 ; i < size ; ++i)
		nowy.first[i] = tab[i];
	nowy.second = size;
	tabl.push_back(nowy);
}

int VectorOfIntArray::getSize(int rowidx) const
{
	return tabl[rowidx].second;
}

int * VectorOfIntArray::get(int rowidx) const
{
	return tabl[rowidx].first;
}

VectorOfIntArray::~VectorOfIntArray(void)
{
	for (size_t i = 0 ; i < tabl.size() ; ++i)
		delete [] tabl[i].first;
}

VectorOfIntArray::VectorOfIntArray(VectorOfIntArray const & drugi)
{
	for (size_t i = 0 ; i < drugi.tabl.size() ; ++i)
		add(drugi.tabl[i].first, drugi.tabl[i].second);
}

// ------------------------------ [ Zadanie 2 ] ------------------------------

template <class T>
class Array
{
	private:
	T * tab;
	int rozm;

	public:
	Array(void) : tab(NULL), rozm(0) {}
	~Array(void);
	void pushBack(T const &);
	bool reserve(int);
	T & operator[](unsigned) const;
	int Rozm(void) const;   // do 3. zadania
};

template <class T>
Array<T>::~Array(void)
{
	delete [] tab;
}

template <class T>
void Array<T>::pushBack(T const & t)
{
	reserve(rozm + 1);
	tab[rozm - 1] = t;
}

template <class T>
bool Array<T>::reserve(int size)
{
	if (size > rozm)
	{
		T * pom = new T[size];
		for (int i = 0 ; i < rozm ; ++i)
			pom[i] = tab[i];
		delete [] tab;
		tab = pom;
		rozm = size;
		return true;
	}
	else
		return false;
}

template <class T>
T & Array<T>::operator[](unsigned i) const
{
	return tab[i];
}

template <class T>
int Array<T>::Rozm(void) const
{
	return rozm;
}

// ------------------------------ [ Zadanie 3 ] ------------------------------

class Predykat
{
	public:
	bool operator()(int) const;
};

bool Predykat::operator()(int liczba) const
{
	return liczba > 0 && liczba < 10;
}

template <class T, class UnaryPredicate>
void copyIf(Array<T> const & src, Array<T> & target, UnaryPredicate p)
{
	for (int i = 0 ; i < src.Rozm() ; ++i)
		if (p(src[i]))
			target.pushBack(src[i]);
}

// ------------------------------ [ Zadanie 4 ] ------------------------------

class Iterator
{
	private:
	ifstream plik;

	public:
	Iterator(string);
	string get(void);
	void next(void);
	bool good(void);
};

Iterator::Iterator(string nazwa)
{
	plik.open(nazwa.c_str());
}

string Iterator::get(void)
{
	string linia;
	streampos pozycja;
	do
	{
		pozycja = plik.tellg();
		getline(plik, linia);
	}
	while (linia == "");
	plik.seekg(pozycja);
	return linia;
}

void Iterator::next(void)
{
    string slowo;
	getline(plik, slowo);
}

bool Iterator::good(void)
{
	return plik && plik.peek() != EOF;
}

// ------------------------------ [ Zadanie 5 ] ------------------------------

struct Point
{
	double tab[3];

	Point operator+(Point const &);
	bool operator==(Point const &);
};

Point Point::operator+(Point const & drugi)
{
	Point p;
	p.tab[0] = tab[0] + drugi.tab[0];
	p.tab[1] = tab[1] + drugi.tab[1];
	p.tab[2] = tab[2] + drugi.tab[2];
	return p;
}

bool Point::operator==(Point const & drugi)
{
	return tab[0] == drugi.tab[0]
		&& tab[1] == drugi.tab[1]
		&& tab[2] == drugi.tab[2];
}

ostream & operator<<(ostream & s, Point const & p)
{
	return s << "(" << p.tab[0] << ", " << p.tab[1]
			 << ", " << p.tab[2] << ")";
}

// ------------------------------ [ Koniec ] ---------------------------------

int main(void)
{
	// zadanie 3.
	Array<int> a, b;
	Predykat p;
	copyIf<int>(a, b, p);
	// koniec zadania 3.
	return 0;   // O tym nie wolno zapomnieæ. :]
}
