#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    int n;

    vector<int> bit;

    FenwickTree(int n, vector<int> &vec) : n(n), bit(n + 1) {
        for (int i = 1; i <= n; i ++) {
            add(i, vec[i]);
            add(i + 1, -vec[i]);
        }
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, int val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    
    int query(int pos) {
        int res = 0;
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
    
    FenwickTree bit(n, vec);
    
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