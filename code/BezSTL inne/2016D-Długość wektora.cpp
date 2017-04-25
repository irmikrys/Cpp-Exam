#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int n;
    cin>>n; //ile elementow ma wektor
    double *tab = new double[n];    //tworzymy tablice dynamiczna
    for(int i=0; i<n; i++)
    {
        cin>>tab[i];
    }
    double sum=0; //w tej zmiennej trzymamy sume kwadratow elementow tablicy tab, zmienna inicjujemy zerem!!!
    for(int j=0; j<n-1; j++)
    {
        sum += (tab[j])*(tab[j]);
    }
    double wynik = sqrt(sum);   //wynik to pierwiastek sum kwadratow elementow
    cout<<"Dlugosc wektora: "<<wynik<<endl;
    return 0;
}
