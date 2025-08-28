#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        if (w >= 0) {
            adj[v].emplace_back(u, w);
        }
    }

    vector<int> dis(n + 1, INT_MAX);
    dis[1] = 0;

    // auto bellmanford = [&]() {
    //     bool tag = false;
    //     for (int i = 1; i <= n; i ++) {
    //         tag = false;
    //         for (int u = 1; u <= n; u ++) {
    //             int d = dis[u];
    //             if (d == INT_MAX) {
    //                 continue;
    //             }
    //             for (auto &[v, w]: adj[u]) {
    //                 tag |= cmin(dis[v], d + w);
    //             }
    //         }
    //         if (!tag) {
    //             break;
    //         }
    //     }
    //     return tag;
    // };

    auto spfa = [&]() {
        vector<int> vis(n + 1), cnt(n + 1);
        queue<int> q;
        cnt[1] = 1;
        vis[1] = 1;
        q.emplace(1);
        while (ssize(q)) {
            int u = q.front(), d = dis[u], c = cnt[u];
            vis[u] = false;
            q.pop();
            for (auto &[v, w]: adj[u]) {
                if (!cmin(dis[v], d + w) || vis[v]) {
                    continue;
                }
                vis[v] = true;
                cnt[v] = c + 1;
                if (cnt[v] > n) {
                    return true;
                }
                q.emplace(v);
            }
        }
        return false;
    };

    // cout << (bellmanford() ? "YES\n" : "NO\n");

    cout << (spfa() ? "YES\n" : "NO\n");
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