#include <bits/stdc++.h>

using namespace std;

struct DisjointSetUnion {
    vector<int> p, rk, sz;

    DisjointSetUnion(int n) : p(n + 1), rk(n + 1), sz(n + 1, 1) {
        iota(begin(p), end(p), 0);
    }

    int find(int x) {
        while (x != p[x]) {
            x = p[x] = p[p[x]];
        }
        return x;
    }

    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

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
    
    vector<vector<pair<int, int>>> que(n + 1);
    for (int i = 1; i <= m; i ++) {
        int a, b; 
        cin >> a >> b;
        que[a].emplace_back(i, b);
        que[b].emplace_back(i, a);
    }
    
    DisjointSetUnion dsu(n);
    vector<int> vis(n + 1), ans(m + 1);
    auto tarjan = [&](auto &self, int u) -> void {
        vis[u] = 1;
        for (int &v: adj[u]) {
            if (!vis[v]) {
                self(self, v);
                dsu.p[dsu.find(v)] = u;
            }
        }
        for (auto &[id, nd]: que[u]) {
            if (vis[nd]) {
                ans[id] = dsu.find(nd);
            }
        }
    };
    tarjan(tarjan, s);
    
    for (int i = 1; i <= m; i ++) {
        cout << ans[i] << '\n';
    }
    
    return 0;
}