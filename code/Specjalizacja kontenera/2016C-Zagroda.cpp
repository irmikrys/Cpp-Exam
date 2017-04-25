#include <iostream>

class Animal{
public:
    virtual Animal* copy()const =0;
};

class Dog:public Animal{
public:
    Animal* copy()const{
        return new Dog(*this);
    }
};

class Cat: public Animal{
public:
    Animal* copy()const{
        return new Cat(*this);
    }
};

class Frog: public Animal{
public:
    Animal* copy() const{
        return new Frog(*this);
    }
};

class AnimalWezel{
public:
    AnimalWezel* next;
    Animal* wsk;
};

class AnimalList{
private:
    AnimalWezel* begin;
    AnimalWezel* end;
public:
    AnimalList(): begin(0), end(0){}
    ~AnimalList();
    void add(Animal* a);
    AnimalList(const AnimalList&);
    AnimalList& operator=(const AnimalList&);
    void wypisz();
};

AnimalList::~AnimalList() {
    AnimalWezel* it;
    while(begin!=0){
        it=begin;
        begin=begin->next;
        delete(it->wsk);
        delete(it);
    }
    begin=0;
    end=0;
}
void AnimalList::add(Animal* a){
    AnimalWezel* tmp=new AnimalWezel;
    if(begin==0){
        tmp->next=0;
        begin=tmp;
        end=tmp;
    }
    else{
        end->next=tmp;
        tmp->next=0;
        end=tmp;
    }
    tmp->wsk=a;
}

AnimalList::AnimalList(const AnimalList& copy1) {
    AnimalWezel* it=copy1.begin;
    while(it!=0){
        this->add(it->wsk->copy());
        it=it->next;
    }
}

AnimalList& AnimalList::operator=(const AnimalList& copy1){
    AnimalWezel* it;
    while(begin!=0){
        it=begin;
        begin=begin->next;
        delete(it->wsk);
        delete(it);
    }
    begin=0;
    end=0;
    it=copy1.begin;
    while(it!=0){
        this->add(it->wsk->copy());
        it=it->next;
    }
    return (*this);
}

void AnimalList::wypisz() {
    AnimalWezel* it=this->begin;
    while(it!=0){
        std::cout << "Wezel listy" <<std::endl;
        it=it->next;
    }
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"------------------------"<<std::endl;
}

int main(){
    Dog* pies=new Dog();
    AnimalList zagroda;
    zagroda.add(pies);
    zagroda.wypisz();
    Cat* kot=new Cat();
    zagroda.add(kot);
    zagroda.wypisz();
    Cat* kot1 = new Cat(*kot);
    zagroda.add(kot1);
    Dog* pies1 = new Dog();
    pies1 = pies;
    zagroda.add(pies1);
    zagroda.wypisz();
    return 0;
}
