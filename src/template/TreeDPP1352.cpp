#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> r(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> r[i];
    }

    vector<int> isroot(n + 1, true);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int v, u;
        cin >> v >> u;
        adj[u].emplace_back(v);        
        isroot[v] = false;
    }

    int rt = 0;
    for (int i = 1; i <= n; i ++) {
        if (isroot[i]) {
            rt = i;
        }
    }

    vector<array<int, 2>> dp(n + 1);
    auto dfs = [&](auto &self, int u) -> void {
        dp[u][1] = r[u];
        for (int &v: adj[u]) {
            self(self, v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };
    dfs(dfs, rt);
    
    int ans = max(dp[rt][0], dp[rt][1]);
    
    cout << ans << '\n';
    
    return 0;
}