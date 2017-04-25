#include<iostream>
#include<map>
#include<string>
#include<list>

using namespace std;

class Slownik
{
public:
    multimap<string, string> obj;
    void dodaj(const char* term, const char* znaczenie);
    list<string> szukaj(const char* term);
    void usun(const char* term);
    void usun(const char* term, const char* znaczenie);
};

/////////dodaje znaczenie do terminu term////////////////////
void Slownik::dodaj(const char* term, const char* znaczenie)
{
    obj.insert( pair<string,string>(term,znaczenie));
}

///////zwraca liste znaczen terminu term /////////////////////
list<string> Slownik::szukaj(const char* term)
{
    list<string> values;

    for (multimap<string, string>::iterator it = obj.begin(); it != obj.end(); ++it)
    {
        if (it->first == term)
            values.push_back((*it).second);
    }

    return values;
}

//////////usuwa termin i wszystkie znaczenia//////////////////
void Slownik::usun(const char* term)
{
    multimap<string, string>::iterator it;
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
    map<string, string>::iterator it;
    for(it=obj.begin(); it!=obj.end(); it++)
    {
        if(it->first == term)
        {
            obj.erase(znaczenie);
            if(it->second.size()<1) obj.erase(it);
        }
    }
}

int main()
{
    Slownik slownik1;
    slownik1.dodaj("english", "angielski");
    slownik1.dodaj("english", "angielka");
    cout<<"--------------------"<<endl;
    slownik1.dodaj("french", "francuski");
    slownik1.dodaj("french", "francuz");
    cout<<"------"<<endl;
    slownik1.dodaj("french", "yolo");
    cout<<"--------------"<<endl;

    list<string>lista = slownik1.szukaj("french");

    for(list<string>::iterator list_iter = lista.begin();
        list_iter != lista.end(); list_iter++)
    {
        cout<<*list_iter<<endl;
    }

    cout<<"------------------------"<<endl;
    slownik1.usun("french", "yolo");
    cout<<"------------------------------"<<endl;
    slownik1.szukaj("french");
    slownik1.szukaj("english");
    slownik1.usun("english");
    cout<<"-----------"<<endl;
    return 0;
}
