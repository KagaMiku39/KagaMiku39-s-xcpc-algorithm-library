#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, T &b) {
	return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, T &b) {
	return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    
    int idx = 0, cnt = 0;
    vector<int> dfn(n + 1), low(n + 1), stk, scc(n + 1), instk(n + 1);
    auto tarjan = [&](auto self, int u) -> void {
        dfn[u] = ++ idx;
        low[u] = dfn[u];
        stk.emplace_back(u);
        instk[u] = 1;
        for (int &v : adj[u]) {
            if (!dfn[v]) {
                self(self, v);
                cmin(low[u], low[v]);
            } else if (instk[v]) {
                cmin(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++;
            int cur = 0;
            do {
                cur = stk.back();
                stk.pop_back();
                instk[cur] = 0;
                scc[cur] = cnt;
            } while (cur != u);
        }
    };
    for (int i = 1; i <= n; i ++) {
        if (!dfn[i]) {
            tarjan(tarjan, i);
        }
    }
    
    cout << cnt << '\n';
    
    vector<vector<int>> ans(cnt + 1);
    for (int i = 1; i <= n; i ++) {
        ans[scc[i]].emplace_back(i);
    }
    
    vector<int> vis(cnt + 1);
    for (int i = 1; i <= n; i ++) {
        if (!vis[scc[i]]) {
            sort(begin(ans[scc[i]]), end(ans[scc[i]]));
            for (int j = 0; j < ssize(ans[scc[i]]); j ++) {
                cout << ans[scc[i]][j] << " \n"[j == ssize(ans[scc[i]]) - 1];
            }
            vis[scc[i]] = true;
        }
    }

    return 0;
}