#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class FenwickTree
{
public:
    FenwickTree() : n(0) {}

    FenwickTree(int n_, const vector<ll>& a) 
    {
        init(n_);
        buildArray(a);
    }

    void init(int n_)
    {
        n = n_;
        bit.assign(n+1,0);
    }

    void buildArray(const vector<ll>& a)
    {
        for (int i = 1; i <= n; i++) bit[i] = a[i];
        for (int i = 1; i <= n; i++)
        {
            int j = i + (i & -i);
            if (j <= n) bit[j] += bit[i];
        }
    }

    void add(int idx, ll delta)
    {
        for (int i = idx; i <= n; i += i & -i)
            bit[i] += delta;
    }

    ll sumPrefix(int idx) const 
    {
        ll sum = 0;
        while (idx > 0)
        {
            sum += bit[idx];
            idx -= (idx & -idx);
        }

        return sum;
    }

    ll sumRange(int l, int r) const 
    {
        if (l > r) return 0;
        return sumPrefix(r) - sumPrefix(l-1);
    }

private:
    int n;
    vector<ll> bit;

};


int main()
{   
    // lets say n >= 10;
    int n = 10;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    FenwickTree fw = FenwickTree(n, a);

    cout << "Sum on prefix 5 before adding 10: " << fw.sumPrefix(5) << "\n";
    fw.add(5, 10);
    cout << "Sum on prefix 5 after adding 10: " << fw.sumPrefix(5) << "\n";
    cout << "Sum on range from 3 to 7: " << fw.sumRange(3,7) << "\n";

    return 0;
}