#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ------------------------------ [ Zadanie 1 ] ------------------------------

class StringToInt
{
	private:
	vector<pair<string, unsigned> > tab;

	public:
	int get(const char *) const;
	void add(const char *);
	void remove(const char *);
	StringToInt operator+(StringToInt const &);
	bool operator<=(StringToInt const &);
};

int StringToInt::get(const char * key) const
{
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (tab[i].first == key)
			return tab[i].second;
	return 0;
}

void StringToInt::add(const char * key)
{
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (tab[i].first == key)
		{
			++tab[i].second;
			return;
		}
}

void StringToInt::remove(const char * key)
{
	for (size_t i = 0 ; i < tab.size() ; ++i)
		if (tab[i].first == key && tab[i].second > 0)
		{
			--tab[i].second;
			return;
		}
}

StringToInt StringToInt::operator+(StringToInt const & drugi)
{
	StringToInt s;
	bool ok;
	for (size_t i = 0 ; i < tab.size() ; ++i)
		s.tab.push_back(tab[i]);
	for (size_t i = 0 ; i < drugi.tab.size() ; ++i)
	{
		ok = true;
		for (size_t j = 0 ; j < tab.size() ; ++j)
			if (tab[j].first == drugi.tab[i].first)
				ok = false;
		if (ok)
			s.tab.push_back(drugi.tab[i]);
	}
	return s;
}

bool StringToInt::operator<=(StringToInt const & drugi)
{
	if (tab.size() > drugi.tab.size())
		return false;
	bool ok;
	for (size_t i = 0 ; i < tab.size() ; ++i)
	{
		ok = false;
		for (size_t j = 0 ; j < drugi.tab.size() ; ++j)
			if (tab[i].first == drugi.tab[j].first)
			{
				ok = true;
				if (tab[i].second > drugi.tab[j].second)
					return false;
				j = drugi.tab.size();
			}
		if (!ok)
			return false;
	}
	return true;
}

// ------------------------------ [ Zadanie 2 ] ------------------------------

template <class T>
class List
{
	public:
	struct wezel
	{
		wezel * nast;
		wezel * poprz;
		T element;
	};

    private:
	wezel * poczatek;
	wezel * koniec;

	public:
	List(void) : poczatek(NULL), koniec(NULL) {}
	~List(void);
	wezel * Poczatek(void) const;
	void pushBack(T const &);
	void deleteFront(void);
	List(List const &);
};

template <class T>
typename List<T>::wezel * List<T>::Poczatek(void) const
{
    return poczatek;
}

template <class T>
List<T>::~List(void)
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
void List<T>::pushBack(T const & t)
{
	if (!poczatek)
	{
		poczatek = new wezel;
		poczatek->element = t;
		poczatek->poprz = NULL;
		poczatek->nast = NULL;
		koniec = poczatek;
	}
	else
	{
		koniec->nast = new wezel;
		koniec->nast->element = t;
		koniec->nast->poprz = NULL;
		koniec->nast->nast = NULL;
		koniec = koniec->nast;
	}
}

template <class T>
void List<T>::deleteFront(void)
{
	if (poczatek)
	{
		wezel * pom = poczatek;
		poczatek = poczatek->nast;
		delete pom;
		if (!poczatek)
			koniec = NULL;
	}
}

template <class T>
List<T>::List(List const & drugi)
{
	wezel * dr = NULL;
	wezel * pom;
	if (drugi.poczatek)
	{
		poczatek = new wezel;
		*poczatek = *drugi.poczatek;
		dr = drugi.poczatek->nast;
		pom = poczatek;
	}
	while (dr)
	{
		pom->nast = new wezel;
		pom = pom->nast;
		*pom = *dr;
		dr = dr->nast;
	}
	pom->nast = NULL;
}

// ------------------------------ [ Zadanie 3 ] ------------------------------

class Wypisz
{
	public:
	void operator()(int) const;
};

void Wypisz::operator()(int liczba) const
{
	cout << liczba << "\n";
}

template <class T, class UnaryFunction>
void forEach(List<T> const & l, UnaryFunction f)
{
	typename List<T>::wezel * pom = l.Poczatek();
	while (pom)
	{
		f(pom->element);
		pom = pom->nast;
	}
}

// ------------------------------ [ Zadanie 4 ] ------------------------------

class Iterator
{
	private:
	stringstream strumien;

	public:
	Iterator(const char *);
	string get(void);
	void next(void);
	bool good(void);
};

Iterator::Iterator(const char * t)
{
	strumien << t;
}

string Iterator::get(void)
{
	string slowo;
	streampos pozycja;
	pozycja = strumien.tellg();
	strumien >> slowo;
	strumien.seekg(pozycja);
	return slowo;
}

void Iterator::next(void)
{
	string slowo;
	strumien >> slowo;
}

bool Iterator::good(void)
{
	return strumien.peek() != EOF;
}

// ------------------------------ [ Zadanie 5 ] ------------------------------

class Time
{
	private:
	int hour;
	int min;
	int sec;

	public:
	Time & operator++(void);
	bool operator<(Time const &);
	Time & operator+=(Time const &);
};

Time & Time::operator++(void)
{
	++sec;
	if (sec > 59)
	{
		sec %= 60;
		++min;
		if (min > 59)
		{
			min %= 60;
			++hour;
			hour %= 24;
		}
	}
	return *this;
}

bool Time::operator<(Time const & drugi)
{
	return (hour == drugi.hour ?
		   (min == drugi.min ? sec < drugi.sec : min < drugi.min)
		   : hour < drugi.hour);
}

Time & Time::operator+=(Time const & drugi)
{
	hour += drugi.hour;
	min += drugi.min;
	sec += drugi.sec;
	if (sec > 59)
	{
		sec %= 60;
		++min;
	}
	if (min > 59)
	{
		min %= 60;
		++hour;
	}
	hour %= 24;
	return *this;
}

// ------------------------------ [ Koniec ] ---------------------------------

int main(void)
{
	// zadanie 3.
	List<int> a;
	Wypisz w;
	forEach<int>(a, w);
	// koniec zadania 3.
	return 0;   // O tym nie wolno zapomnieæ. :]
}
