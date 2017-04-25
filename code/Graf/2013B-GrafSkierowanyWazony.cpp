/*[25] Uzyj STL. Graph<V, W> jest szablonem grafu skierowanego. Krawedzi laczacej wierzcholki v1 i v2 typu V przypisana
 * jest waga typu W. Zaloz, ze dla V i W zdefiniowane sa operatory == i !=, a dla W dodatkowo += i <. Napisz:
 * (a) konstruktor i deklaracje
 * (b) void addEdge(const V& v1, const V& v2, const W& w) dodaje krawedz lub zmienia jej wage
 * (c) bool listNeighbors (const V& v, list<V>& result) - wypelnia result lista sasiadow wierzcholka v
 * (d) bool isPath(const V* path, int n) - sprawdza czy path jest droga w grafie
 * (e) int calcCost(const V* path, int n, W& result) - wypelnia result suma wag przypisanych krawedziom lezacym na
 *     sciezce. Jesli brak krawedzi (path[i], path[i+1]) przerywa dzialanie i zwraca 1. */

#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class V, class W>
class Graph
{
public:
    struct Edge
    {
        V v1;
        V v2;
        W waga;
    };

    vector<Edge> edges;
    vector<V> vertex;

    Graph()
    {

    }

    bool isEdge(const V& v1, const V& v2)const
    {
        typename vector<Edge>::const_iterator it;
        for(it = edges.begin(); it != edges.end(); it++)
        {
            if(it->v1 == v1 && it->v2 == v2) return true;
        }
        return false;
    }

    bool isVertex(const V& v)const
    {
        typename vector<V>::const_iterator it;
        for(it = vertex.begin(); it != vertex.end(); it++)
        {
            if(*it == v) return true;
        }
        return false;
    }

    void addEdge(const V& v1, const V& v2, const W& w)
    {
        typename vector<Edge>::iterator it;
        for(it = edges.begin(); it != edges.end(); it++)
        {
            if(it->v1 == v1 && it->v2 == v2)
            {
                it->waga = w;
                return;
            }
        }
        Edge ed;
        ed.v1 = v1;
        ed.v2 = v2;
        ed.waga = w;
        edges.push_back(ed);

        if(!isVertex(v1)) vertex.push_back(v1);
        if(!isVertex(v2)) vertex.push_back(v2);
    }

    bool listNeighbors(const V& v, list<V>& result)
    {
        typename vector<V>::const_iterator it;
        for(it = vertex.begin(); it != vertex.end(); it++)
        {
            if(isEdge(v, *it)) result.push_back(*it);
        }
        return true;
    }

    bool isPath(const V* path, int n)
    {
        for(int i = 0; i < n - 1; i++)
        {
            if(!isEdge(path[i], path[i + 1])) return false;
        }
        return true;
    }

    int calcCost(const V* path, int n, W& result)
    {
        result = 0;
        if(!isPath(path, n)) return 1;

        typename vector<Edge>::iterator it;

        for(int i = 0; i < n - 1; i++)
        {
            for(it = edges.begin(); it != edges.end(); it++)
            {
                if(it->v1 == path[i] && it->v2 == path[i + 1])
                    result += it->waga;
            }
        }
        return result;
    }

};


int main()
{
    Graph<char, int> g1;
    g1.addEdge('k', 'i', 6);
    g1.addEdge('k', 'o', 4);
    g1.addEdge('a', 'o', 3);
    g1.addEdge('i', 'o', 9);
    g1.addEdge('o', 'r', 7);

    char * path = new char[4];
    path[0] = 'k'; path[1] = 'i'; path[2] = 'o'; path[3] = 'r';

    int res;

    if(g1.isPath(path, 4)) cout << "path jest droga w grafie" << endl;
    cout << "koszt przejscia: " << g1.calcCost(path, 4, res) << endl;

    list<char> neigh;
    g1.listNeighbors('k', neigh);
    typename list<char>::const_iterator it;
    for(it = neigh.begin(); it != neigh.end(); it++)
        cout << *it << " ";

    return 0;
}