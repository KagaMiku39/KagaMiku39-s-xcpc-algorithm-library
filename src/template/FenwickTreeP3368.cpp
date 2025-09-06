#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct FenwickTree {
    int n;

    vector<T> bit;

    FenwickTree(int n, vector<T> &vec) : n(n), bit(n + 1) {
        for (int i = 1; i <= n; i ++) {
            add(i, vec[i]);
            add(i + 1, -vec[i]);
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
            int y, k;
            cin >> y >> k;
            bit.add(x, k);
            bit.add(y + 1, -k);
        }
        if (opt == 2) {
            cout << bit.query(x) << '\n';
        }
    }

    return 0;
}