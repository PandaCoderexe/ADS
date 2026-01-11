/*
This C++ program finds the centroid of a tree.

    -> A tree is an acyclic connected graph.

    -> The centroid of a tree is a node that, if removed, leaves all remaining connected components with at most n/2 nodes.

    -> Essentially, it’s a node that “balances” the tree.
*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> childrens[1000001];
int size[1000001];

int n;

void subSize(int node, int prev)
{
    size[node] = 1;

    for (int child : childrens[node])
    {
        if (child != prev)
        {
            subSize(child, node);
            size[node] += size[child];
        }
    }
}

int centroid(int node, int prev)
{
    for (int child : childrens[node])
    {
        if (child != prev && size[child] > n/2)
        {
            return centroid(child,node);
        }
    }

    return node;
}

int main()
{
    int x, y;
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cin >> x >> y;

        childrens[x].push_back(y);
        childrens[y].push_back(x);
    }

    subSize(1,-1);
    cout << centroid(1,-1);
    return 0;
}