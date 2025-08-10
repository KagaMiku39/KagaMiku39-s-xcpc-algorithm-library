#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> w(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i ++) {
        int u, v;
        cin >> w[i] >> u >> v;
        auto addedge = [&](int x) {
            if (!x) {
                return;
            }
            adj[i].emplace_back(x);
            adj[x].emplace_back(i); 
        };
        addedge(u);
        addedge(v);
    }

    vector<int> sz = w, dep(n + 1), dp(n + 1);
    auto dfs1 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dep[v] = dep[u] + 1; 
            self(self, v, u);
            sz[u] += sz[v];
        }
        dp[1] += dep[u] * w[u];
    };
    dfs1(dfs1, 1, 0);
    
    int ans = INT_MAX;
    auto dfs2 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            dp[v] = dp[u] + sz[1] - 2 * sz[v];
            self(self, v, u);
        }
        cmin(ans, dp[u]);
    };
    dfs2(dfs2, 1, 0);
    
    cout << ans << '\n';

    return 0;
}