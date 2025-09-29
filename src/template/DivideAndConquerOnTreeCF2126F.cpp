#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    i64 ans = 0;
    vector<int> p(n + 1);
    map<pair<int, int>, i64> mp, edg;
    auto dfs = [&](auto &self, int u) -> void {
        for (auto &[v, w]: adj[u]) {
            edg[{u, v}] = w;
            if (v == p[u]) {
                continue;
            }
            if (a[v] != a[u]) {
                ans += w;
            }
            p[v] = u;
            mp[{u, a[v]}] += w;
            self(self, v);
        }  
    };
    dfs(dfs, 1);
    
    while (q --) {
        int v, x;
        cin >> v >> x;
        if (a[v] == x) {
            cout << ans << '\n';
            continue;
        }
        ans += mp[{v, a[v]}];
        ans -= mp[{v, x}];
        int w = edg[{p[v], v}];
        if (a[v] == a[p[v]]) {
            ans += w;            
        } else if (x == a[p[v]]) {
            ans -= w;
        }
        mp[{p[v], a[v]}] -= w;
        mp[{p[v], x}] += w;
        a[v] = x;
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}