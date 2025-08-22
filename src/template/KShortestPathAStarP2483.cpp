#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

constexpr double eps = 1e-9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    double e;
    cin >> n >> m >> e;

    vector<vector<pair<int, double>>> adj(n + 1), radj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        if (u == n) {
            continue;
        }
        adj[u].emplace_back(v, w);
        radj[v].emplace_back(u, w);
    }

    vector<double> f(n + 1, DBL_MAX);
    vector<int> vis(n + 1);
    auto dijkstra = [&]() {
        priority_queue<pair<double, int>> pq;
        f[n] = 0;
        pq.emplace(0, n);
        while (ssize(pq)) {
            auto [dis, u] = pq.top();
            pq.pop();
            dis *= -1;
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (auto &[v, w] : radj[u]) {
                if (!cmin(f[v], dis + w) || vis[v]) {
                    continue;
                }
                pq.emplace(-f[v], v);
            }
        }
    };
    dijkstra();

    int ans = 0;
    auto astar = [&]() {
        priority_queue<tuple<double, double, int>> pq;
        pq.emplace(-f[1], 0, 1);
        while (ssize(pq)) {
            auto [val, cst, u] = pq.top();
            pq.pop();
            val *= -1;
            cst *= -1;
            if (u == n) {
                if (e - cst < eps) {
                    return;
                } else {
                    e -= cst;
                    ans ++;
                }
            }
            for (auto &[v, w] : adj[u]) {
                pq.emplace(-(cst + w + f[v]), -(cst + w), v);
            }
        }
    };
    astar();
    
    cout << ans << '\n';
    
    return 0;
}