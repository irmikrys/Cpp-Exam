#include<iostream>
using namespace std;
class A{
public:
    virtual void f(){cout << "A.f ";}
    ~A(){f();}
};
class B: public A{
public:
    void f(){cout << "B.f ";}
    B(){throw 0;}
    ~B(){f();}
};
int main(){
try{
    B* ptr = new B();
    delete ptr;
    }
    catch(...){cout << " Exc ";}
}
//wypisze: A.f Exc -> konstruktor klasy macierzystej nic nie wypisze,
//tworzac B() wyrzuca wyjatek, ale zanim wyrzuci to wywoluje destruktor
//klasy macierzystej bo jeszcze B() nie stworzyl
