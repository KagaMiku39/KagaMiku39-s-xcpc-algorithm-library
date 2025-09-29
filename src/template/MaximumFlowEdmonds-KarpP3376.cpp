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
    auto add = [&](int u, int v, i64 cap) {
        adj[u].emplace_back(v, cap, ssize(adj[v]));
        adj[v].emplace_back(u, 0, ssize(adj[u]) - 1);
    };

    for (int i = 0; i < m; i ++) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        add(u, v, w);
    }

    i64 flo = 0;
    vector<pair<int, int>> pre; 
    auto bfs = [&]() {
        pre.assign(n + 1, {-1, -1});
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < ssize(adj[u]); i ++) {
                auto &[v, cap, rev] = adj[u][i];
                if (cap > 0 && pre[v].first == -1) {
                    pre[v] = {u, i};
                    if (v == t) {
                        return true;
                    }
                    q.push(v);
                }
            }
        }
        return false;
    };
    while (bfs()) {
        i64 mf = LLONG_MAX;
        for (int cur = t; cur != s; cur = pre[cur].first) {
            auto &[p, idx] = pre[cur];
            mf = min(mf, get<1>(adj[p][idx]));
        }
        for (int cur = t; cur != s; cur = pre[cur].first) {
            auto &[p, idx] = pre[cur];
            get<1>(adj[p][idx]) -= mf;
            int rev = get<2>(adj[p][idx]);
            get<1>(adj[cur][rev]) += mf;
        }
        flo += mf;
    }

    cout << flo << '\n';

    return 0;
}