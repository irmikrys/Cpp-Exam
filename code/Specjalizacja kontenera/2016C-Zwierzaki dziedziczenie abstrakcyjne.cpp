#include <iostream>

class Animal
{
public:
    virtual Animal* clone()const = 0;
};

class Frog : public Animal
{
public:
    Frog* clone()const
    {
        return new Frog(*this);
    }
};

class Dog : public Animal
{
public:
    Dog* clone()const
    {
        return new Dog(*this);
    }
};

class Cat : public Animal
{
public:
    Cat* clone()const
    {
        return new Cat(*this);
    }
};

class AnimalList
{
public:

    class AnimalListEl
    {
    public:
        AnimalListEl * next;
        Animal * dane;
    };

    AnimalListEl * head;
    /////////////konstruktor/////////////////
    AnimalList()
    {
        head = NULL;
    }
    /////////////destruktor//////////////////
    ~AnimalList()
    {
        while(head)
        {
            AnimalListEl * p = head;
            if(p)
            {
                head = p->next;
                delete(p->dane);
                delete(p);
            }
        }
        head = NULL;
    }
    /////////////dodawanie do listy//////////
    void add(Animal*a)
    {
        AnimalListEl*p = new AnimalListEl;
        p->next = head;
        p->dane = a->clone();
        head = p;
    }
    //////////konstruktor kopiuj¹cy//////////
    AnimalList(const AnimalList& copied)
    {
        AnimalListEl* it = copied.head;
        while(it != NULL)
        {
            this->add(it->dane->clone());
            it = it->next;
        }
    }
    /////////////operator = /////////////////
    AnimalList& operator=(const AnimalList& copied)
    {
        AnimalListEl* it;
        //mmusimy zwolnic pamiec bo to op przypisania!!!
        while(head = NULL)
        {
            it = head;
            head = head->next;
            delete(it->dane);
            delete(it);
        }
        head = NULL;
        it = copied.head;
        while(it != NULL)
        {
            this->add(it->dane->clone());
            it = it->next;
        }
        return (*this);
    }
    //////////////pomocnicze wypisanie/////////////////
    void wypisz()
    {
        AnimalListEl* it=this->head;
        while(it!=0)
        {
            std::cout << "Wezel listy" <<std::endl;
            it=it->next;
        }
        std::cout<<"------------------------"<<std::endl;
        std::cout<<"------------------------"<<std::endl;
    }

};

int main()
{
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


