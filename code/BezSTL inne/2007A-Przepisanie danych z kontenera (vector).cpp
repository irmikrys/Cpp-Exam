/*[10] Napisz szablon funkcji parametryzowanej typem T, która do
kontenera vector<T>&source mniejsze niz const T&key. Podaj przyklad
wywolania. */

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void func(vector<T>&result, const vector<T>&source, const T&key)
{
    typename vector<T>::const_iterator it;
    for(it = source.begin(); it != source.end(); it++)
        if((*it) < key) result.push_back(*it);
}

int main()
{
    vector<int> s;
    vector<int> r;
    int key = 4;
    for(int i = 0; i < 10; i++)
        s.push_back(i);
    func<int>(r, s, key);
    for(int j = 0; j < r.size(); j++)
        cout << r[j] << " ";
    return 0;
}
