#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> key(k + 1);
    vector<vector<int>> dp(n + 1, vector<int>(1 << k, INT_MAX));
    for (int i = 1; i <= k; i++) {
        cin >> key[i];
        dp[key[i]][1 << (i - 1)] = 0;
    }

    for (int s = 1; s < 1 << k; s++) {
        for (int i = 1; i <= n; i++) {
            for (int sub = s & (s - 1); sub; sub = s & (sub - 1)) {
                int com = s ^ sub;
                if (dp[i][sub] != INT_MAX && dp[i][com] != INT_MAX) {
                    cmin(dp[i][s], dp[i][sub] + dp[i][com]);
                }
            }
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 1; i <= n; i++) {
            if (dp[i][s] != INT_MAX) {
                pq.emplace(dp[i][s], i);
            }
        }
        while (ssize(pq)) {
            auto [val, u] = pq.top();
            pq.pop();
            if (val > dp[u][s]) {
                continue;
            }
            for (auto &[v, w] : adj[u]) {
                if (cmin(dp[v][s], val + w)) {
                    pq.emplace(dp[v][s], v);
                }
            }
        }
    }
    
    cout << dp[key[1]][(1 << k) - 1] << '\n';

    return 0;
}