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
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].emplace_back(y, z);
        adj[y].emplace_back(x, z);
    }

    int ans = 0;
    vector<int> vis(n + 1), wei(n + 1, INT_MAX);
    priority_queue<pair<int, int>> pq;
    wei[1] = 0;
    pq.emplace(0, 1);
    while (ssize(pq)) {
        auto [w, u] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        ans += -w;
        vis[u] = true;
        for (auto &[v, w]: adj[u]) {
            if (vis[v] || !cmin(wei[v], w)) {
                continue;
            }
            pq.emplace(-w, v);
        }
    }

    if (accumulate(begin(vis), end(vis), 0) != n) {
        cout << "orz\n";
        return 0;
    }
    
    cout << ans << '\n';
    
    return 0;
}