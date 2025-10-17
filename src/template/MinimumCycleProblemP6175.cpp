#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        cmin(adj[u][v], w);
        cmin(adj[v][u], w);
        cmin(dp[u][v], w);
        cmin(dp[v][u], w);
    }

    for (int i = 1; i <= n; i++) {
        adj[i][i] = 0;
        dp[i][i] = 0;
    }
    
    int ans = INT_MAX;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (dp[i][j] != INT_MAX && adj[i][k] != INT_MAX && adj[k][j] != INT_MAX) {
                    cmin(ans, dp[i][j] + adj[i][k] + adj[k][j]);
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dp[i][k] != INT_MAX && dp[k][j] != INT_MAX) {
                    cmin(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
    }
    
    if (ans != INT_MAX) {
        cout << ans << '\n';
    } else {
        cout << "No solution.\n";
    }

    return 0;
}