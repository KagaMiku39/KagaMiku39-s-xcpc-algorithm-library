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

    int dis = -1;
    vector<int> d(n + 1), ver{-1};
    auto dfs = [&](auto &self, int u, int p) -> void {
        for (int &v: adj[u]) {
            if (v == p) {
                continue;
            }
            d[v] = d[u] + 1;
            if (cmax(dis, d[v])) {
                ver.pop_back();
                ver.emplace_back(v);
            }
            self(self, v, u);
        }
    };
    
    
    dfs(dfs, 1, 0);

    dis = -1;

    d[ver.front()] = 0;

    ver.emplace_back(-1);

    dfs(dfs, ver.front(), 0);

    cout << d[ver.back()] << '\n';

    return 0;
}