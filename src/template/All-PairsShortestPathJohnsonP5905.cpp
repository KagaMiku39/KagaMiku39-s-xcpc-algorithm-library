#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    for (int i = 1; i <= n; i ++) {
        adj[0].emplace_back(i, 0);
    }

    vector<int> h(n + 1, INT_MAX);
    h[0] = 0;
    auto bellmanford = [&]() {
        bool tag = false;
        for (int i = 1; i <= n; i ++) {
            tag = false;
            for (int u = 0; u <= n; u ++) {
                int d = h[u];
                if (d == INT_MAX) {
                    continue;
                }
                for (auto &[v, w]: adj[u]) {
                    tag |= cmin(h[v], d + w);
                }
            }
            if (!tag) {
                break;
            }
        }
        return tag;
    };

    if (bellmanford()) {
        cout << "-1\n";
        return 0;
    }

    for (int u = 0; u <= n; u ++) {
        for (auto &[v, w]: adj[u]) {
            w += h[u] - h[v];
        }
    }

    for (int i = 1; i <= n; i ++) {
        vector<int> vis(n + 1), dis(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, i);
        dis[i] = 0;
        while (ssize(pq)) {
            auto [d, u] = pq.top();
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (auto &[v, w]: adj[u]) {
                if (cmin(dis[v], d + w)) {
                    pq.emplace(dis[v], v);
                }
            }
        }
        i64 ans = 0;
        for (int j = 1; j <= n; j ++) {
            ans += 1ll * j * (dis[j] == INT_MAX ? 1e9 : dis[j] - h[i] + h[j]);
        }
        cout << ans << '\n';
    }

    return 0;
}