#include<iostream>
using namespace std;

class A
{
public:
    virtual void f()
    {cout<<"A.f";}
    A(){f();}
};

class B : public A{
public:
    B(){throw -1;}
    void f(){cout<<"B.f";}
    ~B(){f();}
};

class C : public A{
    B b;
    void f(){cout<<"C.f";}
    ~C(){f();}
};

int main()
{
    try
    {
        A *a = new C();
        delete a;
    }
    catch(...)
    {
        cout<<"Exc";
    }
    return 0;
}
//wypisze A.f A.f Exc
