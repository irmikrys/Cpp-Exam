/*Uzyj STL. Klasy B, C i D dziedzicza po klasie class A{public: virtual ~A(){}}; Klasa AList dziedziczy po list<A*> i
 * moze przechowywac obiekty klas A, B, C, D. Napisz klase AList:
 * (a) deklaracje i konstruktor
 * (b) destruktor
 * (c) operator przypisania
 * (d) konstruktor kopiujacy
 * (e) operator + */

#include <iostream>
#include <list>
using namespace std;

class A{
public:
    virtual ~A(){}
    virtual A* clone()const{
        return new A(*this);
    }
};

class B: public A{
public:
    A* clone()const{
        return new B(*this);
    }
};

class C: public A{
public:
    A* clone()const{
        return new C(*this);
    }
};

class D: public A{
public:
    A* clone()const{
        return new D(*this);
    }
};

class AList : public list<A*>
{
public:
    AList(){}
    ~AList(){free();}
    AList(const AList& other){copy(other);}
    AList& operator = (const AList& other){if(&other != this) {free(); copy(other);} return *this;}
    friend AList operator + (const AList& l1, const AList& l2);

    void add(const A* a)
    {
        push_back(a->clone());
    }

    friend ostream& operator << (ostream& os, const AList& l){
        os << l.size() << endl;
        for(list<A*>::const_iterator it = l.begin(); it != l.end(); it++){
            os << typeid(*(*it)).name() << endl;
        }
        os << endl;
        return os;
    }
protected:
    void copy(const AList& other){
        for(list<A*>::const_iterator it = other.begin(); it != other.end(); it++){
            add(*it);
        }
    }
    void free(){
        list<A*>::iterator it1 = begin(), it2 = end();
        erase(it1, it2);
        clear();
    }
};

AList operator+(const AList &l1, const AList &l2) {
    AList tmp;
    for(list<A*>::const_iterator it1 = l1.begin(); it1 != l1.end(); it1++) tmp.add(*it1);
    for(list<A*>::const_iterator it2 = l2.begin(); it2 != l2.end(); it2++) tmp.add(*it2);
    return tmp;
}

int main()
{
    AList l1;
    l1.add(new A()); l1.add(new B()); l1.add(new C()); l1.add(new D());
    cout << l1;
    AList l2;
    l2.add(new B()); l2.add(new D()); l2.add(new C()); l2.add(new C()); l2.add(new A());
    cout << l2;
    AList l3;
    l3 = l1 + l2;
    cout << l3;
    l3 = l2;
    cout << l3;
    return 0;
}

