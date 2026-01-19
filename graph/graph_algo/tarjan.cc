#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

stack<int> st;
vector<int> scc(100000 + 1, 0);
vector<int> dfn(100000 + 1, 0);
vector<int> low(100000 + 1, 0);
vector<vector<int>> ans;
vector<vector<int>> graph;

int id = 0, color_cnt = 0;

void tarjan(int node)
{
    st.push(node);
    low[node] = dfn[node] = ++id;

    for (int neighbour : graph[node])
    {
        if (dfn[neighbour] == 0)
        {
            tarjan(neighbour);
            low[node] = min(low[node], low[neighbour]);
        }
        else if (scc[neighbour] == 0)
        {
            low[node] = min(low[node], dfn[neighbour]);
        }
    }

    if (low[node] == dfn[node])
    {
        ++color_cnt;
        ans.push_back(vector<int>());

        while (true)
        {
            int to = st.top(); st.pop();
            ans.back().push_back(to);
            scc[to] = color_cnt;
            if (to == node) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph.assign(n + 1, {});

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    cout << "scc_count = " << ans.size() << "\n";
    cout << "printed\n";

    return 0;
}
