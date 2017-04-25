#include <iostream>
using namespace std;
class A{
public:
    virtual void f(){cout << "~A.f ";}
    ~A(){f();}
};
class B: public A{
public:
    A*a;
    void f(){cout << "~B.f ";}
    B(){a = new A(); throw 0;}
    ~B(){f(); delete a;}
};
B b;

int main(){
    try{
        B*ptr = new B();
        delete ptr;
    } catch(...) {cout << " Exc ";}
    return 0;
}
//wypisze
