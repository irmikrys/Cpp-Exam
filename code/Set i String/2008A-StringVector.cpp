/*Korzystajac z kontenera STL vector zaimplementuj klase StringVector przechowujaca wskazniki typu char*. Pamiec dla
 * tekstow jest przydzielona na stercie. Zaimplementuj:
 * (a) konstruktor
 * (b) konstruktor kopiujacy
 * (c) destruktor
 * (d) operator przypisania
 * (e) funkcje void add(const char* txt)*/

 #include<iostream>
 #include<vector>
 using namespace std;

class StringVector
{
public:
    vector<char*> tab;

    StringVector();
    StringVector(const StringVector& other);
    ~StringVector();
    StringVector& operator = (const StringVector& other);
    void add(const char* txt);

    friend ostream& operator << (ostream& os, const StringVector& sv){
        os << "rozmiar: " << sv.tab.size() << endl;
        for(vector<char*>::const_iterator it = sv.tab.begin(); it != sv.tab.end(); it++){
            os << *it << endl;
        }
        os << endl;
        return os;
    }

protected:
    void copy(const StringVector& other){
        tab.reserve(other.tab.size());
        for(int i = 0; i < other.tab.size(); i++)
        {
            tab.push_back(other.tab[i]);
            //add(other.tab[i]);  <- albo tak
        }
    }
    void free(){
        vector<char*>::iterator it1 = tab.begin(), it2 = tab.end();
        tab.erase(it1, it2);
    }
};

StringVector::StringVector() {
    tab.clear();
}

StringVector::StringVector(const StringVector &other) {
    copy(other);
}

StringVector::~StringVector() {
    free();
}

StringVector &StringVector::operator=(const StringVector &other) {
    if(&other != this)
    {
        free();
        copy(other);
    }
    return *this;
}

void StringVector::add(const char *txt) {
    char * tmp = new char [strlen(txt)];
    strcpy(tmp, txt);                    //kopiuje lancuch znakow do tablicy znakow
    tab.push_back(tmp);
}

int main(){
    StringVector sv1;
    sv1.add("Irmina");
    sv1.add("Rebi");
    sv1.add("Janusz");
    cout << sv1;

    StringVector sv2;
    sv2.add("Anna");
    sv2.add("Kacper");
    cout << sv2;

    StringVector sv3(sv2);
    cout << sv3;

    sv2 = sv1;
    cout << sv2;

    return 0;
}







