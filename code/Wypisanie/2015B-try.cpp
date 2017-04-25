#include<iostream>
using namespace std;

class A{
public:
    virtual void f(int i){cout<<"A.f:"<<i<<" ";}
    A(int i){f(i);}
};

class B : public A{
    A a;
public:
    void f(int i){cout<<"B.f:"<<i<<" ";}
    B(int i=0):A(-1), a(i){
        if (i<0) throw 0;
        else f(i);
    }
};

int main()
{
    try{
        A *a = new B();
        a->f(1);
        delete a;
    }
    catch (int e){cout<<"Exc";}
    return 0;
}

// wypisze: A.f:-1 A.f:0 B.f:0 B.f:1





