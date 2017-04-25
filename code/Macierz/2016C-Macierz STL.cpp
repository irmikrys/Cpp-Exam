#include <iostream>
#include <vector>
using namespace std;

class Mat: public vector<double*>
{
public:
    vector<int> ile;
    int ilosc;
    Mat():ilosc(0){}
    ~Mat()
    {
     vector<double*>::iterator it;
     for(it=begin(); it!=end(); it++)
     {
         delete [] *it;
         cout<<"dd"<<endl;
     }
    }

    double* addRow(int Size)
    {
        double *tmp= new double[Size];
        push_back(tmp);
        ilosc++;
        ile.push_back(Size);
        return tmp;
    }

    void deleteRow(int r)
    {
        if(ilosc<=r) return; // throw InvalidIndex

            vector<int>::iterator it;
            it=ile.begin()+r;
            ile.erase(it);

            vector<double*>::iterator id;
            id=begin()+r;
            delete [] *id;
            erase(id);

            ilosc--;
    }

    double * operator()(int row, int col)
    {
        if(ilosc<=row);//throw InvalidIndex
        if(ile[row]<=col);//throw InvalidIndex

        vector<double*>::iterator id;
        id=begin()+row;
       double *cos = id[col];
       return cos;
    }




};

//ten operator nie zadzaiala poniewaz przyjmujemy ze tam gdzie macierz nie istnieje sa zera
//wiec to sie nie skompiluje, nalezaloby sprawdzac dokladnie czy nie wychodzimy poza pamiec,
//ale nie bylo to wymagane na egzaminie
    Mat operator+(const Mat &m1, const Mat &m2)
    {
        Mat tmp;
        if(m1.ilosc>=m2.ilosc) tmp.ilosc=m1.ilosc;
        else tmp.ilosc=m2.ilosc;

        for(int i=0; i<tmp.ilosc; i++)
        {
            if(m1.ile[i]>=m2.ile[i])
            {
                tmp.ile.push_back(m1.ile[i]);
                double *cos=new double[tmp.ile[i]];
                tmp.push_back(cos);
            }
            else
            {
                tmp.ile.push_back(m2.ile[i]);
                double *cos=new double[tmp.ile[i]];
                tmp.push_back(cos);
            }
        }

        for(int i=0; i<tmp.ilosc; i++)
        {
            for(int j=0; j<tmp.ile[i]; j++)
            {
                tmp[i][j]=m1[i][j]+m2[i][j];
            }
        }

    }




int main()
{

    return 0;
}
