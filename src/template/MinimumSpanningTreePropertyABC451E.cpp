#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i < n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }

    vector<int> id(n + 1);
    
    iota(next(begin(id)), end(id), 1);
    
    sort(next(begin(id)), end(id), [&](const int &l, const int &r) {
        return a[1][l] < a[1][r];
    });

    vector<vector<pair<int, int>>> adj(n + 1);    
    for (int i = 2; i <= n; i ++) {
        int j = id[i];
        vector<pair<int, int>> tmp;
        for (int k = 1; k < i; k ++) {
            int l = id[k], off = a[j][l];
            if (a[1][j] == a[1][l] + off) {
                tmp.emplace_back(off, l);
            }
        }
        sort(begin(tmp), end(tmp));
        if (tmp.empty()) {
            cout << "No\n";
            return 0;
        }
        if (ssize(tmp) > 1 && tmp[0].first == tmp[1].first) {
            cout << "No\n";
            return 0;
        }
        adj[j].emplace_back(tmp[0].second, a[j][tmp[0].second]);
        adj[tmp[0].second].emplace_back(j, a[j][tmp[0].second]);
    }
    
    for (int i = 1; i < n; i ++) {
        vector<int> dis(n + 1);
        auto dfs = [&](auto &self, int u, int p) -> void {
            for (auto &[v, w]: adj[u]) {
                if (v == p) {
                    continue;
                }
                dis[v] = dis[u] + w;
                self(self, v, u);
            }
        };
        dfs(dfs, i, i);
        for (int j = i + 1; j <= n; j ++) {
            if (dis[j] != a[i][j]) {
                cout << "No\n";
                return 0;
            }
        }
    }

    cout << "Yes\n";
    
    return 0;
}