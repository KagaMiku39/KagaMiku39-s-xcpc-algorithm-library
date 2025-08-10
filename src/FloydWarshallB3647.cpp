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

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 1; i <= n; i ++) {
        dp[i][i] = 0;
    }
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        cmin(dp[u][v], w);
        cmin(dp[v][u], w);
    }

    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                if (dp[i][k] == INT_MAX || dp[k][j] == INT_MAX) {
                    continue;
                }
                cmin(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << dp[i][j] << " \n"[j == n];
        }
    }

    return 0;
}