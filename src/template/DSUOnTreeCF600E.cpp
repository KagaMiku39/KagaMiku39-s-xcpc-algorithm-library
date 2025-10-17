#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    vector<int> sz(n + 1, 1), p(n + 1), ch(n + 1);
    sz[0] = 0;
    auto dfs1 = [&](auto &self, int u, int pa) -> void {
        p[u] = pa;
        for (int &v: adj[u]) {
            if (v == pa) {
                continue;
            }
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[ch[u]]) {
                ch[u] = v;
            }
        }
    };
    dfs1(dfs1, 1, 0);

    int mx = 0;
    i64 sum = 0;
    vector<int> col(n + 1);
    vector<i64> ans(n + 1);
    auto foo = [&](int x) {
        if (col[c[x]] >= mx) {
            if (col[c[x]] == mx) {
                sum += c[x];
            } else {
                sum = c[x];
            }
            mx = col[c[x]];
        }
    };
    auto dfs2 = [&](auto &self, int u, int off) -> void {
        col[c[u]] += off;
        if (~off) {
            foo(u);
        }
        for (int &v: adj[u]) {
            if (v == p[u]) {
                continue;
            }
            self(self, v, off);
        }
    };        
    auto dfs3 = [&](auto &self, int u, bool tag) -> void {
        for (int &v: adj[u]) {
            if (v == p[u] || v == ch[u]) {
                continue;
            }
            self(self, v, true);
        }
        if (ch[u]) {
            self(self, ch[u], false);
        }
        for (int &v: adj[u]) {
            if (v == p[u] || v == ch[u]) {
                continue;
            }
            dfs2(dfs2, v, 1);
        }
        col[c[u]] ++;
        foo(u);
        ans[u] = sum;
        if (tag) {
            sum = mx = 0;
            dfs2(dfs2, u, -1);
        }
    };
    dfs3(dfs3, 1, 1);
    
    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << " \n"[i == n];
    }
    
    return 0;
}