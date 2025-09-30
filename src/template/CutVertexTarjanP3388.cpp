#include <bits/stdc++.h>

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
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    int idx = 0;
    vector<int> dfn(n + 1), low(n + 1), iscut(n + 1);
    for (int i = 1; i <= n; i ++) {
        if (dfn[i] == 0) {
            int rt = i;
            auto tarjan = [&](auto &self, int u, int p) -> void {
                dfn[u] = ++ idx;
                low[u] = dfn[u];
                int ch = 0;
                for (const int &v : adj[u]) {
                    if (v == p) {
                        continue;
                    }
                    if (dfn[v] == 0) {
                        self(self, v, u);
                        cmin(low[u], low[v]);
                        if (low[v] >= dfn[u] && u != rt) {
                            iscut[u] = true;
                        }
                        ch ++;
                    } else {
                        cmin(low[u], dfn[v]);
                    }
                }  
                if (u == rt && ch > 1) {
                    iscut[u] = true;
                }
            };
            tarjan(tarjan, i, 0);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (iscut[i]) {
            ans ++;
        }
    }
    
    cout << ans << '\n';
    
    for (int i = 1; i <= n; i ++) {
        if (iscut[i]) {
            cout << i << " ";
        }
    }
    cout << '\n';

    return 0;
}