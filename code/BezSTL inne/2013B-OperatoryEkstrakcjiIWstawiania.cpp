/*[10] Dla klasy class Vector {public: double*data; int size;}; zaimplementuj operatory ekstrakcji >> i wstawiania <<
 * do strumienia.*/

#include <iostream>
using namespace std;

class Vector
{
public:
    double * data;
    int size;

    friend ostream& operator << (ostream& stream, const Vector& v);
    friend istream& operator >> (istream& stream, Vector& v);
};

ostream &operator<<(ostream &stream, const Vector &v)
{
    stream << "[ ";
    for(int i = 0; i < v.size; i++)
    {
        stream << v.data[i] << " ";
    }
    stream << "]" << endl;
    return stream;
}

istream &operator>>(istream &stream, Vector &v)
{
    int s;
    stream >> s;
    v.size = s;
    v.data = new double[s];
    for(int i = 0; i < v.size; i++)
    {
        double d;
        stream >> d;
        v.data[i] = d;
    }
    return stream;
}

int main()
{
    Vector v1;
    cin >> v1;
    cout << v1;
    return 0;
}
