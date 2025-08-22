#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmin(T &a, T &b) {
	return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(2 * n + 1);
    for (int k = 0; k < m; k ++) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        adj[i + (!a) * n].emplace_back(j + b * n);
        adj[j + (!b) * n].emplace_back(i + a * n);
    }

    int idx = 0, top = 0, cnt = 0;
    vector<int> dfn(2 * n + 1), low(2 * n + 1), stk, scc(2 * n + 1);
    auto tarjan = [&](auto self, int u) -> void {
        dfn[u] = low[u] = ++ idx;
        stk.emplace_back(u);
        for (int &v : adj[u]) {
            if (!dfn[v]) {
                self(self, v);
                cmin(low[u], low[v]);
            } else if (!scc[v]) {
                cmin(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            ++ cnt;
            int cur = 0;
            do {
                cur = stk.back();
                stk.pop_back();
                scc[cur] = cnt;
            } while (cur != u);
        }
    };
    for (int i = 1; i <= 2 * n; i ++) {
        if (!dfn[i]) {
            tarjan(tarjan, i);
        }
    }
    
    bool ok = true;
    for (int i = 1; i <= n; i ++) {
        if (scc[i] == scc[i + n]) {
            ok = false;
            break;
        }
    }

    if (ok) {
        cout << "POSSIBLE" << '\n';
        for (int i = 1; i <= n; i ++) {
            cout << (scc[i] > scc[i + n]) << " \n"[i == n];
        }
    } else {
        cout << "IMPOSSIBLE" << '\n';
    }

    return 0;
}