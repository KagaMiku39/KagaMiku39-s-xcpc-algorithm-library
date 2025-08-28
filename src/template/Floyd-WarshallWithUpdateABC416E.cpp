#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<i64>> adj(n + 2, vector<i64>(n + 2, LLONG_MAX));
    for (int i = 1; i <= n + 1; i ++) {
        adj[i][i] = 0;
    }

    for (int i = 1; i <= m; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        cmin(adj[a][b], 1ll * c);
        cmin(adj[b][a], 1ll * c);
    }

    int k, tt;
    cin >> k >> tt;
    vector<int> d(k + 1);
    for (int i = 1; i <= k; i ++) {
        cin >> d[i]; 
        cmin(adj[d[i]][n + 1], 1ll * tt);
        cmin(adj[n + 1][d[i]], 0ll);
    } 
    
    for (int k = 1; k <= n + 1; k ++) {
        for (int i = 1; i <= n + 1; i ++) {
            for (int j = 1; j <= n + 1; j ++) {
                if (adj[i][k] == LLONG_MAX || adj[k][j] == LLONG_MAX) {
                    continue;
                }
                cmin(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    int q;
    cin >> q;
    
    while (q --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, t;
            cin >> x >> y >> t;
            if (adj[x][y] <= t) {
                continue;
            }
            adj[x][y] = t;
            adj[y][x] = t;
            for (int i = 1; i <= n + 1; i ++) {
                for (int j = 1; j <= n + 1; j ++) {
                    if (adj[i][x] != LLONG_MAX && adj[y][j] != LLONG_MAX) {
                        cmin(adj[i][j], adj[i][x] + t + adj[y][j]);
                    }
                    if (adj[i][y] != LLONG_MAX && adj[x][j] != LLONG_MAX) {
                        cmin(adj[i][j], adj[i][y] + t + adj[x][j]);
                    }
                }
            }
        }
        if (opt == 2) {
            int x;
            cin >> x;
            if (adj[x][n + 1] <= tt) {
                continue;
            }
            adj[x][n + 1] = tt;
            adj[n + 1][x] = 0;
            for (int i = 1; i <= n + 1; i ++) {
                for (int j = 1; j <= n + 1; j ++) {
                    if (adj[i][x] != LLONG_MAX && adj[n + 1][j] != LLONG_MAX) {
                        cmin(adj[i][j], adj[i][x] + tt + adj[n + 1][j]);
                    }
                    if (adj[i][n + 1] != LLONG_MAX && adj[x][j] != LLONG_MAX) {
                        cmin(adj[i][j], adj[i][n + 1] + adj[x][j]);
                    }
                }
            }
        }
        if (opt == 3) {
            i64 ans = 0;
            for (int i = 1; i <= n; i ++) {
                for (int j = 1; j <= n; j ++) {
                    if (adj[i][j] == LLONG_MAX) {
                        continue;
                    }
                    ans += adj[i][j];
                }
            }
            cout << ans << '\n';
        }
    }

    return 0;
}