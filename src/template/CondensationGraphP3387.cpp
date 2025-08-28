#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
	return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    
    int idx = 0, cnt = 0;
    vector<vector<int>> t(n + 1);
    vector<int> dfn(n + 1), low(n + 1), scc(n + 1), stk, instk(n + 1);
    auto tarjan = [&](auto &self, int u) -> void {
        dfn[u] = ++idx;
        low[u] = dfn[u];
        stk.emplace_back(u);
        instk[u] = 1;
        for (int& v : adj[u]) {
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
    
    vector<int> w(cnt + 1);
    for (int i = 1; i <= n; i ++) {
        w[scc[i]] += a[i];
    }
    
    for (int u = 1; u <= n; u ++) {
        for (int& v : adj[u]) {
            if (scc[u] != scc[v]) {
                t[scc[u]].emplace_back(scc[v]);
            }
        }
    }

    vector<int> dp(cnt + 1), vis(cnt + 1);
    auto dfs = [&](auto &self, int u) -> void {
        vis[u] = 1;
        for (int& v : t[u]) {
            if (!vis[v]) {
                self(self, v);
            }
            cmax(dp[u], dp[v]);
        }
        dp[u] += w[u];
    };
    for (int i = 1; i <= cnt; i ++) {
        if(!vis[i]){
            dfs(dfs, i);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= cnt; i ++) {
        cmax(ans, dp[i]);
    }
    
    cout << ans << '\n';

    return 0;
}