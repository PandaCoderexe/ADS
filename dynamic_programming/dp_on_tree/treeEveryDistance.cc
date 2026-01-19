#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

static const int MAXN = 200001;

vector<vector<int>> tree(MAXN);
ll subtreeAns[MAXN];
ll ans[MAXN];
int subtreeSize[MAXN];

void preprocessing(int curr, int par)
{
    int numOfNodes = 1;
    ll ansSubTree = 0;

    for (int &child : tree[curr])
    {
        if (child != par)
        {
            preprocessing(child, curr);
            numOfNodes += subtreeSize[child];
            ansSubTree += subtreeSize[child] + subtreeAns[child];
        }
    }

    subtreeSize[curr] = numOfNodes;
    subtreeAns[curr] = ansSubTree;
}

void calculateDistance(int curr, int par, ll par_ans, int& totalNodes)
{
    ans[curr] = subtreeAns[curr] + par_ans;

    for (int &child : tree[curr])
    {
        if (child == par) continue;

        ll outside_from_curr = ans[curr] - (subtreeAns[child] + subtreeSize[child]);
        int outside_count = totalNodes - subtreeSize[child];
        ll child_par_ans = outside_from_curr + outside_count;

        calculateDistance(child, curr, child_par_ans, totalNodes);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        tree[i].clear();
        subtreeAns[i] = 0;
        ans[i] = 0;
        subtreeSize[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    preprocessing(1, 0);

    int totalNodes = n;
    calculateDistance(1, 0, 0LL, totalNodes);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
    cout << "printed\n";

    return 0;
}
