#include <bits/stdc++.h>

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

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edg(m + 1);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(i);
        adj[v].emplace_back(i);
        edg[i] = {u, v};
    }
    
    int idx = 0;
    vector<int> dfn(n + 1), low(n + 1);
    vector<pair<int, int>> ans;
    auto tarjan = [&](auto self, int u, int pid) -> void {
        dfn[u] = ++ idx;
        low[u] = dfn[u]; 
        for (int eid: adj[u]) {
            if (eid == pid) {
                continue;
            }
            int v = edg[eid].first ^ edg[eid].second ^ u;
            if (dfn[v] == 0) {
                self(self, v, eid);
                cmin(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    ans.emplace_back(min(u, v), max(u, v));
                }
            } else {
                cmin(low[u], dfn[v]);
            }
        }
    };
    tarjan(tarjan, 1, 0);
    
    sort(begin(ans), end(ans));

    for (auto &[a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }

    return 0;
}