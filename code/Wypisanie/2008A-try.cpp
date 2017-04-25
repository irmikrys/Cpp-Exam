#include <iostream>
using namespace std;

class {
public:
    virtual void f(){cout << "A.f ";}
    A(){f();}
};

class B{
    A a;
public:
    void f(){cout << "B.f ";}
    B(){f();}
};

A a;

int main(){
    B b;
    cout << "M";
    return 0;
}

//wypisze: A.f A.f B.f M, bo tworzy obiekt A globalnie (A.f), potem obiekt B - konstruktor tworzy obiekt A a (A.f) i
//potem wypisuje B.f, na koniec M ;)


