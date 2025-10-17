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

    vector<int> u(m + 1), v(m + 1), w(m + 1); 
    vector<vector<tuple<int, int, int>>> adj(n + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> u[i] >> v[i] >> w[i];
        adj[u[i]].emplace_back(v[i], w[i], i);
        adj[v[i]].emplace_back(u[i], w[i], i);
    }

    int s;
    cin >> s;

    vector<int> vis(n + 1),  id(n + 1);
    vector<i64> dis(n + 1, LLONG_MAX);
    priority_queue<pair<i64, int>> pq;
    dis[s] = 0;
    pq.emplace(0, s);
    while (ssize(pq)) {
        auto [d, u] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        d = -d;
        vis[u] = true;
        for (auto &[v, wei, i]: adj[u]) {
            if (vis[v]) {
                continue;
            }
            if (cmin(dis[v], d + wei)) {
                id[v] = i;
                pq.emplace(-(d + wei), v);
            } else if (dis[v] == d + wei) {
                if (w[id[v]] > wei) {
                    id[v] = i;
                }
            }
        }
    }
    
    i64 sum = 0;
    vector<int> ans;
    for (int i = 1; i <= n; i ++) {
        if (i != s) {
            sum += w[id[i]];
            ans.emplace_back(id[i]);
        }
    }

    cout << sum << '\n';

    for (int &i: ans) {
        cout << i << " \n"[i == ans.back()];
    }

    return 0;
}