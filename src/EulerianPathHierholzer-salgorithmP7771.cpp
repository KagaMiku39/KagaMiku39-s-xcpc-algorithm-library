#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> out(n + 1), in(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        out[u] ++;
        in[v] ++;
    }
    
    int s = 1, cnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (out[i] != in[i]) {
            cnt ++;
            if (out[i] - in[i] == 1) {
                s = i;
            }
        }
    }

    if (cnt == 0) {
        bool tag = false;
        for (int i = 1; i <= n; i ++) {
            if (out[i] > 0) {
                s = i;
                tag = true;
                break;
            }
        }
        if (!tag && m > 0) {
            cout << "No\n";
            return 0;
        }
    } else if (cnt == 2) {
        bool ok = true;
        for (int i = 1; i <= n; i ++) {
            if (out[i] - in[i] != 1 && out[i] - in[i] != -1 && out[i] != in[i]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "No\n";
            return 0;
        }
    } else {
        cout << "No\n";
        return 0;
    }
    
    for (int i = 1; i <= n; i ++) {
        sort(begin(adj[i]), end(adj[i]));
    }
    
    vector<int> id(n + 1), path;
    stack<int> stk;
    stk.push(s);
    while (!stk.empty()) {
        int u = stk.top();
        if (id[u] < ssize(adj[u])) {
            int v = adj[u][id[u]];
            id[u] ++;
            stk.push(v);
        } else {
            stk.pop();
            path.push_back(u);
        }
    }
    
    if (ssize(path) != m + 1) {
        cout << "No\n";
        return 0;
    }
    
    reverse(begin(path), end(path));
    
    for (int i = 0; i < ssize(path); i ++) {
        cout << path[i] << " \n"[i == ssize(path) - 1];
    }
    
    return 0;
}