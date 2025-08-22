#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> w(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> w[i];
    }

    vector<vector<int>> adj(n + 1); 
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    vector<int> sz(n + 1, 1), ch(n + 1);
    sz[0] = 0;
    auto dfs1 = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[ch[u]] < sz[v]) {
                ch[u] = v;
            }
        }
    };
    dfs1(dfs1, 1, 0);
    
    vector<vector<int>> dp(n + 1, vector<int>(1001)); 
    auto dfs2 = [&](auto &self, int u, int p) -> void {
        if (!ch[u]) {
            dp[u][w[u]] = w[u]; 
            return;
        }
        self(self, ch[u], u);
        swap(dp[u], dp[ch[u]]);
        for (int j = w[u] + 1; j <= 1000; ++j) {
            dp[u][j] = 0;
        }
        for (int &v: adj[u]) {
            if (v == p || v == ch[u]) {
                continue;
            }
            self(self, v, u);
            for (int i = w[u]; i; i --) {
                for (int j = 0; j <= min(w[v], i); j ++) {
                    cmax(dp[u][i], dp[u][i - j] + dp[v][j]);
                }
            }
        }
    };
    dfs2(dfs2, 1, 0);
    
    int ans = 0;
    for (int i = 0; i <= w[1]; i ++) {
        cmax(ans, dp[1][i]);
    }
    
    cout << ans << '\n';
    
    return 0;
}