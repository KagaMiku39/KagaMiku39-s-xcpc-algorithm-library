#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#define lc 2 * cur
#define rc 2 * cur + 1

template<typename T>
struct SegmentTree {
    int n, mod;
    
    vector<T> vec; 

    struct Node{
        T val, tag;
    };
    vector<Node> st;

    SegmentTree(int n, int mod, vector<T> &vec) : n(n), mod(mod), vec(vec), st(4 * (n + 1)) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        st[cur].val = (1ll * st[lc].val + st[rc].val) % mod; 
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            st[cur].val = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }

    void pushdown(int cur, int s, int t, int mid) {
        if (!st[cur].tag) {
            return; 
        }
        st[lc].val = (st[lc].val + (mid - s + 1ll) * st[cur].tag) % mod;
        st[rc].val = (st[rc].val + i64(t - mid) * st[cur].tag) % mod;
        st[lc].tag = (1ll * st[lc].tag + st[cur].tag) % mod;
        st[rc].tag = (1ll * st[rc].tag + st[cur].tag) % mod;
        st[cur].tag = 0;
    }

    void add(int lo, int ro, T val) {
        add(1, 1, n, lo, ro, val);
    }

    void add(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            st[cur].val = (st[cur].val + (t - s + 1ll) * val) % mod;
            st[cur].tag = (1ll * st[cur].tag + val) % mod;
            return; 
        }
        int mid = (s + t) / 2; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            add(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            add(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    T query(int lo, int ro) {
        return query(1, 1, n, lo, ro);
    }

    T query(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return st[cur].val;
        }
        int mid = (s + t) / 2;
        T sum = 0; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            sum = (1ll * sum + query(lc, s, mid, lo, ro)) % mod;
        }
        if (ro > mid) {
            sum = (1ll * sum + query(rc, mid + 1, t, lo, ro)) % mod;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, r, mod;
    cin >> n >> m >> r >> mod;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }
    
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i ++) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    
    vector<int> p(n + 1), sz(n + 1, 1), dep(n + 1), ch(n + 1);
    sz[0] = 0, dep[r] = 1;
    auto dfs1 = [&](auto &self, int u, int pa) -> void {
        p[u] = pa;
        for (int &v: adj[u]) {
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
    dfs1(dfs1, r, 0);

    int idx = 0;
    vector<int> tp(n + 1), id(n + 1), arr(n + 1);
    auto dfs2 = [&](auto &self, int u, int top) -> void {
        tp[u] = top;
        id[u] = ++ idx;
        arr[idx] = vec[u] % mod;
        if (!ch[u]) {
            return;
        }
        self(self, ch[u], top);
        for (int &v: adj[u]) {
            if (v == p[u] || v == ch[u]) {
                continue;
            }
            self(self, v, v);
        }
    };
    dfs2(dfs2, r, r);

    SegmentTree st(n, mod, arr);

    auto add = [&](int a, int b, int val) {
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            st.add(id[tp[a]], id[a], val);
            a = p[tp[a]];
        }
        if (dep[a] < dep[b]) {
            swap(a, b);
        }
        st.add(id[b], id[a], val);
    };

    auto query = [&](int a, int b) {
        int sum = 0;
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            sum = (1ll * sum + st.query(id[tp[a]], id[a])) % mod;
            a = p[tp[a]];
        }
        if (dep[a] < dep[b]) {
            swap(a, b);
        }
        sum = (1ll * sum + st.query(id[b], id[a])) % mod;
        return sum;
    };

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, z;
            add(x, y, z);
        }
        if (opt == 2) {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << '\n';
        }
        if (opt == 3) {
            int x, z;
            cin >> x >> z;
            st.add(id[x], id[x] + sz[x] - 1, z);
        }
        if (opt == 4) {
            int x;
            cin >> x;
            cout << st.query(id[x], id[x] + sz[x] - 1) << '\n';
        }
    }
    
    return 0;
}