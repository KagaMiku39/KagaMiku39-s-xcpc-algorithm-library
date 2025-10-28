#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct SegmentTree {
    #define lc 2 * cur
    // #define lc seg[cur].ch[0]
    #define rc 2 * cur + 1
    // #define rc seg[cur].ch[1]

    int n;

    // int idx = 1, rt = 1;
    
    vector<T> vec; 
    
    struct Node {
        T val;
        
        array<T, 2> tag{0, 1};

        // array<int, 2> ch;
    };
    vector<Node> seg;
    
    int mod;
    
    SegmentTree(int n, const vector<T> &vec, int mod) : n(n), vec(vec), seg(4 * n), mod(mod) {
        build(1, 1, n);
    }

    // SegmentTree(int n, const vector<T> &vec, int mod) : n(n), seg(2 * n), mod(mod) {
    //     for (int i = 1; i <= n; i ++) {
    //         add(i, i, vec[i]);
    //     }
    // }

    void pushup(int cur) {
        seg[cur].val = (1ll * seg[lc].val + seg[rc].val) % mod;
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            seg[cur].val = vec[s] % mod;
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }

    void pushdown(int cur, int s, int t, int mid) {
        if (!seg[cur].tag[0] && seg[cur].tag[1] == 1) {
            return; 
        }
        seg[lc].val = (1ll * seg[lc].val * seg[cur].tag[1] + (mid - s + 1ll) * seg[cur].tag[0]) % mod;
        seg[rc].val = (1ll * seg[rc].val * seg[cur].tag[1] + i64(t - mid) * seg[cur].tag[0]) % mod;
        seg[lc].tag[0] = (1ll * seg[lc].tag[0] * seg[cur].tag[1] + seg[cur].tag[0]) % mod;
        seg[lc].tag[1] = 1ll * seg[lc].tag[1] * seg[cur].tag[1] % mod;
        seg[rc].tag[0] = (1ll * seg[rc].tag[0] * seg[cur].tag[1] + seg[cur].tag[0]) % mod;
        seg[rc].tag[1] = 1ll * seg[rc].tag[1] * seg[cur].tag[1] % mod;
        seg[cur].tag = {0, 1};
    }

    void add(int lo, int ro, T val) {
        add(1, 1, n, lo, ro, val);
        // add(rt, 1, n, lo, ro, val);
    }
    
    void add(int cur, int s, int t, int lo, int ro, T val) {
    // void add(int &cur, int s, int t, int lo, int ro, T val) {
    //     if (!cur) {
    //         cur = ++ idx;
    //     }
        if (lo <= s && t <= ro) {
            seg[cur].val = (seg[cur].val + (t - s + 1ll) * val) % mod;
            seg[cur].tag[0] = (seg[cur].tag[0] + val) % mod;
            return; 
        }
        int mid = (s + t) / 2; 
        // int mid = s + (t - s) / 2;
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            add(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            add(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    void mul(int lo, int ro, T val) {
        mul(1, 1, n, lo, ro, val);
        // mul(rt, 1, n, lo, ro, val);
    }
    
    void mul(int cur, int s, int t, int lo, int ro, T val) {
    // void mul(int &cur, int s, int t, int lo, int ro, T val) {
    //     if (!cur) {
    //         cur = ++ idx;
    //     }
        if (lo <= s && t <= ro) {
            seg[cur].val = 1ll * seg[cur].val * val % mod;
            seg[cur].tag[0] = 1ll * seg[cur].tag[0] * val % mod;
            seg[cur].tag[1] = 1ll * seg[cur].tag[1] * val % mod;
            return; 
        }
        int mid = (s + t) / 2; 
        // int mid = s + (t - s) / 2;
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            mul(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            mul(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
    }

    T query(int lo, int ro) {
        return query(1, 1, n, lo, ro);
    }
    
    T query(int cur, int s, int t, int lo, int ro) {
        // if (!cur) {
        //     return 0;
        // }
        if (lo <= s && t <= ro) {
            return seg[cur].val;
        }
        int mid = (s + t) / 2;
        // int mid = s + (t - s) / 2;
        T sum = 0; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            sum = (sum + query(lc, s, mid, lo, ro)) % mod;
        }
        if (ro > mid) {
            sum = (sum + query(rc, mid + 1, t, lo, ro)) % mod;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, m;
    cin >> n >> q >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    SegmentTree<int> seg(n, vec, m);

    while (q --) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            int k;
            cin >> k;
            seg.mul(x, y, k);
        }
        if (opt == 2) {
            int k;
            cin >> k;
            seg.add(x, y, k);
        }
        if (opt == 3) {
            cout << seg.query(x, y) << '\n';
        }
    }

    return 0;
}