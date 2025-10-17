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
    for (int i = 1; i <= n; i ++) {
        adj[i][i] = 0;
    }
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        cmin(adj[u][v], w);
        cmin(adj[v][u], w);
    }

    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                if (adj[i][k] == INT_MAX || adj[k][j] == INT_MAX) {
                    continue;
                }
                cmin(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            cout << adj[i][j] << " \n"[j == n];
        }
    }

    return 0;
}