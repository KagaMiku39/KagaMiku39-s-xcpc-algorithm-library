#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    
    vector<vector<pair<int, int>>> gr(n + 1);
    for (int i = 1; i <= n; i ++) {
        gr[c[i]].emplace_back(a[i], b[i]);
    }
    
    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i ++) {
        for (int j = m; ~j; j --) {
            for (auto& [w, v] : gr[i]) {
                if (j >= w) {
                    cmax(dp[j], dp[j - w] + v);
                }
            }
        }
    }

    cout << dp[m] << '\n';

    return 0;
}