/*
                                                            Union-Find (DSU) 
        structure efficiently manages disjoint sets. Its two core operations are Find (to determine the set representative) and 
  Union (to merge two sets). It's primarily used in graph algorithms, notably Kruskal's algorithm for Minimum Spanning Trees and cycle detection.
*/

#include <iostream>
#include <vector>
#include <numeric> 

using namespace std;

class UnionFind
{
private:
    vector<int> parent, size;    
public:
    UnionFind(int n) : parent(n), size(n, 1) 
    {
        iota(parent.begin(), parent.end(), 0); 
    }
    
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        
        return parent[i] = find(parent[i]); 
    }

    void unionSets(int i, int j)
    {
        int rootI = find(i);
        int rootJ = find(j);

        if (rootI == rootJ)
        {
            cout << i << " and " << j << " come from the same tree\n";
            return;
        }
        if (size[rootI] < size[rootJ])
        {
            parent[rootI] = rootJ;
            size[rootJ] += size[rootI];
            cout << i << " tree was merged into " << j << " tree\n";
        }
        else 
        {
            parent[rootJ] = rootI;
            size[rootI] += size[rootJ];
            cout << j << " tree was merged into " << i << " tree\n";
        }
    }
};

int main()
{
    UnionFind uf(3);

    cout << "Operation: unionSets(1,2)\n";
    uf.unionSets(1,2);
    cout << "Operation: unionSets(2,1)\n";
    uf.unionSets(2,1);
    cout << "Operation: unionSets(0,2)\n";
    uf.unionSets(0,2);

	return 0;
};