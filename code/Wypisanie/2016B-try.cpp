#include<iostream>
using namespace std;

class A{
public:
    virtual void f(){cout << "~A.f ";}
    virtual ~A(){f();}
};

class B: public A{
public:
    void f(){cout << "~B.f ";}
    ~B(){f();}
};

B b;

int main(){
    A* a = new B();
    cout << "M ";
    delete a;
    return 0;
}
//wypisze: M ~B.f ~A.f ~B.f ~A.f
