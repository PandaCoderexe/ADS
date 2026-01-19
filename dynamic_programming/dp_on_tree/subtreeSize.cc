#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> tree(200001);
vector<int> ans(200001);

void subtreeSize(int curr, int par)
{
    int subtree_size = 0;
    for (int& child : tree[curr])
    {
        if (child != par)
        {
            subtreeSize (child,curr);
            subtree_size += 1 + ans[child];
        }   
    }
    ans[curr] = subtree_size;
}

int main()
{
    int n;
    cin >> n;

    // lets say that our root is 1 
    for (int i = 2; i < n+1; i++)
    {
        int par;
        cin >> par;
        tree[par].push_back(i);
    }

    subtreeSize(1,-1);

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}