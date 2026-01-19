#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using t = tuple<int,int>;

vector<vector<int>> tree(200001);
int dp[200001][2]; // 0 -> we do not take this edge 1 -> we take this edge 

void treeMatching(int curr, int par)
{
    vector<int> prefix, suffix;
    dp[curr][0] = 0; dp[curr][1] = 0; 

    bool leaf = true;
    for (int& child : tree[curr])
    {
        if (child != par)
        {
            leaf = false;
            treeMatching(child, curr);
        }
    } 

    if (leaf) return;

    for (int& child : tree[curr])
    {
        if (child != par)
        {
            suffix.push_back(max(dp[child][0], dp[child][1]));
            prefix.push_back(max(dp[child][0], dp[child][1]));
        }
    }

    for (int i = 1; i < (int)prefix.size(); i++) prefix[i] += prefix[i-1];
    for (int i = (int)suffix.size()-2; i >= 0; i--) suffix[i] += suffix[i+1];

    dp[curr][0] = suffix[0];
    int check = 0;
    for (int& child : tree[curr])
    {
        if (child != par)
        {
            int leftChild = (check == 0) ? 0 : prefix[check-1];
            int rightChild = (check == (int)suffix.size()-1) ? 0 : suffix[check+1];

            dp[curr][1] = max(dp[curr][1], 1 + leftChild + rightChild + dp[child][0]);
            check++;
        }
    }
}

int main()
{
    int n; // number of nodes
    cin >> n;

    for (int i = 0; i < n-1; i++)
    {
        int x,y;
        cin >> x >> y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    treeMatching(1,-1);

    cout << max(dp[1][1], dp[1][0]);
    return 0;
}