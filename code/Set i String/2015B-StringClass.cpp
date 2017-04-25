/*Klasa String dynamicznie alokuje pamiec dla tablicy znakow.
*class String{ char *sp; //dalsze deklaracje };
*Zadeklaruj i zaimplementuj:
*(a) konstruktor String(const char* t)
*(b) destruktor
*(c) operator +
*(d) operator[] - powinien zwracac referencje do znaku o podanym numerze lub wyrzucac wyjatek OutOfBounds*/

#include <iostream>
using namespace std;

class OutOfBounds{};

class String
{
public:
    char *sp;

    String(const char* t);
    ~String();
    friend String operator + (const String& s, const char* txt);
    char& operator[](int i);
    operator const char*()const
    {
        return sp;
    }

};

String::String(const char *t)
{
    sp = new char[256];
    strcpy(sp, t);
}

String::~String()
{
    if(sp) delete[] sp;
    sp = nullptr;
}

String operator+(const String &s, const char *txt)
{
    String tmp(s.sp);
    strcat(tmp.sp, txt);
    return tmp;
}

char &String::operator[](int i)
{
    if(i < 0 || i > 255) throw OutOfBounds();
    return sp[i];
}

int main()
{
    String s1("Ala ma ");
    String s2("Dropsa");
    String s3 = s1 + "kota";
    for(int i = 0; i < strlen(s3); i++)
        putchar(s3[i]);
    return 0;
}



