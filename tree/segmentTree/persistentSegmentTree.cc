#include <iostream>
#include <vector>

using namespace std;

struct PST {
    struct Node {
        int lc = 0;
        int rc = 0;
        int cnt = 0;
        long long sum = 0;
    };

    int n = 0;
    vector<Node> tree;

    PST(int n_, int reserve_nodes) : n(n_) {
        tree.reserve(reserve_nodes);
        tree.push_back(Node());
    }

    int new_node(const Node& x) {
        tree.push_back(x);
        return (int)tree.size() - 1;
    }

    int update(int v, int tl, int tr, int pos, int addCnt, long long addSum) {
        int nv = new_node(tree[v]);
        tree[nv].cnt += addCnt;
        tree[nv].sum += addSum;

        if (tl == tr) return nv;

        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            int leftNew = update(tree[nv].lc, tl, tm, pos, addCnt, addSum);
            tree[nv].lc = leftNew;
        } else {
            int rightNew = update(tree[nv].rc, tm + 1, tr, pos, addCnt, addSum);
            tree[nv].rc = rightNew;
        }
        return nv;
    }

    pair<long long,long long> queryDiff(int vr, int vl, int tl, int tr, int l, int r) const {
        if (r < tl || tr < l) return {0, 0};
        if (l <= tl && tr <= r) {
            long long dc = (long long)tree[vr].cnt - (long long)tree[vl].cnt;
            long long ds = tree[vr].sum - tree[vl].sum;
            return {dc, ds};
        }
        int tm = (tl + tr) >> 1;
        auto A = queryDiff(tree[vr].lc, tree[vl].lc, tl, tm, l, r);
        auto B = queryDiff(tree[vr].rc, tree[vl].rc, tm + 1, tr, l, r);
        return {A.first + B.first, A.second + B.second};
    }

    pair<long long,long long> rangeQuery(int rootR, int rootL, int l, int r) const {
        if (n == 0 || l > r) return {0, 0};
        l = max(l, 0);
        r = min(r, n - 1);
        if (l > r) return {0, 0};
        return queryDiff(rootR, rootL, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> val = {2, 0, 2, 1, 0};
    vector<long long> w = {5, 7, 11, 13, 17};

    int N = (int)val.size();
    int K = 3;

    PST pst(K, (N + 5) * 25);
    vector<int> root(N + 1, 0);

    for (int i = 0; i < N; i++) {
        root[i + 1] = pst.update(root[i], 0, K - 1, val[i], 1, w[i]);
    }

    auto brute = [&](int a, int b, int L, int R) -> pair<long long,long long> {
        long long cnt = 0, sum = 0;
        for (int i = a; i <= b; i++) {
            if (L <= val[i] && val[i] <= R) {
                cnt++;
                sum += w[i];
            }
        }
        return {cnt, sum};
    };

    vector<tuple<int,int,int,int>> queries = {
        {1, 3, 0, 1},
        {0, 4, 2, 2},
        {2, 4, 0, 0},
        {0, 0, 0, 2},
        {0, 4, 0, 0},
    };

    for (auto [a,b,L,R] : queries) {
        auto got = pst.rangeQuery(root[b + 1], root[a], L, R);
        auto exp = brute(a, b, L, R);
        cout << got.first << " " << got.second << " | " << exp.first << " " << exp.second << "\n";
    }

    return 0;
}
