/*[30] Zaimplementuj klasę StringSet (zbior) przechowujaca pojedyncze instancje tekstow.
 *
 * (a) deklaracja, konstruktor, destruktor
 * (b) void insert(const char* t) - dodaje element do zbioru
 * (c) bool has(const char* t) - sprawdza czy element nalezy do zbioru
 * (d) operatorem == do porownania, czy zbiory sa rowne
 * (e) operatorem < do sprawdzenia czy jeden zbior zawiera sie w drugim
 * (f) operatorem * do wyznaczania przeciecia zbiorow
 *
 * Uzyj dowolnego kontenera STL (poza szablonem set).
 */

#include <iostream>
#include <list>

using namespace std;


class StringSet
{
public:
    list<string> zbior;

    StringSet();
    ~StringSet();
    void insert(const char*t);
    bool has(const char*t)const;
    bool operator==(StringSet const& other);
    bool operator<(StringSet const& other);
    StringSet operator*(StringSet const& other);

    void wypisz();
};

StringSet::StringSet()
{
    zbior.clear();
}

StringSet::~StringSet()
{
    zbior.clear();
}

void StringSet::insert(const char *t)
{
    if(this->has(t)) return;
    else
    {
        zbior.push_back(t);
        zbior.sort();
    }
}

bool StringSet::has(const char *t)const
{
    list<string>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(*it == t)    return true;
    }
    return false;
}

bool StringSet::operator==(StringSet const&other)
{
    if(other.zbior.size() != zbior.size())
    {
        cout << "nie rowne" << endl << endl;
        return false; //  else jest zbedne bo tu masz return
    }
        list<string>::const_iterator it1, it2;
        for(it1 = other.zbior.begin(), it2 = zbior.begin(); it1 != other.zbior.end(); it1++, it2++)
                if(*it1 != *it2)
                {
                    cout << "nie rowne" << endl << endl;
                    return false;
                }
        cout << "rowne" << endl << endl;
        return true;
}

bool StringSet::operator<(StringSet const&other)
{
    list<string>::const_iterator it, it1 = zbior.end(); // tu musisz zainicjowac it1 na koniec zbioru bo moze nie wejsc do ifa ponizej i wtedy it1 bd niezainicjalizowane i bd zle dzialac

    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(!(other.has((*it).c_str())))
        {
            it1 = it;
            break;
        }
    }
    if(it1 != zbior.end())
    {
        cout << "nie zawiera sie" << endl;
        return false; // tu tez else zbedne
    }

        cout << "zawiera sie" << endl;
        return true;
}

StringSet StringSet::operator*(StringSet const&other)
{
    StringSet iloczyn;
    list<string>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        if(other.has((*it).c_str()))
        {
            iloczyn.zbior.push_back(*it);
        }
    }
    return iloczyn;
}

void StringSet::wypisz()
{
    list<string>::const_iterator it;
    for(it = zbior.begin(); it != zbior.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;
}


int main()
{
    StringSet zbior1;
    zbior1.insert("Irmis");
    zbior1.insert("Kacpi");
    zbior1.insert("Drops");
    zbior1.wypisz();

    StringSet zbior2;
    zbior2.insert("Irmis");
    zbior2.insert("Drops");
    zbior2.insert("lolollo");
    zbior2.insert("Kacpi");
    zbior2.wypisz();

    zbior1 == zbior2;

    StringSet zbior3 = zbior1 * zbior2;
    zbior3.wypisz();

    zbior1 < zbior2;

    return 0;
}
