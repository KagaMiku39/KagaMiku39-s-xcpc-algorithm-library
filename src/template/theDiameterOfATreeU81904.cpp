#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    i64 ans = 0;
    vector<i64> dp(n + 1);
    auto dfs = [&](auto &self, int u, int p) -> void {
        for (auto &[v, w]: adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            cmax(ans, dp[u] + dp[v] + w);
            cmax(dp[u], dp[v] + w);
        }
    };
    dfs(dfs, 1, 0);

    cout << ans << '\n';
    
    return 0;
}