/*
A segment tree is a binary tree data structure that stores information (such as sums, minima, or maxima) about subranges of an array. 
            It allows you to answer range queries and perform updates efficiently by visiting only 𝑂(log 𝑛) nodes. 
                Each node represents an interval, and its value is computed from its children.
*/
#include <iostream>
#include <vector>
using namespace std;

// range update range query
struct SegTree_RangeRange
{
    int n;
    vector<long long> tree;
    vector<long long> lazy;
    SegTree_RangeRange(int n_, vector<long long>& vals): n(n_)
    {
        tree.resize(4*n, 0);
        lazy.resize(4*n,0);
        build(vals,1,0, n-1);
    }

    void build(vector<long long>& vals, int v, int tl, int tr)
    {
        if (tl == tr) {tree[v] = vals[tl]; return;}
        int tm  = (tr+tl) /2;
        build(vals, v*2, tl, tm);
        build(vals,v*2+1, tm+1, tr);
        tree[v] = tree[v*2]+ tree[v*2+1];
    }

    void push(int v, int tl, int tr)
    {
        if (lazy[v] == 0 || tl == tr) return;
        int tm = (tr+tl) / 2;
        long long add = lazy[v];

        lazy[v*2] += add;
        lazy[2*v+1] += add;

        tree[2*v] += add * (tm - tl + 1);
        tree[2*v+1] += add * (tr - (tm + 1) +1);

        lazy[v] = 0;
    }

    void update(int l, int r, long long add)
    {
        update(1, 0, n-1, l,r, add);
    }

    void update(int v, int tl, int tr, int l, int r, long long add)
    {
        if (l > r) return;
        if (l == tl && tr == r)
        {
            tree[v] += add * (tr - tl + 1);
            lazy[v] += add;
            return;
        }

        push(v,tl,tr);
        int tm = (tr+tl) / 2;
        update(v*2,tl,tm,l,min(r,tm), add);
        update(v*2+1,tm+1,tr,max(tm+1,l), r, add);

        tree[v] = tree[v*2] + tree[v*2+1];
    }

    long long rangeQuery(int l, int r)
    {
        return rangeQuery(1,0,n-1,l,r);
    }

    long long rangeQuery(int v, int tl, int tr, int l, int r)
    {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        push(v,tl,tr);
        int tm = (tr + tl) /2;
        return rangeQuery(v*2, tl, tm, l, min(r,tm)) + rangeQuery(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
};

// point update range query
struct SegTree_PointRange
{
    int n;
    vector<long long> tree;

    SegTree_PointRange(int n_, vector<long long>& a): n(n_)
    {
        tree.resize(4*n, 0);
        build(a,0,n-1,1);
    }

    void build(vector<long long>& a, int tl, int tr, int v)
    {
        if (tl == tr) {tree[v] = a[tl]; return;}
        int tm = (tl + tr) / 2;
        build(a, tl, tm, 2*v);
        build(a, tm+1, tr, 2*v+1);
        tree[v] = tree[v*2] + tree[v*2+1];
    }

    void update(int pos, long long add)
    {
        update(1,0,n-1,pos,add);
    }

    void update(int v, int tl, int tr, int pos, long long add)
    {
        if (tl == tr) { tree[v] += add; return; }
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2,tl,tm,pos,add);
        else update(2*v+1, tm+1,tr,pos,add);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    long long query(int l, int r)
    {
        return query(1,0,n-1,l,r);
    }

    long long query(int v, int tl, int tr, int l, int r)
    {
        if (l > r) return 0;
        if (tl == l && tr == r) return tree[v];
        int tm = (tl+tr) /2;
        return query(2*v, tl, tm, l, min(r,tm)) + query(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
};

// range update point query
struct SegTree_RangePoint
{
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    SegTree_RangePoint(int n_, vector<long long>& a): n(n_)
    {
        tree.resize(4*n, 0);
        lazy.resize(4*n, 0);
        build(a,0,n-1,1);
    }

    void build(vector<long long>& a, int tl, int tr, int v)
    {
        if (tl == tr) {tree[v] = a[tl]; return;}
        int tm = (tr + tl) / 2;
        build(a,tl,tm,v*2);
        build(a,tm+1, tr, 2*v+1);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    void push(int v, int tl, int tr)
    {
        if (lazy[v] == 0 || tl == tr) return;
        long long add = lazy[v];
        int tm = (tr + tl) / 2;

        lazy[2*v] += add;
        lazy[2*v+1] += add;

        tree[2*v] += add * (tm - tl + 1);
        tree[2*v+1] += add * (tr - (tm + 1) + 1);

        lazy[v] = 0;
    }

    void update(int l, int r, long long add)
    {
        update(1, 0, n-1, l, r, add);
    }

    void update(int v, int tl, int tr, int l, int r, long long add)
    {
        if (l > r) return;
        if (tl == l && tr == r)
        {
            tree[v] += add * (tr - tl + 1);
            lazy[v] += add;
            return;
        }
        push(v,tl,tr);
        int tm = (tl + tr) / 2;
        update(2*v, tl, tm, l, min(r,tm), add);
        update(2*v+1, tm+1, tr, max(l, tm+1), r, add);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    long long query(int pos)
    {
        return query(1,0,n-1,pos);
    }

    long long query(int v, int tl, int tr, int pos)
    {
        if (tl == tr) return tree[v];
        push(v,tl,tr);
        int tm = (tr + tl) / 2;
        if (pos <= tm) return query(2*v, tl, tm, pos);
        else return query(2*v+1, tm+1, tr, pos);
    }
};

static long long sumRange(const vector<long long>& a, int l, int r) {
    long long s = 0;
    for (int i = l; i <= r; i++) s += a[i];
    return s;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr);

    {
        vector<long long> a = {1,2,3,4,5};
        SegTree_RangeRange st((int)a.size(), a);

        bool ok1 = (st.rangeQuery(0,4) == 15);
        st.update(1,3,10);
        a[1]+=10; a[2]+=10; a[3]+=10;
        bool ok2 = (st.rangeQuery(1,3) == sumRange(a,1,3));
        cout << "SegTree_RangeRange test 1: " << (ok1 ? "PASS" : "FAIL") << "\n";
        cout << "SegTree_RangeRange test 2: " << (ok2 ? "PASS" : "FAIL") << "\n";
    }

    {
        vector<long long> a = {5,-2,7,0,3};
        SegTree_PointRange st((int)a.size(), a);

        bool ok1 = (st.query(0,2) == (5 + -2 + 7));
        st.update(2, 5);
        a[2] += 5;
        bool ok2 = (st.query(1,4) == sumRange(a,1,4));
        cout << "SegTree_PointRange test 1: " << (ok1 ? "PASS" : "FAIL") << "\n";
        cout << "SegTree_PointRange test 2: " << (ok2 ? "PASS" : "FAIL") << "\n";
    }

    {
        vector<long long> a = {3,1,4,1,5};
        SegTree_RangePoint st((int)a.size(), a);

        bool ok1 = (st.query(2) == 4);
        st.update(1,4,7);
        a[1]+=7; a[2]+=7; a[3]+=7; a[4]+=7;
        bool ok2 = (st.query(0) == a[0]) && (st.query(4) == a[4]) && (st.query(2) == a[2]);
        cout << "SegTree_RangePoint test 1: " << (ok1 ? "PASS" : "FAIL") << "\n";
        cout << "SegTree_RangePoint test 2: " << (ok2 ? "PASS" : "FAIL") << "\n";
    }

    return 0;
}