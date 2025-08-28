#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct SegmentTreeMerge {
    #define lc(x) segm[x].ch[0]
    #define rc(x) segm[x].ch[1]

    struct Node {
        array<int, 2> ch;

        int cnt, val;

        Node() : ch{}, cnt{}, val{} {}
    };
    vector<Node> segm;
    
    vector<int> root;

    int idx;

    SegmentTreeMerge(int n) : idx{}, segm(100 * n), root(n + 1) {}

    void pushup(int cur) {
        if (segm[lc(cur)].cnt >= segm[rc(cur)].cnt) {
            segm[cur].cnt = segm[lc(cur)].cnt;
            segm[cur].val = segm[lc(cur)].val;
        } else {
            segm[cur].cnt = segm[rc(cur)].cnt;
            segm[cur].val = segm[rc(cur)].val;
        }
    }

    void modify(int &cur, int s, int t, int pos, int val) {
        if (!cur) {
            cur = ++ idx;
        }
        if (s == t) {
            segm[cur].cnt += val;
            segm[cur].val = pos;
            return;
        }
        int mid = s + (t - s) / 2;
        if (pos <= mid) {
            modify(lc(cur), s, mid, pos, val);
        } else {
            modify(rc(cur), mid + 1, t, pos, val);
        }
        pushup(cur);
    }

    int merge(int lt, int rt, int s, int t) {
        if (!lt || !rt) {
            return lt + rt;
        }
        if (s == t) {
            segm[lt].cnt += segm[rt].cnt;
            return lt;
        }
        int mid = s + (t - s) / 2;
        lc(lt) = merge(lc(lt), lc(rt), s, mid);
        rc(lt) = merge(rc(lt), rc(rt), mid + 1, t);
        pushup(lt);
        return lt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> p(n + 1), sz(n + 1, 1), dep(n + 1), ch(n + 1);
    sz[0] = 0;
    dep[1] = 1;
    auto dfs1 = [&](auto &self, int u, int pa) -> void {
        p[u] = pa;
        for (int &v : adj[u]) {
            if (v == pa) {
                continue;
            }
            dep[v] = dep[u] + 1;
            self(self, v, u);
            sz[u] += sz[v];
            if (sz[ch[u]] < sz[v]) {
                ch[u] = v;
            }
        }
    };
    dfs1(dfs1, 1, 0);

    vector<int> tp(n + 1);
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
    dfs2(dfs2, 1, 1);

    auto lca = [&](int u, int v) {
        while (tp[u] != tp[v]) {
            if (dep[tp[u]] < dep[tp[v]]) {
                swap(u, v);
            }
            u = p[tp[u]];
        }
        return dep[u] < dep[v] ? u : v;
    };

    SegmentTreeMerge segm(n);

    while (m --) {
        int u, v, z;
        cin >> u >> v >> z;
        int t = lca(u, v);
        segm.modify(segm.root[u], 1, 1e5, z, 1);
        segm.modify(segm.root[v], 1, 1e5, z, 1);
        segm.modify(segm.root[t], 1, 1e5, z, -1);
        if (p[t]) {
            segm.modify(segm.root[p[t]], 1, 1e5, z, -1);
        }
    }

    vector<int> ans(n + 1);
    auto dfs = [&](auto &self, int u, int pa) -> void {
        for (int &v : adj[u]) {
            if (v == pa) {
                continue;
            }
            self(self, v, u);
            segm.root[u] = segm.merge(segm.root[u], segm.root[v], 1, 1e5);
        }
        if (segm.segm[segm.root[u]].cnt > 0) {
            ans[u] = segm.segm[segm.root[u]].val;
        } else {
            ans[u] = 0;
        }
    };
    dfs(dfs, 1, 0);

    for (int i = 1; i <= n; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}