#include <bits/stdc++.h>

#define ssize(x) int(x.size())

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

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edg(m + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            continue;
        }
        adj[u].emplace_back(i);
        adj[v].emplace_back(i);
        edg[i] = {u, v};
    }
    
    int idx = 0;
    vector<int> dfn(n + 1), low(n + 1), isbridge(m + 1);
    auto tarjan = [&](auto &self, int u, int pid) -> void {
        dfn[u] = low[u] = ++ idx;
        for (int eid: adj[u]) {
            if (eid == pid) {
                continue;
            }
            int v = edg[eid].first ^ edg[eid].second ^ u; 
            if (dfn[v] == 0) {
                self(self, v, eid);
                cmin(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    isbridge[eid] = true; 
                }
            } else {
                cmin(low[u], dfn[v]);
            }
        }
    };
    
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(tarjan, i, 0);
        }
    }

    int cnt = 0;
    vector<int> id(n + 1); 
    auto dfs = [&](auto &self, int u) -> void {
        id[u] = cnt;
        for (int eid : adj[u]) {
            if (isbridge[eid]) {
                continue;
            }
            int v = edg[eid].first ^ edg[eid].second ^ u;
            if (id[v] == 0) { 
                self(self, v);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!id[i]) {
            cnt ++;
            dfs(dfs, i);
        }
    }
    
    vector<vector<int>> ebcc(cnt + 1);
    for (int i = 1; i <= n; i++) {
        ebcc[id[i]].emplace_back(i);
    }
    
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) {
        cout << ssize(ebcc[i]);
        for (int nd : ebcc[i]) {
            cout << ' ' << nd;
        }
        cout << '\n';
    }

    return 0;
}