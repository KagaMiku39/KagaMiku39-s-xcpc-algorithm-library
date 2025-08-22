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

    vector<int> dis(n + 1, INT_MAX), vis(n + 1);
    queue<int> q;
    dis[s] = 0;
    vis[s] = true;
    q.emplace(s);
    while (ssize(q)) {
        int u = q.front(), d = dis[u];
        vis[u] = false;
        q.pop();
        for (auto &[v, w]: adj[u]) {
            if (!cmin(dis[v], d + w) || vis[v]) {
                continue;
            }
            vis[v] = true;
            q.emplace(v);
        }
    }

    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}