#include <iostream>
using namespace std;

class A
{
public:
    virtual void f(){cout << "A.f ";}
    ~A(){f();}
};

class B
{
    A a;
public:
    void f(){cout << "B.f ";}
    B(){throw -1;}
    ~B(){f();}
};

int main()
{
    try{
        B b;
    } catch(...) {cout << "Exc";}
    return 0;
}

//wypisze: A.f Exc -> A.f bo przy tworzeniu A a gdy uruchomimy konstruktor i Exc bo wyrzuci -1