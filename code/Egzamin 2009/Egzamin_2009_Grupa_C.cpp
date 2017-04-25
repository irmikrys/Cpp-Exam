#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

// ------------------------------ [ Zadanie 1 ] ------------------------------

class String2String
{
	private:
	vector<pair<string, string> > tab;

	public:
	void add(const char *, const char *);
	void remove(const char *, const char *);
	int find(const char *, int) const;
	void get(const char *, String2String &) const;
	String2String & operator+=(String2String const &);
};

void String2String::add(const char * a, const char * b)
{
	bool jest = false;
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (a == tab[i].first && b == tab[i].second)
		{
			jest = true;
			i = tab.size();
		}
	if (!jest)
		tab.push_back(pair<string, string>(a, b));
}

void String2String::remove(const char * a, const char * b)
{
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (a == tab[i].first && b == tab[i].second)
		{
			tab.erase(tab.begin() + i);
			return;
		}
}

int String2String::find(const char * a, int start) const
{
	for (size_t i = start ; i < tab.size() ; ++i)
		if (a == tab[i].first)
			return i;
	return -1;
}

void String2String::get(const char * a, String2String & target) const
{
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (a == tab[i].first)
			target.add(tab[i].first.c_str(), tab[i].second.c_str());
}

String2String & String2String::operator+=(String2String const & drugi)
{
	for (size_t i = 0 ; i <drugi.tab.size() ; ++i)
		add(drugi.tab[i].first.c_str(), drugi.tab[i].second.c_str());
	return *this;
}

// ------------------------------ [ Zadanie 2 ] ------------------------------

template <class T>
class List
{
	protected:
	struct wezel
	{
		wezel * nast;
		T element;
	};

	wezel * poczatek;

	void czysc(void);

	public:
	List(void) : poczatek(NULL) {}
	~List(void);
	void pushFront(T const &);
	bool getLast(T &) const;
	List & operator=(List const &);
};

template <class T>
void List<T>::czysc(void)
{
	wezel * pom;
	while (poczatek)
	{
		pom = poczatek;
		poczatek = poczatek->nast;
		delete pom;
	}
}

template <class T>
List<T>::~List(void)
{
	czysc();
}

template <class T>
void List<T>::pushFront(T const & t)
{
	wezel * nowy = new wezel;
	nowy->element = t;
	nowy->nast = poczatek;
	poczatek = nowy;
}

template <class T>
bool List<T>::getLast(T & t) const
{
	if (!poczatek)
		return false;
	wezel * pom = poczatek;
	while (pom->nast)
		pom = pom->nast;
	t = pom->element;
	return true;
}

template <class T>
List<T> & List<T>::operator=(List const & drugi)
{
	if (poczatek == drugi.poczatek)
		return *this;
	czysc();
	wezel * dr;
	wezel * pom;
	if (drugi.poczatek)
	{
		poczatek = new wezel;
		poczatek->element = drugi.poczatek->element;
		dr = drugi.poczatek->nast;
		pom = poczatek;
	}
	while (dr)
	{
		pom->nast = new wezel;
		pom = pom->nast;
		pom->element = dr->element;
		dr = dr->nast;
	}
	pom->nast = NULL;
	return *this;
}

// ------------------------------ [ Zadanie 3 ] ------------------------------

template <class T>
class DefaultComparator
{
	public:
	static bool compare(T const & a, T const & b)
	{
		return a == b;
	}
};

template <class T, class Comparator = DefaultComparator<T> >
class Set : public List<T>
{
	public:
	void insert(T const &);
	bool has(T const &) const;
	bool operator<(Set<T> const &) const;
};

template <class T, class Comparator>
void Set<T, Comparator>::insert(const T & t)
{
	if (!has(t))
		pushFront(t);
}

template <class T, class Comparator>
bool Set<T, Comparator>::has(T const & t) const
{
	bool jest = false;
	typename List<T>::wezel * pom = List<T>::poczatek;
	while (pom && !jest)
	{
		if (Comparator::compare(t, pom->element))
			jest = true;
		pom = pom->nast;
	}
	return jest;
}

template <class T, class Comparator>
bool Set<T, Comparator>::operator<(Set<T> const & drugi) const
{
	bool zawiera = true;
	typename List<T>::wezel * pom = List<T>::poczatek;
	while (pom && zawiera)
	{
		if (!drugi.has(pom->element))
			zawiera = false;
		pom = pom->nast;
	}
	return zawiera;
}

// ------------------------------ [ Zadanie 4 ] ------------------------------

class Iterator
{
	private:
	ifstream plik;

	public:
	Iterator(string);
	char get(void);
	void next(void);
	bool good(void);
};

Iterator::Iterator(string nazwa)
{
	plik.open(nazwa.c_str());
}

char Iterator::get(void)
{
	char znak = plik.peek();
	if (!((znak >= '0' && znak <= '9')
	|| (znak >= 'A' && znak <= 'Z')
	|| (znak >= 'a' && znak <= 'z')))
		znak = ' ';
	return znak;
}

void Iterator::next(void)
{
	plik.ignore();
}

bool Iterator::good(void)
{
	return plik && plik.peek() != EOF;
}

// ------------------------------ [ Zadanie 5 ] ------------------------------

class Ulamek
{
	private:
	int licznik;
	int mianownik;

	public:
	Ulamek & operator+=(Ulamek const &);
	bool operator==(Ulamek const &) const;
	friend istream & operator>>(istream &, Ulamek &);
};

Ulamek & Ulamek::operator+=(Ulamek const & drugi)
{
	int mniejszy;
	licznik = licznik * drugi.mianownik + drugi.licznik * mianownik;
	mianownik = mianownik * drugi.mianownik;
	if (licznik < mianownik)
		mniejszy = licznik;
	else
		mniejszy = mianownik;
	for (int i = mniejszy ; i > 0 ; --i)
		if (licznik % i == 0 && mianownik % i == 0)
		{
			licznik /= i;
			mianownik /= i;
		}
	return *this;
}

bool Ulamek::operator==(Ulamek const & drugi) const
{
	return licznik == drugi.licznik && mianownik == drugi.mianownik;
}

istream & operator>>(istream & s, Ulamek & u)
{
	return s >> u.licznik >> u.mianownik;
}

// ------------------------------ [ Koniec ] ---------------------------------

int main(void)
{
	// Pusto. :P
	return 0;   // Ale o tym nie wolno zapomnieæ. :]
}
