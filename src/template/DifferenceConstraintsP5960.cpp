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

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[v].emplace_back(u, w);
    } 

    for (int i = 1; i <= n; i ++) {
        adj[0].emplace_back(i, 0);
    }

    vector<int> dis(n + 1, INT_MAX), vis(n + 1), cnt(n + 1);
    queue<int> q;
    dis[0] = 0;
    vis[0] = true;
    cnt[0] = 1;
    auto spfa = [&]() {
        q.push(0);
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
                q.push(v);
            }
        }
        return false;
    };

    if (spfa()) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 1; i <= n; i ++) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}