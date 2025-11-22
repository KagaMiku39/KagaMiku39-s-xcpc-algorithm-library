#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n, q;
    cin >> n >> q;

    vector<string> s(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
    }

    map<string, vector<int>> pre;
    for (int i = 1; i <= n; i ++) {
        if (pre.count(s[i])) {
            continue;
        }
        pre[s[i]].resize(n + 1);
        for (int j = 1; j <= n; j ++) {
            pre[s[i]][j] = pre[s[i]][j - 1] + (s[i] == s[j]);
        }
    }

    while (q --) {
        int x, y;
        cin >> x >> y;
        if (x > y) {
            swap(x, y);
        }
        bool ok = false;
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 2; j ++) {
                ok |= s[x][i] == s[y][j];
            }
        }
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 2; j ++) {
                string str = string(1, s[x][i]) + s[y][j];
                if (str[0] > str[1]) {
                    swap(str[0], str[1]);
                }
                if (!pre.count(str)) {
                    continue;
                }
                ok |= pre[str][y] - pre[str][x - 1];
            }
        }
        if (ok) {
            cout << y - x << '\n';
            continue;
        }
        int ans = INT_MAX;
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 2; j ++) {
                string str = string(1, s[x][i]) + s[y][j];
                if (str[0] > str[1]) {
                    swap(str[0], str[1]);
                }
                if (!pre.count(str)) {
                    continue;
                }
                int tmp = lower_bound(begin(pre[str]), end(pre[str]), 1 + pre[str][y]) - begin(pre[str]);
                if (tmp != n + 1) {
                    cmin(ans, 2 * tmp - x - y);
                }
                if (pre[str][x - 1]) {
                    int lo = 0, ro = x - 1;
                    auto pred = [&](int k) {
                        return pre[str][x - 1] - pre[str][k];
                    };
                    while (lo + 1 < ro) {
                        int mid = lo + (ro - lo) / 2;
                        if (pred(mid)) {
                            lo = mid;
                        } else {
                            ro = mid;
                        }
                    }
                    lo ++;
                    cmin(ans, x + y - 2 * lo);
                }
            }
        }
        if (ans != INT_MAX) {
            cout << ans << '\n';
        } else {
            cout << "-1\n";
        }
    }
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