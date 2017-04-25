/*Korzystajac z kontenera STL list zaimplementuj klase StringSet przechowujaca unikalne teksty w postaci wskaznikow typu
 * char*. Pamiec dla tekstow jest przydzielona na stercie. Zaimplementuj:
 * (a) konstruktor
 * (b) destruktor
 * (c) funkcje void insert(const char* txt) - wstawia tekst, sprawdzajac wczesniej czy jest umieszczony w kontenerze
 * (d) funkcje bool exist(const char* txt) - sprawdza czy tekst jest w kontenerze
 * (e) operator <= - sprawdza czy jeden zbior zawiera sie w drugim*/

 #include<iostream>
 #include<list>
 using namespace std;

class StringSet
{
public:
    list<char*> zbior;

    StringSet();
    ~StringSet();
    void insert(const char* txt);
    bool exist(const char* txt)const;
    bool operator <= (const StringSet& other);

    friend ostream& operator <<(ostream& os, const StringSet& s){
        os << "Elementow: " << s.zbior.size() << endl;
        for(list<char*>::const_iterator it = s.zbior.begin(); it != s.zbior.end(); it++){
            os << *it << endl;
        }
        os << endl;
        return os;
    }

};

StringSet::StringSet() {

}

StringSet::~StringSet() {
    list<char*>::iterator it1 = zbior.begin(), it2 = zbior.end();
    zbior.erase(it1, it2);
    //zbior.clear();
}

void StringSet::insert(const char *txt) {
    if(this->exist(txt)) return;
    char * tmp = new char [strlen(txt)];
    strcpy(tmp, txt);
    zbior.push_back(tmp);
}

bool StringSet::exist(const char *txt) const {
    for(list<char*>::const_iterator it = zbior.begin(); it != zbior.end(); it++)
        {
            cout << *it << " " << txt << endl;
            if(*it == txt)
                return true;
        }
    return false;
}

bool StringSet::operator<=(const StringSet &other) {
    if(zbior.size() > other.zbior.size()) return false;
    for(list<char*>::const_iterator it = zbior.begin(); it != zbior.end(); it++)
        if(!other.exist(*it)) return false;
    return true;
}

int main()
{
    StringSet set1;
    set1.insert("Irmina"); set1.insert("Rebi"); set1.insert("Anna"); set1.insert("Rebi");
    cout << set1;

    StringSet set2;
    set2.insert("Anna"); set2.insert("Rebi");
    cout << set2;

    if(set2 <= set1) cout << "Zawiera sie" << endl << endl; else cout << "Nie zawiera sie" << endl << endl;

    set1.~StringSet();
    cout << set1;

    return 0;
}




