#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static void read_tree(int &n, vector<vector<int>> &tree) {
    cin >> n;
    tree.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
}

static void build_parent_and_order(const vector<vector<int>> &tree, int root,
                                   vector<int> &parent, vector<int> &order) {
    int n = (int)tree.size() - 1;
    parent.assign(n + 1, -1);
    order.clear();
    order.reserve(n);

    vector<int> st;
    st.reserve(n);
    st.push_back(root);
    parent[root] = 0;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : tree[u]) {
            if (parent[v] != -1) continue;
            parent[v] = u;
            st.push_back(v);
        }
    }
}

static void compute_down(const vector<vector<int>> &tree, const vector<int> &parent,
                         const vector<int> &order, vector<int> &down) {
    int n = (int)tree.size() - 1;
    down.assign(n + 1, 0);

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        int best = 0;
        for (int v : tree[u]) {
            if (v == parent[u]) continue;
            best = max(best, down[v] + 1);
        }
        down[u] = best;
    }
}

static void compute_up_and_answer(const vector<vector<int>> &tree, const vector<int> &parent, const vector<int> &order, const vector<int> &down, vector<int> &up, vector<int> &ans) {
    int n = (int)tree.size() - 1;
    up.assign(n + 1, -1);
    ans.assign(n + 1, 1);

    int root = order.empty() ? 1 : order[0];
    up[root] = -1;
    ans[root] = max(down[root], up[root]) + 1;

    for (int u : order) {
        int best1 = -1, best2 = -1, bestChild = -1;

        for (int v : tree[u]) {
            if (v == parent[u]) continue;
            int cand = down[v] + 1;
            if (cand > best1) {
                best2 = best1;
                best1 = cand;
                bestChild = v;
            } else if (cand > best2) {
                best2 = cand;
            }
        }

        for (int v : tree[u]) {
            if (v == parent[u]) continue;

            int bestSibling = (v == bestChild ? best2 : best1);

            int bestFromU = 0;
            if (up[u] != -1) bestFromU = max(bestFromU, up[u]);
            if (bestSibling != -1) bestFromU = max(bestFromU, bestSibling);

            up[v] = bestFromU + 1;
            ans[v] = max(down[v], up[v]) + 1;
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    vector<vector<int>> tree;
    read_tree(n, tree);

    vector<int> parent, order;
    build_parent_and_order(tree, 1, parent, order);

    vector<int> down;
    compute_down(tree, parent, order, down);

    vector<int> up, ans;
    compute_up_and_answer(tree, parent, order, down, up, ans);

    for (int i = 1; i < (int)ans.size(); i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
