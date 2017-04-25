#include <iostream>
using namespace std;

class A
{
public:
    virtual void f(){cout << "A.f";}
    A(){f();}
};

class B : public A{
public:
    void f(){cout<<"B.f";}
    B(){f();}
};

class C : public A{
public:
    B b;
    void f(){cout<<"C.f";}
    C(){throw -1;}
};

int main()
{
    try{
        B b;
        C c;
    } catch(...){
        cout<<"Exc";
    }
    return 0;
}
// wypisze A.f B.f A.f A.f B.f Exc
