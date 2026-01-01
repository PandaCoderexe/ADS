/*
        Lazy propagation is a segment tree technique that speeds up range updates by postponing them. 
You store a pending update in a node and push it to children only when a query or further update needs those values, 
                                    keeping operations about 𝑂(log 𝑛)
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree
{
public:
    SegmentTree(const vector<long long>& a_)
    {
        a = a_;
        N = (int)a.size();
        segTree.assign(4 * N + 5, 0);
        lazy.assign(4 * N + 5, 0);

        build(0, N - 1, 0);
    }

    long long querySum(int ql, int qr)
    {
        return querySum(0, 0, N - 1, ql, qr);
    }

    void pointUpdate(int pos, long long val)
    {
        pointUpdate(0, 0, N - 1, pos, val);
    }

    void rangeAdd(int l, int r, long long val)
    {
        rangeAdd(0, 0, N - 1, l, r, val);
    }

private:
    void build(int l, int r, int idx)
    {
        if (l == r)
        {
            segTree[idx] = a[l];
        }
        else
        {
            int mid = (l + r) / 2;

            build(l, mid, 2 * idx + 1);
            build(mid + 1, r, 2 * idx + 2);

            segTree[idx] = segTree[2 * idx + 1] + segTree[2 * idx + 2];
        }
    }

    void push(int idx, int tl, int tr)
    {
        if (lazy[idx] == 0 || tl == tr) return;

        int tm = tl + (tr - tl) / 2;
        long long add = lazy[idx];

        segTree[idx * 2 + 1] += add * (tm - tl + 1);
        segTree[idx * 2 + 2] += add * (tr - (tm + 1) + 1);

        lazy[idx * 2 + 1] += add;
        lazy[idx * 2 + 2] += add;
        lazy[idx] = 0;
    }

    long long querySum(int idx, int tl, int tr, int ql, int qr)
    {
        if (ql > qr) return 0;
        if (ql == tl && qr == tr) return segTree[idx];

        push(idx, tl, tr);
        int tm = tl + (tr - tl) / 2;

        return querySum(2 * idx + 1, tl, tm, ql, min(qr, tm)) +
               querySum(2 * idx + 2, tm + 1, tr, max(ql, tm + 1), qr);
    }

    void pointUpdate(int idx, int tl, int tr, int pos, long long val)
    {
        if (tl == tr)
        {
            a[pos] = val;
            segTree[idx] = val;
            lazy[idx] = 0;
            return;
        }

        push(idx, tl, tr);
        int tm = tl + (tr - tl) / 2;

        if (pos <= tm) pointUpdate(2 * idx + 1, tl, tm, pos, val);
        else pointUpdate(2 * idx + 2, tm + 1, tr, pos, val);

        segTree[idx] = segTree[2 * idx + 1] + segTree[2 * idx + 2];
    }

    void rangeAdd(int idx, int tl, int tr, int l, int r, long long add)
    {
        if (l > r) return;

        if (l == tl && r == tr)
        {
            segTree[idx] += add * (tr - tl + 1);
            lazy[idx] += add;
            return;
        }

        push(idx, tl, tr);
        int tm = tl + (tr - tl) / 2;

        rangeAdd(idx * 2 + 1, tl, tm, l, min(r, tm), add);
        rangeAdd(idx * 2 + 2, tm + 1, tr, max(l, tm + 1), r, add);

        segTree[idx] = segTree[2 * idx + 1] + segTree[2 * idx + 2];
    }

    int N;
    vector<long long> a;
    vector<long long> segTree;
    vector<long long> lazy;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> a = {1, 2, 3, 4, 5};
    SegmentTree st(a);

    cout << "Array: [1,2,3,4,5]\n";
    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 15)\n";
    cout << "sum(1,3) = " << st.querySum(1,3) << " (expected 9)\n";
    cout << "sum(2,2) = " << st.querySum(2,2) << " (expected 3)\n";
    cout << "sum(0,0) = " << st.querySum(0,0) << " (expected 1)\n";
    cout << "sum(4,4) = " << st.querySum(4,4) << " (expected 5)\n";

    cout << "\nPoint update: a[2] = 10\n";
    st.pointUpdate(2, 10);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 22)\n";
    cout << "sum(1,3) = " << st.querySum(1,3) << " (expected 16)\n";
    cout << "sum(2,2) = " << st.querySum(2,2) << " (expected 10)\n";

    cout << "\nPoint update: a[0] = -7\n";
    st.pointUpdate(0, -7);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 14)\n";
    cout << "sum(0,1) = " << st.querySum(0,1) << " (expected -5)\n";


    cout << "\nRange add: add +5 on [1,3]\n";
    st.rangeAdd(1, 3, 5);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 29)\n";
    cout << "sum(1,3) = " << st.querySum(1,3) << " (expected 31)\n";
    cout << "sum(3,4) = " << st.querySum(3,4) << " (expected 14)\n";

    cout << "\nRange add: add -2 on [0,4]\n";
    st.rangeAdd(0, 4, -2);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 19)\n";
    cout << "sum(0,0) = " << st.querySum(0,0) << " (expected -9)\n";
    cout << "sum(4,4) = " << st.querySum(4,4) << " (expected 3)\n";

    cout << "\nRange add: add +10 on [2,4]\n";
    st.rangeAdd(2, 4, 10);

    cout << "sum(2,4) = " << st.querySum(2,4) << " (expected 53)\n";
    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 49)\n";

    cout << "\nPoint update after lazy: a[3] = 100\n";
    st.pointUpdate(3, 100);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 132)\n";
    cout << "sum(3,3) = " << st.querySum(3,3) << " (expected 100)\n";
    cout << "sum(2,4) = " << st.querySum(2,4) << " (expected 136)\n";

    return 0;
}