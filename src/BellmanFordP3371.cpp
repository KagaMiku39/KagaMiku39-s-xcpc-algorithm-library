#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    vector<int> dp(n + 1, INT_MAX);
    dp[s] = 0;
    for (int i = 1; i < n; i ++) {
        bool flag = false;
        for (int u = 1; u <= n; u ++) {
            if (dp[u] == INT_MAX) {
                continue;
            }
            for (auto &[v, w]: adj[u]) {
                flag |= cmin(dp[v], dp[u] + w);
            }
        }
        if (!flag) {
            break;
        }
    }
    
    for (int i = 1; i <= n; i ++) {
        cout << dp[i] << " \n"[i == n];
    }

    return 0;
}