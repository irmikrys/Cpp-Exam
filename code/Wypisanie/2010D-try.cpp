#include<iostream>
using namespace std;
class A{
public:
    virtual void f(){cout << "A.f ";}
    A(){f();}
};
class B: public A{
public:
    void f(){cout << "B.f ";}
    B(int i = 0){
        if(i >= 0) throw -1;
        else f();
        }
};

B b;

int main(){
    try{
        A*a = new B(-1);
        delete a;
    } catch(int e) {cout << "Exc ";
    }
} //wypisze A.f i program sie [posypie po zlapaniu inta
