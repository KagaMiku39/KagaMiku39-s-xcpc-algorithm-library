#include <bits/stdc++.h>

using namespace std;

constexpr int logn = 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v; 
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    vector<int> dep(n + 1);
    vector<vector<int>> up(n + 1, vector<int>(logn + 1));
    dep[1] = 1;
    auto dfs = [&](auto self, int u, int pa) -> void {
        for (int i = 1; i <= logn; i ++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto v: adj[u]) {
            if (v == pa) {
                continue;
            }
            up[v][0] = u;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, s, 0);

    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        for (int i = logn; ~i; i --) {
            if (dep[u] - (1 << i) >= dep[v]) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn; ~i; i --) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    };
    
    for (int i = 1, a, b; i <= m; i ++) {
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }

    return 0;
}