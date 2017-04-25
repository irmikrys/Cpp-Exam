#include <iostream>
using namespace std;

class A
{
public:
    A() {f();}
    virtual ~A() {cout << "~A ";}
    void f() {cout << "A.f ";}
};

class B{
public:
    B(){f();}
    ~B(){cout << "~B ";}
    void f(){printf("B.f ");}
};

class C : public A, public B{
public:
    C(){f();}
    ~C(){printf("~C ");}
    void f(){printf("C.f ");}
};

int main()
{
    A* a = new C();
    B* b = new C();
    delete a;
    delete b;
    return 0;
}

//wypisze: A.f B.f C.f A.f B.f C.f ~C ~B ~A ~B (kolejnosc dziedziczenia ma znaczenie)




