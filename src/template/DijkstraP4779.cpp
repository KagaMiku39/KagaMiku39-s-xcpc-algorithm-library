#include <bits/stdc++.h>

#define ssize(x) int(x.size())

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

    vector<int> vis(n + 1), dis(n + 1, INT_MAX);
    dis[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    while (ssize(pq)) {
        auto [val, u] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (auto &[v, w]: adj[u]) {
            if (!vis[v] && cmin(dis[v], val + w)) {
                pq.emplace(val + w, v);
            }
        }
    }
    
    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}