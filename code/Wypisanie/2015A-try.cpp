#include<iostream>
using namespace std;

class A{
public:
    virtual void f(){cout<<"A.f ";}
    A(){f();}
};

class B : public A{
public:
    void f()
    {cout<<"B.f ";}
    B(int i=0)
    {f();
     if (i) throw i;}
};

B b; // !!!

int main()
{
    try{
        B b(-1); //rzuci -1 bo tylko jak bd zero to bd falszywy if
        A *a = new A();
    }
    catch (int e){cout<<"Exc";}
    return 0;
}

// wypisze A.f B.f A.f B.f Exc






