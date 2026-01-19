#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static const int MAXN = 200000;

vector<vector<int>> tree(MAXN + 1);
int diameterArr[MAXN + 1];
int downPath[MAXN + 1];

void dfs(int u, int p) {
    downPath[u] = 0;
    diameterArr[u] = 0;

    int best1 = 0, best2 = 0;

    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);

        diameterArr[u] = max(diameterArr[u], diameterArr[v]);

        int cand = downPath[v] + 1;
        if (cand > best1) {
            best2 = best1;
            best1 = cand;
        } else if (cand > best2) {
            best2 = cand;
        }
    }

    downPath[u] = best1;
    diameterArr[u] = max(diameterArr[u], best1 + best2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        tree[i].clear();
        diameterArr[i] = 0;
        downPath[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

    cout << diameterArr[1] << "\n";

    return 0;
}
