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

    vector<vector<int>> adj(n + 1); 
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            continue; 
        }
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    int clk = 0;
    vector<int> dfn(n + 1), low(n + 1), stk, instk(n + 1);
    vector<vector<int>> vbcc;
    auto tarjan = [&](auto &self, int u, int pa) -> void {
        dfn[u] = low[u] = ++ clk;
        stk.emplace_back(u);
        instk[u] = true;
        int cnt = 0;
        for (int v : adj[u]) {
            if (v == pa) {
                continue; 
            }
            if (!dfn[v]) {
                cnt ++;
                self(self, v, u);
                cmin(low[u], low[v]);
                if ((pa != 0 && low[v] >= dfn[u]) || (pa == 0 && cnt > 1)) {
                    vector<int> bcc;
                    int k;
                    do {
                        k = stk.back();
                        stk.pop_back();
                        instk[k] = false;
                        bcc.emplace_back(k);
                    } while (k != v);
                    bcc.emplace_back(u);
                    vbcc.emplace_back(bcc);
                }
            } else if (dfn[v] < dfn[u]) {
                cmin(low[u], dfn[v]);
            }
        }
    };
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(tarjan, i, 0);
            if (ssize(stk) > 0) {
                vector<int> bcc;
                while (!stk.empty()) {
                    int k = stk.back();
                    stk.pop_back();
                    instk[k] = false;
                    bcc.emplace_back(k);
                }
                vbcc.emplace_back(bcc);
            }
        }
    }
    
    cout << ssize(vbcc) << '\n';
    for (auto &bcc : vbcc) {
        cout << ssize(bcc);
        for (int &nd : bcc) {
            cout << ' ' << nd;
        }
        cout << '\n';
    }

    return 0;
}