#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const i64 k = 1001;

    vector<vector<tuple<int, i64, int>>> adj(n + 1);
    auto add = [&](int u, int v, i64 cap) {
        adj[u].emplace_back(v, cap, ssize(adj[v]));
        adj[v].emplace_back(u, 0, ssize(adj[u]) - 1);
    };

    vector<int> s(m + 1), e(m + 1);
    // for (int i = 1; i <= m; i ++) {
    //     cin >> s[i] >> e[i];
    //     i64 c;
    //     cin >> c;
    //     i64 cap = c * k + 1;
    //     add(s[i], e[i], cap);
    // }
    for (int i = 1; i <= m; i ++) {
        cin >> s[i] >> e[i];
        i64 c;
        cin >> c;
        add(s[i], e[i], c);
    }

    auto EK = [&]() {
        i64 flo = 0;
        vector<pair<int, int>> pre; 
        auto bfs = [&]() {
            pre.assign(n + 1, {-1, -1});
            queue<int> q;
            q.push(1);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i = 0; i < ssize(adj[u]); i++) {
                    auto &[v, cap, rev] = adj[u][i];
                    if (cap > 0 && pre[v].first == -1) {
                        pre[v] = {u, i};
                        if (v == n) {
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
            for (int u = n; u != 1; u = pre[u].first) {
                auto &[p, idx] = pre[u];
                mf = min(mf, get<1>(adj[p][idx]));
            }
            for (int u = n; u != 1; u = pre[u].first) {
                auto &[p, idx] = pre[u];
                get<1>(adj[p][idx]) -= mf;
                int rev = get<2>(adj[p][idx]);
                get<1>(adj[u][rev]) += mf;
            }
            flo += mf;
        }    
        return flo;
    };

    // i64 ans = EK();

    // cout << ans / k << ' ' << ans % k << '\n';

    cout << EK() << ' ';
    
    for (int i = 1; i <= m; i ++) {
        add(s[i], e[i], 1);
    }

    cout << EK() << '\n';

    return 0;
}