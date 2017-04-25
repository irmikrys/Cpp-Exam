#include <iostream>
using namespace std;

class A
{
public:
    virtual void f(){cout << "A.f ";}
    ~A(){f();}
};

class B: public A
{
public:
    void f(){cout << "B.f ";}
    ~B(){f();}
};

B b;

int main()
{
    A* a = new B();
    delete a;
    cout << "M ";
    return 0;
}

//wypisze: A.f M B.f A.f -> wywola sie destruktor klasy A bo ma virtual, wypisze M i zniszczy obiekt globalny, czyli
//wypisze B.f (klasa potomna) A.f (klasa macierzysta)

