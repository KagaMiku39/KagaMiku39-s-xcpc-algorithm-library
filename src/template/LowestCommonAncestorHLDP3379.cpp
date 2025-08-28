#include <bits/stdc++.h>

using namespace std;

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
    
    vector<int> p(n + 1), sz(n + 1, 1), dep(n + 1), ch(n + 1);
    sz[0] = 0, dep[s] = 1;
    auto dfs1 = [&](auto &self, int u, int pa) -> void {
        p[u] = pa;
        for (int &v: adj[u]) {
            if (v == pa) {
                continue;
            }
            dep[v] = dep[u] + 1;
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[ch[u]] < sz[v]) {
                ch[u] = v;
            }
        }
    };
    dfs1(dfs1, s, 0);

    vector<int> tp(n + 1);
    auto dfs2 = [&](auto &self, int u, int top) -> void {
        tp[u] = top;
        if (!ch[u]) {
            return;
        }
        self(self, ch[u], top);
        for (int &v: adj[u]) {
            if (v == p[u] || v == ch[u]) {
                continue;
            }
            self(self, v, v);
        }
    };
    dfs2(dfs2, s, s);

    auto lca = [&](int a, int b) {
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            a = p[tp[a]];
        }
        return dep[a] < dep[b] ? a : b;
    };
    
    for (int i = 1; i <= m; i ++) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }

    return 0;
}