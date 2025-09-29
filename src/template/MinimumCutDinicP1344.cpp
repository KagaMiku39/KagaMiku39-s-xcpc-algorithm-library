#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    constexpr int k = 1001;

    vector<vector<tuple<int, i64, int>>> adj(n + 1);
    auto add = [&](int u, int v, int cap) {
        adj[u].emplace_back(v, cap, ssize(adj[v]));
        adj[v].emplace_back(u, 0, ssize(adj[u]) - 1);
    };

    vector<int> s(m + 1), e(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> s[i] >> e[i];
        i64 c;
        cin >> c;
        i64 cap = c * k + 1;
        add(s[i], e[i], cap);
    }
    // for (int i = 1; i <= m; i ++) {
    //     cin >> s[i] >> e[i];
    //     i64 c;
    //     cin >> c;
    //     add(s[i], e[i], c);
    // }

    auto dinic = [&]() {
        i64 flo = 0;
        vector<int> iter(n + 1), lev(n + 1);
        auto bfs = [&]() {
            lev.assign(n + 1, -1);
            queue<int> q;
            lev[1] = 0;
            q.push(1);
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
            return lev[n] != -1;
        };
        auto dfs = [&](auto &self, int u, i64 mf) -> i64 {
            if (u == n) {
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
            while ((mf = dfs(dfs, 1, LLONG_MAX)) > 0) {
                flo += mf;
            }
        }
        return flo;
    };

    i64 ans = dinic();
    
    cout << ans / k << ' ' << ans % k << '\n';

    // cout << dinic() << ' ';

    // for (int i = 1; i <= m; i ++) {
    //     add(s[i], e[i], 1);
    // }

    // cout << dinic() << '\n';

    return 0;
}