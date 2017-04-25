/*Uzyj STL. Klasa Directory zawiera dowolna liczbe obiektow klas File i Directory. Obie klasy dziedzicza po
 * abstrakcyjnej klasie DirElement. Zarowno plik(File) jak i folder(Directory) maja nazwe (tekst). Do przechowywania
 * podobiektow w klasie Directory wykorzystaj wybrany kontener z biblioteki STL, w ktorym umieszczone sa wskazniki typu
 * DirElement*.
 * (a) zadeklaruj i zaimplementuj klasy DirElement, File i Directory
 * Dla klasy Directory zadeklaruj i zaimplementuj:
 * (b) bool add (DirElement* e) - dodaje element, ale katalog musi miec obiekty o UNIKALNYCH nazwach
 * (c) destruktor
 * (d) bool delete(const char* name) - znajduje i usuwa element o nazwie name*/

#include <iostream>
#include <vector>
using namespace std;

class DirElement
{
public:
    string name;
    DirElement(){}
    DirElement(const char* n): name(n){}
    virtual ~DirElement(){}
    virtual DirElement* clone()const = 0;
};

class File: public DirElement
{
public:
    File(){}
    DirElement* clone()const {
        return new File(*this);
    }

    File(const char* _name):DirElement(_name){} //taki konstruktor ze wzgledu na dziedziczenie string name!
};

class Directory: public DirElement
{
public:
    vector<DirElement*> dir;

    DirElement* clone()const{
        return new Directory(*this);
    }

    Directory(){}
    Directory(const char* _name):DirElement(_name){}

    bool add(DirElement* e){
        for(vector<DirElement*>::const_iterator it = dir.begin(); it != dir.end(); it++){
            if((*it)->name == e->name) return false;        // taki zapis, bo DirElement** (it) to typ !!!
        }
        dir.push_back(e->clone());
        return true;
    }

    ~Directory(){
        vector<DirElement*>::iterator it1 = dir.begin(), it2 = dir.end();
        dir.erase(it1, it2);
        dir.clear();
    }

    bool deleteEl(const char* name){
        for(vector<DirElement*>::iterator it = dir.begin(); it != dir.end(); it++){
            if((*it)->name == name) {dir.erase(it); return true;}
        }
        return false;
    }

    friend ostream& operator << (ostream& os, const Directory& d){
        os << d.dir.size() << endl;
        for(vector<DirElement*>::const_iterator it = d.dir.begin(); it != d.dir.end(); it++){
            os << typeid(*(*it)).name() << " " << (*it)->name << endl;
        }
        os << endl;
        return os;
    }
};

int main()
{
    Directory dir1("Home"); Directory dir2("Irmina"); Directory dir3("cpp"); Directory dir4("Documents");
    File f1("cpp1"); File f2("cpp2"); File f3("cpp3");

    Directory defaultDir;
    defaultDir.name = "Default";
    defaultDir.add(dir1.clone());defaultDir.add(dir2.clone());defaultDir.add(dir3.clone());defaultDir.add(f2.clone());
    cout << defaultDir;

    defaultDir.add(f3.clone()); defaultDir.add(f2.clone());
    defaultDir.add(dir2.clone()); //add dziala
    cout << defaultDir;

    defaultDir.deleteEl("cpp2");
    defaultDir.deleteEl("Home");
    defaultDir.deleteEl("cp1");
    cout << defaultDir; //delete dziala

    return 0;
}


