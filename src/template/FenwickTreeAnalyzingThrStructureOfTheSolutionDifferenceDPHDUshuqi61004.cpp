#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
struct FenwickTree {
    int n;

    vector<T> bit;

    FenwickTree(int n) : n(n), bit(n + 1, numeric_limits<T>::max()) {}

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, T val) {
        while (pos <= n) {
            cmin(bit[pos], val);
            pos += lowbit(pos);
        }
    }
    
    T query(int pos) {
        T res = numeric_limits<T>::max();
        while (pos) {
            cmin(res, bit[pos]);
            pos -= lowbit(pos);
        }
        return res;
    }
};

void solve() {   
    int n;
    cin >> n;

    vector<int> p(n + 2), id(n + 2);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
        id[p[i]] = i;
    }
    p[n + 1] = n + 1;
    id[n + 1] = n + 1; 

    vector<int> dp(n + 2, INT_MAX);
    FenwickTree<int> bit(n + 1);
    dp[0] = 0;
    bit.add(1, 0);
    for (int i = 1; i <= n + 1; i ++) {
        dp[i] = bit.query(id[i]) + i;
        if (id[i] > id[i - 1]) {
            cmin(dp[i], dp[i - 1]);
        }
        bit.add(id[i] + 1, dp[i] - i);
    }

    cout << dp[n + 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}