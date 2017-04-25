/*Klasa Folder zawiera dowolna sekwencje obiektow nalezacych do klas File lub Folder. Obiekty wystepuja w dowolnej
 * kolejnosci i sa roznych typow. Klasa Folder dziedziczy po File. Pliki i katalogi maja nazwe (tekst). Do przechowywa-
 * nia podobiektow w klasie Folder wykorzystaj wybrany kontener STL.
 * (a) zadeklaruj i zaimplementuj klasy File i Folder
 * Dla klasy Folder zaimplementuj
 * (b) konstruktor kopiujacy
 * (c) destruktor
 * (d) operator przypisania */

#include <iostream>
#include <vector>
using namespace std;

class File
{
public:
    string name;

    virtual File* clone()const{
        return new File(*this);
    }

    File(){}
    File(const char* n): name(n){}
    virtual ~File(){}
};

class Folder: public File
{
public:
    vector<File*> kat;

    Folder(){}
    Folder(const char* _n): File(_n){}
    Folder(const Folder& other){copy(other);}
    ~Folder(){free();}
    Folder& operator=(const Folder& other){if(&other != this){free(); copy(other);} return *this;}

    File* clone()const{
        return new Folder(*this);
    }

    void add(const File* f){
        for(vector<File*>::const_iterator it = kat.begin(); it != kat.end(); it++){
            if((*it)->name == f->name) return;
        }
        kat.push_back(f->clone());
    }
    friend ostream& operator << (ostream& os, const Folder& f){
        os << f.name << ": " << f.kat.size() << endl;
        for(vector<File*>::const_iterator it = f.kat.begin(); it != f.kat.end(); it++)
            os << typeid(*(*it)).name() << " " << (*it)->name << endl;
        os << endl;
        return os;
    }
protected:
    void free(){
        if(kat.size()){
            for(vector<File*>::iterator it = kat.begin(); it != kat.end(); it++) delete *it;
            kat.erase(kat.begin(), kat.end());
            kat.clear();
        }
    }

    void copy(const Folder& other){
        kat.reserve(other.kat.size());
        for(vector<File*>::const_iterator it = other.kat.begin(); it != other.kat.end(); it++) add((*it)->clone());
    }
};

int main()
{
    File f1("cpp"); File f2("jimp.doc"); File f3("doc.txt");
    Folder kat1("Home"); Folder kat2("Documents"); Folder kat3("Downloads"); Folder kat4("Photos");

    File* kk = kat1.clone();
    cout << kk->name << endl << endl;

    Folder default1("Default1");
    default1.add(f1.clone()); default1.add(kat1.clone()); default1.add(kat2.clone()); default1.add(f3.clone());
    cout << default1;

    Folder default2("Default2");
    default2.add(f3.clone()); default2.add(f2.clone());
    cout << default2;

    default1 = default2;
    cout << default1;

    return 0;
}
