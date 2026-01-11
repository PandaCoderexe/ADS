/*
    This code is implementation of solution to problem LCASQ. Link: https://www.spoj.com/problems/LCASQ/
            The lowest common ancestor (LCA) of two nodes in a rooted tree is the deepest node that is an ancestor of both nodes. 
    Using binary lifting, we preprocess the depth of each node and a table up[v][k] that stores the 2^k-th ancestor of v in O(n log n) time. 
                    For a query (u, v), we first lift the deeper node to the same depth as the other, 
            then lift both nodes from the largest k down to 0 until they become equal, and that node is the LCA.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int MAX_N = 10000;
int LOG = 14;

vector<vector<int>> children(MAX_N);
vector<vector<int>> up(MAX_N, vector<int>(LOG));
vector<int> depth(MAX_N);

void dfs(int n)
{
    for (int child : children[n])
    {   
        depth[child] = depth[n]+1;
        up[child][0] = n; 

        for (int j = 1; j < LOG; j++)
        {
            up[child][j] = up[ up[child][j-1] ][j-1];
        }
        dfs(child);
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b]) swap(a, b);

    int k = depth[a] - depth[b];
    for (int i = 0; i < LOG; i++)
    {
        if (k & (1 << i))
        {
            a = up[a][i];
        }
    }

    if (a == b)
    {
        return a;
    }

    for (int i = LOG-1; i >= 0; i--)
    {
        if (up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int cnt;
        cin >> cnt;
        
        for (int j = 0; j < cnt; j++)
        {
            int c;
            cin >> c;
            children[i].push_back(c);
        }
    }

    dfs(0);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int a,b;
        cin >> a >> b;
        cout << lca(a,b) << "\n";
    }

    return 0;
}