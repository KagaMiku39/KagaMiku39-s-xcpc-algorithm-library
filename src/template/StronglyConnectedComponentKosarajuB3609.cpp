#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        radj[v].emplace_back(u);
    }
    
    vector<int> vis(n + 1), stk;
    auto dfs1 = [&](auto &self, int u) -> void {
        vis[u] = true;
        for (int &v: adj[u]) {
            if (!vis[v]) {
                self(self, v);
            }
        }
        stk.emplace_back(u);
    };

    int cnt = 0;
    vector<int> scc(n + 1);
    auto dfs2 = [&](auto &self, int u) -> void {
        vis[u] = true;
        scc[u] = cnt;
        for (int &v: radj[u]) {
            if (!vis[v]) {
                self(self, v);
            }
        }
    };

    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) {
            dfs1(dfs1, i);
        }
    }
    
    fill(next(begin(vis)), end(vis), false);
    
    for (int i = ssize(stk) - 1; ~i; i --) {
        int u = stk[i];
        if (!vis[u]) {
            cnt ++;
            dfs2(dfs2, u);
        }
    }
    
    cout << cnt << '\n';
    
    vector<vector<int>> ans(cnt + 1);
    for (int i = 1; i <= n; i ++) {
        ans[scc[i]].emplace_back(i);
    }

    vector<int> tag(cnt + 1);
    for (int i = 1; i <= n; i ++) {
        if (!tag[scc[i]]) {
            sort(begin(ans[scc[i]]), end(ans[scc[i]]));
            for (int j = 0; j < ssize(ans[scc[i]]); j ++) {
                cout << ans[scc[i]][j] << " \n"[j == ssize(ans[scc[i]]) - 1];
            }
            tag[scc[i]] = true;
        }
    }

    return 0;
}