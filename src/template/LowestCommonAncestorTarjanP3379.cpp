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

    // void merge(int a, int b) {
    //     int pa = find(a), pb = find(b);
    //     if (pa == pb) {
    //         return;
    //     }
    //     if (rk[pa] > rk[pb]) {
    //         swap(pa, pb);
    //     }
    //     p[pa] = pb;
    //     rk[pb] += rk[pa] == rk[pb];
    // }

    void merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) {
            return;
        }
        if (sz[pa] > sz[pb]) {
            swap(pa, pb);
        }
        p[pa] = pb;
        sz[pb] += sz[pa];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<int>> adj(n + 1);
    
    vector<vector<pair<int, int>>> q(n + 1);
    
    for (int i = 1; i < n; i ++) {
        int u, v; 
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    for (int i = 1; i <= m; i ++) {
        int a, b; 
        cin >> a >> b;
        q[a].emplace_back(i, b);
        q[b].emplace_back(i, a);
    }
    
    DisjointSetUnion dsu(n);
    vector<int> vis(n + 1), ans(m + 1);
    auto tarjan = [&](auto self, int u) -> void {
        vis[u] = 1;
        for (int &v: adj[u]) {
            if (!vis[v]) {
                self(self, v);
                dsu.p[dsu.find(v)] = u;
            }
        }
        for (auto &[id, nd]: q[u]) {
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