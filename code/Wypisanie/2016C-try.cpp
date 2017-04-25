#include<iostream>
using namespace std;

class A
{
public:
    virtual void f(){cout<<"A.f ";}
    A(){f();}
    ~A(){cout<<"~A.f ";}
};

class B : public A{
public:
    A*a;
    void f(){cout<<"B.f";}
    B(){
        f();
        a = new A();
        throw 0;
    }
};

int main()
{
    try{
        A*a = new B();
        delete a;           //nie wykona sie
    }
    catch(...)          //wylapie throw 0 z konstruktora, ktory sie nie dokonczy wiec zniszczy obiekt;
                        // gdyby by³o bez gwiazdki (nie A*a tylko A a)
    {cout<<"Exc ";}
    return 0;
}

//wypisze A.f B.f A.f ~A.f Exc


