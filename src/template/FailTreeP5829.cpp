#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct FailTree {
    int n;
    
    vector<vector<int>> adj;

    vector<int> p, sz, dep, ch, tp;

    FailTree(const string &s) : n(ssize(s) + 1), adj(n), p(n), sz(n), dep(n), ch(n, 0), tp(n) {
        string str = " " + s;
        vector<int> fail(n);
        for (int i = 2, j = 0; i < n; i ++) {
            while (j > 0 && str[i] != str[j + 1]) {
                j = fail[j];
            }
            if (str[i] == str[j + 1]) {
                j ++;
            }
            fail[i] = j;
        }

        for (int i = 1; i < n; i ++) {
            adj[fail[i]].emplace_back(i);
        }
        auto dfs1 = [&](auto &self, int u, int pa) -> void {
            p[u] = pa;
            sz[u] = 1;
            dep[u] = (u == pa) ? 1 : dep[pa] + 1;
            for (int &v : adj[u]) {
                self(self, v, u);
                sz[u] += sz[v];
                if (!ch[u] || sz[ch[u]] < sz[v]) {
                    ch[u] = v;
                }
            }
        };
        dfs1(dfs1, 0, 0);
        auto dfs2 = [&](auto &self, int u, int top) -> void {
            tp[u] = top;
            if (!ch[u]) {
                return;
            }
            self(self, ch[u], top);
            for (int &v : adj[u]) {
                if (v == p[u] || v == ch[u]) {
                    continue;
                }
                self(self, v, v);
            }
        };
        dfs2(dfs2, 0, 0);
    }

    int query(int a, int b) {
        int aa = a, bb = b;
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            a = p[tp[a]];
        }
        int l = dep[a] < dep[b] ? a : b;
        if (l == aa || l == bb)  {
            return p[l];
        }
        return l;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    FailTree ft(s);

    int m;
    cin >> m;

    while (m --) {
        int p, q;
        cin >> p >> q;
        cout << ft.query(p, q) << '\n';
    }

    return 0;
}