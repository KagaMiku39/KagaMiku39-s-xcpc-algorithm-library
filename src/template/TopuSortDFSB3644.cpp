#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    
    for (int i = 1; i <= n; i ++) {
        int a; 
        while (cin >> a, a) {
            adj[i].emplace_back(a);
        }
    }

    vector<int> c(n + 1), topu;
    auto dfs = [&](auto &self, int u) -> bool {
        c[u] = -1;
        for (auto &v: adj[u]) {
            if (c[v] < 0) {
                return false;
            }
            if (!c[v] && !self(self, v)) {
                return false;
            }
        }
        c[u] = 1;
        topu.emplace_back(u);
        return true;
    };
    
    for (int i = 1; i <= n; i ++) {
        if (!c[i]) {
            dfs(dfs, i);
        }
    }
    
    reverse(begin(topu), end(topu));

    for (int j = 0; auto &i: topu) {
        cout << i << " \n"[++ j == n];
    }

    return 0;
}