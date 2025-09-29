#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<tuple<int, i64, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        i64 w;
        cin >> w;
        adj[u].emplace_back(v, w, ssize(adj[v]));
        adj[v].emplace_back(u, 0, ssize(adj[u]) - 1);
    }

    i64 ans = 0;
    vector<int> iter, lev(n + 1);
    auto bfs = [&]() {
        lev.assign(n + 1, -1);
        queue<int> q;
        lev[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &[v, cap, rev] : adj[u]) {
                if (cap > 0 && lev[v] < 0) {
                    lev[v] = lev[u] + 1;
                    q.push(v);
                }
            }
        }
        return lev[t] != -1;
    };
    auto dfs = [&](auto &self, int u, i64 mf) -> i64 {
        if (u == t) {
            return mf;
        }
        for (int &i = iter[u]; i < ssize(adj[u]); i ++) {
            auto &[v, cap, rev] = adj[u][i];
            if (cap > 0 && lev[u] < lev[v]) {
                i64 dis = self(self, v, min(mf, cap));
                if (dis > 0) {
                    cap -= dis;
                    get<1>(adj[v][rev]) += dis;
                    return dis;
                }
            }
        }
        return 0;
    };
    while (bfs()) {
        iter.assign(n + 1, 0);
        i64 mf = 0;
        while ((mf = dfs(dfs, s, LLONG_MAX)) > 0) {
            ans += mf;
        }
    }

    cout << ans << '\n';

    return 0;
}