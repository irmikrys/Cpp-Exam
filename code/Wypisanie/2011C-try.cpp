#include <iostream>
using namespace std;
class A{
public:
    virtual void f(int i){cout << i << " ";}
    ~A(){f(1);}
};
class B: public A{
    int x;
    A a;
public:
    B(int _x): x(_x){}
    void f(int i){cout << i << " ";};
    ~B(){f(x);}
};

int main(){
    B b(2); //wypisze 2 1 1
    A*ptr = new B(3); //nic nie zmienia
    delete ptr;
    return 0;
}
//wypisze 1 2 1 1
