#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

constexpr int logn = 20;

struct VirtualTree {
    int n, cnt{};

    vector<vector<pair<int, int>>> adj;
    
    vector<vector<int>> p;
    
    vector<int> dep, dfn;
    
    vector<i64> mi;
    
    vector<vector<int>> vadj;

    vector<char> iskey;

    VirtualTree(int n) : n(n), adj(n + 1), p(n + 1, vector<int>(logn + 1)), dep(n + 1), dfn(n + 1), mi(n + 1), vadj(n + 1), iskey(n + 1) {}

    void addedge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void work() {
        mi[1] = numeric_limits<i64>::max();
        dfs(1, 0);
    }

    i64 solve() {
        int k;
        cin >> k;
        if (!k) {
            return 0;
        }
        vector<int> a(k + 1);
        for (int i = 1; i <= k; i ++) {
            cin >> a[i];
            iskey[a[i]] = 1;
        }
        sort(next(begin(a)), end(a), [&](int u, int v) {
            return dfn[u] < dfn[v];
        });
        a.erase(unique(next(begin(a)), end(a)), end(a));
        vector<int> vec;
        build(a, vec);
        i64 res = getdp(1);
        for (int &u : vec) {
            vadj[u].clear();
        }
        for (int i = 1; i < ssize(a); i ++) {
            iskey[a[i]] = 0;
        }
        return res;
    }

    void dfs(int u, int pa) {
        dfn[u] = ++ cnt;
        p[u][0] = pa;
        dep[u] = dep[pa] + 1;
        for (int i = 1; i <= logn; i ++) {
            p[u][i] = p[p[u][i - 1]][i - 1];
        }
        for (auto &[v, w] : adj[u]) {
            if (v == pa) {
                continue;
            }
            mi[v] = min(mi[u], 1ll * w);
            dfs(v, u);
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        for (int i = logn; ~i; i --) {
            if (dep[u] - (1 << i) >= dep[v]) {
                u = p[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = logn; ~i; i --) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }

    void build(vector<int> &a, vector<int> &vec) {
        vector<int> s;
        s.emplace_back(1);
        vec.emplace_back(1);
        for (int i = 1; i < ssize(a); i ++) {
            int u = a[i];
            if (u == 1) {
                continue;
            }
            int t = lca(u, s.back());
            vec.emplace_back(u);
            vec.emplace_back(t);
            while (ssize(s) > 1 && dep[s[ssize(s) - 2]] >= dep[t]) {
                vadj[s[ssize(s) - 2]].emplace_back(s.back());
                s.pop_back();
            }
            if (t != s.back()) {
                vadj[t].emplace_back(s.back());
                s.back() = t;
            }
            s.emplace_back(u);
        }
        while (ssize(s) > 1) {
            vadj[s[ssize(s) - 2]].emplace_back(s.back());
            s.pop_back();
        }
    }

    i64 getdp(int u) {
        if (vadj[u].empty()) {
            return mi[u];
        }
        i64 sum = 0;
        for (int v : vadj[u]) {
            sum += getdp(v);
        }
        if (iskey[u]) {
            return mi[u];
        } else {
            return min(sum, mi[u]);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    VirtualTree vt(n);

    for (int i = 1; i < n; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        vt.addedge(u, v, w);
    }

    vt.work();

    int m;
    cin >> m;

    while (m --) {
        cout << vt.solve() << '\n';
    }

    return 0;
}