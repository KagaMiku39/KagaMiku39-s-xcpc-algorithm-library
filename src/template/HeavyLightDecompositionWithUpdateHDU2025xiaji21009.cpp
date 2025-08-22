#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

#define lc 2 * cur
#define rc 2 * cur + 1

template<typename T>
struct SegmentTree {
    int n;
    
    vector<T> vec; 

    struct Node{
        T val, tag;
    };
    vector<Node> st;

    SegmentTree(int n, vector<T> &vec) : n(n), vec(vec), st(4 * (n + 1)) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        st[cur].val = max(st[lc].val, st[rc].val); 
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

    void pushdown(int cur) {
        if (!st[cur].tag) {
            return; 
        }
        st[lc].val += st[cur].tag;
        st[rc].val += st[cur].tag;
        st[lc].tag += st[cur].tag;
        st[rc].tag += st[cur].tag;
        st[cur].tag = 0;
    }
    
    void add(int lo, int ro, T val) {
        add(1, 1, n, lo, ro, val);
    }

    void add(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            st[cur].val += val;
            st[cur].tag += val;
            return; 
        }
        int mid = (s + t) / 2; 
        pushdown(cur);
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
        T mx = 0; 
        pushdown(cur);
        if (lo <= mid) {
            cmax(mx, query(lc, s, mid, lo, ro));
        }
        if (ro > mid) {
            cmax(mx, query(rc, mid + 1, t, lo, ro));
        }
        return mx;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

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
    sz[0] = 0, dep[1] = 1;
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
    dfs1(dfs1, 1, 0);

    int idx = 0;
    vector<int> tp(n + 1), id(n + 1), arr(n + 1);
    auto dfs2 = [&](auto &self, int u, int top) -> void {
        tp[u] = top;
        id[u] = ++ idx;
        arr[idx] = vec[u];
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
    dfs2(dfs2, 1, 1);

    SegmentTree st(n, arr);
    
    vector<int> tag(n + 1);

    auto query = [&](int a, int b) {
        int mx = 0;
        while (tp[a] != tp[b]) {
            if (dep[tp[a]] < dep[tp[b]]) {
                swap(a, b);
            }
            cmax(mx, st.query(id[tp[a]], id[a]));
            cmax(mx, vec[tp[a]] + tag[p[tp[a]]]);
            a = p[tp[a]];
        }
        if (dep[a] < dep[b]) {
            swap(a, b);
        }
        cmax(mx, st.query(id[b], id[a]));
        if (b == tp[b]) {
            cmax(mx, vec[b] + tag[p[b]]);
        }
        return mx;
    };

    auto add = [&](int pos, int val) {
        if (p[pos]) {
            st.add(id[p[pos]], id[p[pos]], val);
            vec[p[pos]] += val;
        }
        if (ch[pos]) {
            st.add(id[ch[pos]], id[ch[pos]], val);
        }
        tag[pos] += val;
    };
    
    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << '\n';
        }
        if (opt == 2) {
            int x, z;
            cin >> x >> z;
            add(x, z);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }
    
    return 0;
}