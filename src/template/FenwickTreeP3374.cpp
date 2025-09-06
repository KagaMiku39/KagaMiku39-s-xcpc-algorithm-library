#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct FenwickTree {
    int n;

    vector<T> bit;

    FenwickTree(int n, vector<T> &vec) : n(n), bit(n + 1) {
        for (int i = 1; i <= n; i ++) {
            add(i, vec[i]);
        }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, T val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    
    T query(int lo, int ro) {
        return query(ro) - query(lo - 1);
    }
    
    T query(int pos) {
        T res = 0;
        while (pos) {
            res += bit[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    FenwickTree<int> bit(n, vec);
    
    while (m --) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            int k;
            cin >> k;
            bit.add(x, k);
        }
        if (opt == 2) {
            int y;
            cin >> y;
            cout << bit.query(y) - bit.query(x - 1) << '\n';
        }
    }

    return 0;
}