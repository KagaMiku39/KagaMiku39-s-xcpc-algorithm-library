#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int clk = 0;
    vector<int> dfn(n * 2 + 1), low(n * 2 + 1);
    vector<int> p(n * 2 + 1);
    vector<i64> pw(n * 2 + 1);
    
    vector<vector<pair<int, int>>> tree(n * 2 + 1);
    int cnt = n;

    vector<i64> d_cyc(n * 2 + 1), l_cyc(n * 2 + 1);

    auto build_cyc = [&](int u, int v, int w) { // u: top of cycle, v: bottom
        cnt++;
        i64 sum = w;
        for (int k = v; k != u; k = p[k]) {
            d_cyc[k] = sum;
            sum += pw[k];
        }
        i64 total_len = sum;

        tree[u].emplace_back(cnt, 0);
        tree[cnt].emplace_back(u, 0);

        for (int k = v; k != u; k = p[k]) {
            l_cyc[k] = total_len;
            tree[k].emplace_back(cnt, min(d_cyc[k], total_len - d_cyc[k]));
            tree[cnt].emplace_back(k, min(d_cyc[k], total_len - d_cyc[k]));
        }
    };

    function<void(int, int)> tarjan = 
        [&](int u, int fa) {
        dfn[u] = low[u] = ++clk;
        for (auto& [v, w] : adj[u]) {
            if (v == fa) continue;
            if (!dfn[v]) {
                p[v] = u;
                pw[v] = w;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    tree[u].emplace_back(v, w);
                    tree[v].emplace_back(u, w);
                }
            } else if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
                build_cyc(v, u, w);
            }
        }
    };
    
    tarjan(1, 0);

    int LOGN = 20;
    vector<vector<int>> up(cnt + 1, vector<int>(LOGN));
    vector<i64> dis(cnt + 1);
    vector<int> dep(cnt + 1);

    function<void(int, int, i64, int)> dfs_lca = 
        [&](int u, int fa, i64 d, int depth) {
        up[u][0] = fa;
        dis[u] = d;
        dep[u] = depth;
        for (int i = 1; i < LOGN; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto& [v, w] : tree[u]) {
            if (v == fa) continue;
            dfs_lca(v, u, d + w, depth + 1);
        }
    };

    dfs_lca(1, 0, 0, 1);

    int u_son = 0, v_son = 0;
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = LOGN - 1; i >= 0; --i) {
            if (dep[up[u][i]] >= dep[v]) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOGN - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        u_son = u;
        v_son = v;
        return up[u][0];
    };

    while (q--) {
        int u, v;
        cin >> u >> v;
        int p = lca(u, v);
        if (p <= n) {
            cout << dis[u] + dis[v] - 2 * dis[p] << '\n';
        } else {
            i64 len = abs(d_cyc[u_son] - d_cyc[v_son]);
            i64 d_ab = min(len, l_cyc[u_son] - len);
            cout << dis[u] + dis[v] - dis[u_son] - dis[v_son] + d_ab << '\n';
        }
    }

    return 0;
}