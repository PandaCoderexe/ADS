/*
Binary lifting is a preprocessing technique for rooted trees where we build a table up[v][k] storing the 2^k-th ancestor of each node v in O(n log n) time. 
    Then we can move a node upward by any distance d in O(log n) by decomposing d into powers of two and applying the corresponding jumps.

*/
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int n = 8;
int LOG = 1;

vector<vector<int>> tree = {{},{2,3},{1,4,5},{1,6,7},{2,8},{2},{3},{3},{4}};
vector<int> parent(9, -1);
vector<vector<int>> up;

void preprocessing()
{
    for (int v = 1; v <= n; v++) up[v][0] = parent[v];
    
    for (int k = 1; k < LOG; k++)
    {
        for (int v = 1; v <= n; v++)
        {
            up[v][k] = up[up[v][k-1]][k-1];
        }
    }
}

int binary_lifting(int node, int k)
{
    for (int i = 0; i < LOG; i++)
    {
        if (k & (1 << i)) node = up[node][i];
    }

    return node;
}

int main()
{

    int root = 1;
    parent[root] = 1;

    stack<int> s;
    s.push(root);

    while(!s.empty())
    {
        int cur = s.top(); s.pop();

        for (int child : tree[cur])
        {
            if (parent[child] != -1) continue;

            parent[child] = cur;
            s.push(child);
        }
    }

    // precomputing log
    while((1LL << LOG) <= n) LOG++;

    up.assign(n+1, vector<int>(LOG, 0));

    preprocessing();

    cout << "result = " << binary_lifting(8, 0)  << "  has to be 8\n";
    cout << "result = " << binary_lifting(8, 1)  << "  has to be 4\n";
    cout << "result = " << binary_lifting(8, 2)  << "  has to be 2\n";
    cout << "result = " << binary_lifting(8, 3)  << "  has to be 1\n";
    cout << "result = " << binary_lifting(8, 4)  << "  has to be 1\n";

    return 0;
}