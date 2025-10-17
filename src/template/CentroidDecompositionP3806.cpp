#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

constexpr int maxsz = 10000005;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 1; i <= n - 1; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> que(m + 1); 
    for (int i = 1; i <= m; i ++) {
        cin >> que[i];
        if (que[i] >= maxsz) {
            que[i] = maxsz - 1;
        }
    }

    int mxs = n + 1, sum = n, cen = 0;
    vector<int> siz(n + 1), del(n + 1);  
    auto getcen = [&](auto &self, int u, int p) -> void {
        siz[u] = 1;
        int s = 0;
        for (auto &[v, w] : adj[u]) {
            if (v == p || del[v]) {
                continue;
            }
            self(self, v, u);
            siz[u] += siz[v];
            cmax(s, siz[v]);
        }
        cmax(s, sum - siz[u]);
        if (s < mxs) {
            mxs = s;
            cen = u;
        }
    };
    getcen(getcen, 1, 0);
    
    vector<int> d(n + 1), dis;
    auto getdis = [&](auto &self, int u, int p) -> void {
        dis.emplace_back(d[u]);
        for (auto &[v, w] : adj[u]) {
            if (v == p || del[v]) {
                continue;
            }
            d[v] = d[u] + w;
            self(self, v, u);
        }
    };

    vector<int> ans(m + 1), q, judge(maxsz);
    auto calc = [&](int u) {
        judge[0] = 1;
        
        for (auto &[v, w] : adj[u]) {
            if (del[v]) {
                continue;
            }
            dis.clear();
            d[v] = w;
            getdis(getdis, v, u); 
            for (int j = 0; j < ssize(dis); j++) {
                if (dis[j] >= maxsz) {
                    continue;
                }
                for (int k = 1; k <= m; k++) {
                    if (ans[k]) {
                        continue;
                    }
                    if (que[k] >= dis[j] && que[k] < maxsz) { 
                        if (judge[que[k] - dis[j]]) {
                            ans[k] = 1;
                        }
                    }
                }
            }
            for (int j = 0; j < ssize(dis); j++) {
                if (dis[j] < maxsz) {
                    q.emplace_back(dis[j]);
                    judge[dis[j]] = 1;
                }
            }
        }
        for (int i = 0; i < ssize(q); i ++) {
            judge[q[i]] = 0;
        }
        q.clear();
    };

    auto divide = [&](auto &self, int u) -> void {
        calc(u);
        del[u] = 1;
        for (auto &[v, w] : adj[u]) {
            if (del[v]) {
                continue;
            }
            sum = siz[v];
            mxs = n + 1;
            getcen(getcen, v, 0);
            self(self, cen);
        }
    };
    
    divide(divide, cen);
    for (int i = 1; i <= m; i ++) {
        cout << (ans[i] ? "AYE\n" : "NAY\n");
    }

    return 0;
}