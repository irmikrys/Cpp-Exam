#include<iostream>
using namespace std;
class A{
public:
    virtual void f() {cout << "A.f ";}
    ~A(){f();}
};
class B: public A{
    A a;
public:
    void f(){cout << "B.f ";}
    B(){throw -1;}
    ~B(){f();}
};
int main(){
    try{
        B b;
    } catch (...) {cout << " Exc ";}
    return 0;
}
//wypisze A.f A.f Exc -> po wyrzuceniu wyjatku w konstruktorze
//zniszczy obiekt A() ktory tam powstal i wywyola destruktor dla
//klasy bazowej

