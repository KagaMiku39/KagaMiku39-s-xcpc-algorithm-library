#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<tuple<int, i64, i64, int>>> adj(n + 1);
    auto add = [&](int u, int v, i64 cap, i64 cst) {
        adj[u].emplace_back(v, cap, cst, ssize(adj[v]));
        adj[v].emplace_back(u, 0, -cst, ssize(adj[u]) - 1);
    };

    for (int i = 1; i <= m; i ++) {
        int u, v;
        i64 w, c;
        cin >> u >> v >> w >> c;
        add(u, v, w, c);
    }

    i64 flo = 0, cst = 0;
    vector<i64> dis, mf;
    vector<pair<int, int>> pre;
    auto spfa = [&]() {
        vector<int> vis(n + 1, false);
        queue<int> q;
        dis.assign(n + 1, LLONG_MAX);
        mf.assign(n + 1, 0);
        pre.assign(n + 1, {-1, -1});
        dis[s] = 0;
        mf[s] = LLONG_MAX;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = 0; i < ssize(adj[u]); i ++) {
                auto &[v, cap, c, rev] = adj[u][i];
                if (cap > 0 && dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    mf[v] = min(mf[u], cap);
                    pre[v] = {u, i};
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return mf[t] > 0;
    };
    while (spfa()) {
        i64 f = mf[t];
        flo += f;
        cst += f * dis[t];
        int u = t;
        while (u != s) {
            auto &[p, id] = pre[u];
            get<1>(adj[p][id]) -= f;
            int rev = get<3>(adj[p][id]);
            get<1>(adj[u][rev]) += f;
            u = p;
        }
    }

    cout << flo << ' ' << cst << '\n';

    return 0;
}