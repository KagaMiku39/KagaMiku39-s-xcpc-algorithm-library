#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }

    vector<int> f(n + 1, -1);
    auto sg = [&](auto &self, int u) -> int {
        if (f[u] != -1) {
            return f[u];
        }
        set<int> s;
        for (int v : adj[u]) {
            s.insert(self(self, v));
        }
        int res = 0;
        while (s.count(res)) {
            res ++;
        }
        return f[u] = res;
    };

    vector<int> vec(n + 1);
    for (int i = 1; i <= k; i ++) {
        cin >> vec[i];
    }
    
    int sum = 0;
    for (int i = 1; i <= k; i ++) {
        sum ^= sg(sg, vec[i]);
    }

    cout << (sum ? "win" : "lose") << '\n';

    return 0;
}