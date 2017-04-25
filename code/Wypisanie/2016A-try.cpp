#include <iostream>
using namespace std;
class A{
    int i;
public:
    A(int _i = 0): i(_i){cout << "A" << i << " ";}
    ~A(){cout << "~A" << i << " ";}
};
class B: public A{
    int x;
    A a;
public:
    B(int _x):A(1), x(_x){ }
    ~B(){cout << "~B" << x << " ";}
};
B b(5);

int main(){
    A*ptr = new B(3);
    delete ptr;
    return 0;
}
//wypisze A1 A0 A1 A0 ~A1 ~B5 ~A0 ~A1 -> nie wypisuje destruktora dla B
//bo A nie ma wirtualnego, wiec bierze swoj
