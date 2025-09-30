#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    vector<int> dis(n + 1, INT_MAX);
    dis[s] = 0;
    for (int i = 1; i < n; i ++) {
        bool tag = false;
        for (int u = 1; u <= n; u ++) {
            if (dis[u] == INT_MAX) {
                continue;
            }
            for (auto &[v, w]: adj[u]) {
                tag |= cmin(dis[v], dis[u] + w);
            }
        }
        if (!tag) {
            break;
        }
    }
    
    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}