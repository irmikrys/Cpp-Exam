#include <iostream>
#include <map>
#include <string>
#include <list>

using namespace std;

class Slownik
{
public:
    map<string, list<string> > obj;
    void dodaj(const char* term, const char* znaczenie);
    list<string> & szukaj(const char* term);
    void usun(const char* term);
    void usun(const char* term, const char* znaczenie);
    friend ostream & operator<<(ostream & strumyk, const Slownik & tmp);
};

/////////////////wypisuje slownik////////////////////////////////////////
ostream & operator<<(ostream & strumyk, const Slownik & tmp)
{
    map<string, list<string> >::const_iterator it1;
    list<string>::const_iterator it2;
    for(it1 = tmp.obj.begin(); it1 != tmp.obj.end(); ++it1)
    {
        strumyk << "TERMIN: " << it1->first << endl;
        for(it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
        {
            strumyk << *it2 << " ";
        }
        strumyk << "\nxxxxxxxxxx" << endl;
    }
    return strumyk;
}

/////////dodaje znaczenie do terminu term////////////////////
void Slownik::dodaj(const char* term, const char* znaczenie)
{
    map<string, list<string> >::iterator it;
    list<string> listaZ;
    for(it=obj.begin(); it!=obj.end(); it++)
    {
        if(it->first == term)
        {
            it->second.push_back(znaczenie);
            break;
        }
    }
    if(it == obj.end())
    {
        listaZ.push_back(znaczenie);
        obj.insert(pair<string, list<string> >(term, listaZ));
    }
}

///////zwraca liste znaczen terminu term /////////////////////
list<string> & Slownik::szukaj(const char* term)
{
    return obj.at(term);
    /*
    map<string, list<string> >::iterator it;
    for(it = obj.begin(); it != obj.end(); ++it)
    {
        if(it->first == term)
        {
            return it->second;
        }
    }
    */
}

//////////usuwa termin i wszystkie znaczenia//////////////////
void Slownik::usun(const char* term)
{
    map<string, list<string> >::iterator it;
    for(it=obj.begin(); it!=obj.end(); it++)
    {
        if(it->first == term)
        {
            obj.erase(it);
        }
    }
}

///////usuwa wybrane znaczenie slowa term/////////////////////
void Slownik::usun(const char* term, const char* znaczenie)
{
    map<string, list<string> >::iterator it;
    for(it=obj.begin(); it!=obj.end(); it++)
    {
        if(it->first == term)
        {
            it->second.remove(znaczenie);
            if(it->second.size()<1) obj.erase(it);
        }
    }
}

int main()
{
    Slownik slownik1;

    slownik1.dodaj("english", "angielski");
    slownik1.dodaj("english", "angielka");
    slownik1.dodaj("french", "francuski");
    slownik1.dodaj("french", "francuz");
    slownik1.dodaj("french", "yolo");

    list<string> lista_tmp;

    lista_tmp = slownik1.szukaj("french");

    for(list<string>::const_iterator it = lista_tmp.begin(); it != lista_tmp.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << slownik1 << endl;

    slownik1.usun("french", "yolo");

    lista_tmp = slownik1.szukaj("french");
    for(list<string>::const_iterator it = lista_tmp.begin(); it != lista_tmp.end(); ++it)
    {
        cout << *it << endl;
    }
    cout<<slownik1;

    //slownik1.szukaj("french");
    //slownik1.szukaj("english");
    //slownik1.usun("english");
    cout<<"-----------"<<endl;
    return 0;
}
