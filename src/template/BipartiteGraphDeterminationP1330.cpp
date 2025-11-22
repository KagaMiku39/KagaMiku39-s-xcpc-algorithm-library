#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    int ans = 0;
    bool tag = false;
    vector<int> c(n + 1, -1);
    for (int i = 1; i <= n; i ++) {
        if (!~c[i]) {
            int sum[2]{};
            auto dfs = [&](auto &self, int u, int col) -> bool {
                c[u] = col;
                sum[col] ++;
                for (int &v: adj[u]) {
                    if (!~c[v]) {
                        if (self(self, v, col ^ 1)) {
                            return true;
                        }
                    }
                    if (c[v] == col) {
                        return true;
                    }
                }
                return false;
            };
            if (dfs(dfs, i, 1)) {
                tag = true;
                break;
            }
            ans += min(sum[0], sum[1]);
        }
    }

    if (tag) {
        cout << "Impossible\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}