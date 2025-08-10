#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, e;
    cin >> n >> m >> e;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < e; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    
    vector<int> mat(m + 1), vis(m + 1);
    int res = 0;

    auto hungarian = [&](auto self, int u) -> bool {
        for (const int &v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                if (mat[v] == 0 || self(self, mat[v])) {
                    mat[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    
    for (int i = 1; i <= n; i ++) {
        fill(begin(vis), end(vis), false);
        if (hungarian(hungarian, i)) {
            res ++;
        }
    }
    
    cout << res << '\n';

    return 0;
}