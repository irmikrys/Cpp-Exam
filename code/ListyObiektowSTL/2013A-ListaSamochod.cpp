/*Klasa Samochod ma atrybuty: string marka, string model, int rocznik. Napisz klase LS(lista samochodow)
 * (a) zadeklaruj wymagane struktury danych
 * (b) napisz operator << pozwalajacy na zapis obiektu klasy LS do strumienia ostream
 * (c) napisz operator >> umozliwiajacy odczyt obiketu klasy LS ze strumienia istream
 * (d) void LS::szukaj(int start, int end, const char* txt, list<Samochod>& result) - znajduje wszystkie samochody,
 *     ktorych rocznik zawiera sie pomiedzy start i end oraz marka lub model zawieraja lancuch txt.
 * Uzyj dowolnego kontenera STL.*/

#include <iostream>
#include <list>
#include <string>

using namespace std;

class NoBeginning{};

class Samochod
{
public:
    string marka;
    string model;
    int rocznik;

    Samochod(){}
    Samochod(const char* ma, const char* mo, int ro):marka(ma), model(mo), rocznik(ro){}
};

class LS
{
public:
    list<Samochod> lista;

    void add(const char* marka, const char* model, int rocznik)
    {
        list<Samochod>::const_iterator it;
        for(it = lista.begin(); it != lista.end(); it++)
        {
            if(it->marka == marka && it->model == model && it->rocznik == rocznik) return;
        }
        lista.push_back(Samochod(marka, model, rocznik));
    }

    void szukaj(int start, int end, const char* txt, list<Samochod>& result);
    friend ostream& operator << (ostream& os, const LS& l);
    friend istream& operator >> (istream& is, LS& l);
};

void LS::szukaj(int start, int end, const char *txt, list<Samochod>& result)
{
    list<Samochod>::const_iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if(it->rocznik <= end && it->rocznik >= start)
            if(it->marka.find(txt) <= it->marka.length() || it->model.find(txt) <= it->model.length())
                result.push_back(*it);
    }
}

ostream &operator<<(ostream &os, const LS &l)
{
    os << "#begin" << endl << endl;
    os << "MARKA" << "\t \t" << "MODEL" << "\t \t" << "ROCZNIK" << endl;
    for(list<Samochod>::const_iterator it = l.lista.begin(); it != l.lista.end(); it++)
    {
        os << it->marka << "\t \t" << it->model << "\t \t" << it->rocznik << endl;
    }
    os << endl;
    os << "#end" << endl;
    return os;
}

istream &operator>>(istream &is, LS &l)
{
    string a;
    string ma, mo;
    int r;
    is >> a;
    if(a != "#begin") throw NoBeginning();
    for( ; ; )
    {
        is >> ma;
        if(!is) break; //moglo sie skonczyc
        if(ma == "#end") break;

        is >> mo;
        is >> r;
        Samochod s;
        s.marka = ma; s.model = mo; s.rocznik = r;
        l.lista.push_back(s);
    }
    return is;
}


int main()
{
    LS ls;
    ls.add("Honda", "Civice", 2009);
    ls.add("Toyota", "Camry", 1994);
    ls.add("Ford", "Mondeo", 2002);
    ls.add("Subaru", "Impreza", 2007);

    cout << ls;

    LS res;
    ls.szukaj(2002, 2008, "e", res.lista);
    cout << res;

    LS ls2;
    try {cin >> ls2;} catch(...){cout << "NoBeginning!" << endl;} cout << ls2;

    return 0;
}

