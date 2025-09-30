#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int logn = 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int clk = 0, cnt = n;
    vector<int> dfn(n * 2 + 1), low(n * 2 + 1), p(n * 2 + 1);
    vector<i64> pw(n * 2 + 1), dcyc(n * 2 + 1), lcyc(n * 2 + 1);
    vector<vector<pair<int, int>>> tr(n * 2 + 1);
    auto build = [&](int u, int v, int w) {
        cnt ++;
        i64 sum = w;
        for (int k = v; k != u; k = p[k]) {
            dcyc[k] = sum;
            sum += pw[k];
        }
        i64 tot = sum;

        tr[u].emplace_back(cnt, 0);
        tr[cnt].emplace_back(u, 0);

        for (int k = v; k != u; k = p[k]) {
            lcyc[k] = tot;
            i64 weight = min(dcyc[k], tot - dcyc[k]);
            tr[k].emplace_back(cnt, weight);
            tr[cnt].emplace_back(k, weight);
        }
    };

    auto tarjan = [&](auto &self, int u, int pa) -> void {
        dfn[u] = low[u] = ++ clk;
        for (auto &[v, w] : adj[u]) {
            if (v == pa) {
                continue;
            }
            if (!dfn[v]) {
                p[v] = u;
                pw[v] = w;
                self(self, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    tr[u].emplace_back(v, w);
                    tr[v].emplace_back(u, w);
                }
            } else if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
                build(v, u, w); 
            }
        }
    };    
    tarjan(tarjan, 1, 0);

    vector<i64> dis(cnt + 1);
    vector<int> dep(cnt + 1);
    vector<vector<int>> up(cnt + 1, vector<int>(logn));
    auto dfs = [&](auto &self, int u, int pa, i64 d, int de) -> void {
        up[u][0] = pa;
        dis[u] = d;
        dep[u] = de;
        for (int i = 1; i < logn; i ++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto &[v, w] : tr[u]) {
            if (v == pa) {
                continue;
            }
            self(self, v, u, d + w, de + 1);
        }
    };
    dfs(dfs, 1, 0, 0, 1);

    int uson = 0, vson = 0;
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = logn - 1; i >= 0; --i) {
            if (dep[up[u][i]] >= dep[v]) {
                u = up[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        uson = u;
        vson = v;
        return up[u][0];
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        int p = lca(u, v);
        if (p <= n) {
            cout << dis[u] + dis[v] - 2 * dis[p] << '\n';
        } 
        else {
            i64 len = abs(dcyc[uson] - dcyc[vson]), dab = min(len, lcyc[uson] - len);
            cout << dis[u] + dis[v] - dis[uson] - dis[vson] + dab << '\n';
        }
    }

    return 0;
}