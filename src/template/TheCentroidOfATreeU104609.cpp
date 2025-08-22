#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> cen, sz(n + 1, 1);
    auto dfs = [&](auto &self, int u, int p) -> void {
        int mx = 0;
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            self(self, v, u);
            sz[u] += sz[v];
            cmax(mx, sz[v]);
        }
        cmax(mx, n - sz[u]);
        if (mx <= n / 2) {
            cen.emplace_back(u);
        }
    };
    dfs(dfs, 1, 0);

    sort(begin(cen), end(cen));

    for (int &i: cen) {
        cout << i << " \n"[i == cen.back()];
    }

    return 0;
}