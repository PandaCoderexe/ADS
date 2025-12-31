#include <iostream>
#include <vector>

using namespace std;

class SegmentTree
{
public:
    SegmentTree(const vector<long long>& a_)
    {
        a = a_;
        N = (int)a.size();
        segTree.assign(4*N+5,0);

        build(0,N-1,0);
    }

    long long querySum(int ql,int qr)
    {
        return querySum(0, 0, N-1, ql, qr);
    }

    void pointUpdate(int pos, long long val)
    {
        pointUpdate(0, 0, N-1, pos, val);
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
            int mid = (l+r)/2;

            build(l, mid, 2*idx+1);
            build(mid+1, r, 2*idx+2);

            segTree[idx] = segTree[2*idx+1] + segTree[2*idx+2];
        }
    }

    long long querySum(int idx, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return segTree[idx];
        int mid = (l+r)/2;
        return querySum(2*idx+1, l, mid, ql,qr) + querySum(2*idx+2, mid+1, r, ql,qr);
    }

    void pointUpdate(int idx, int l, int r, int pos, long long val)
    {
        if (l == r)
        {
            a[pos] = val;
            segTree[idx] = val;
            return; 
        }

        int mid = (l+r)/2;
        if (pos <= mid) pointUpdate(2*idx+1, l, mid, pos, val);
        else pointUpdate(2*idx+2, mid+1, r, pos, val);

        segTree[idx] = segTree[2*idx+1] + segTree[2*idx+2];
    }

    int N; // lenght of seg tree array
    vector<long long> a;
    vector<long long> segTree;
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

    cout << "\nUpdate: a[2] = 10\n";
    st.pointUpdate(2, 10);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 22)\n";
    cout << "sum(1,3) = " << st.querySum(1,3) << " (expected 16)\n";
    cout << "sum(2,2) = " << st.querySum(2,2) << " (expected 10)\n";

    cout << "\nUpdate: a[0] = -7\n";
    st.pointUpdate(0, -7);

    cout << "sum(0,4) = " << st.querySum(0,4) << " (expected 14)\n";
    cout << "sum(0,1) = " << st.querySum(0,1) << " (expected -5)\n";

    return 0;
}