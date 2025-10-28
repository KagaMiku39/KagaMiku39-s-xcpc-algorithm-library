#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct SegmentTree {
    // #define lc 2 * cur
    #define lc seg[cur].ch[0]
    // #define rc 2 * cur + 1
    #define rc seg[cur].ch[1]
    
    int n;

    int idx = 1, rt = 1;
    
    vector<T> vec; 

    struct Node {
        T val, tag;

        array<int, 2> ch;
    };
    vector<Node> seg;

    // SegmentTree(int n, const vector<T> &vec) : n(n), vec(vec), seg(4 * n) {
    //     build(1, 1, n);
    // }

    SegmentTree(int n, const vector<T> &vec) : n(n), vec(vec), seg(2 * n) {
        for (int i = 1; i <= n; i ++) {
            add(i, i, vec[i]);
        }
    }

    void pushup(int cur) {
        seg[cur].val = seg[lc].val + seg[rc].val; 
    }

    // void build(int cur, int s, int t) {  
    //     if (s == t) {
    //         seg[cur].val = vec[s];
    //         return;
    //     }
    //     int mid = (s + t) / 2;
    //     build(lc, s, mid);
    //     build(rc, mid + 1, t);
    //     pushup(cur);
    // }

    void pushdown(int cur, int s, int t, int mid) {
        if (!seg[cur].tag) {
            return; 
        }
        seg[lc].val += (mid - s + 1) * seg[cur].tag;
        seg[rc].val += (t - mid) * seg[cur].tag;
        seg[lc].tag += seg[cur].tag;
        seg[rc].tag += seg[cur].tag;
        seg[cur].tag = 0;
    }
    
    void add(int lo, int ro, T val) {
        // add(1, 1, n, lo, ro, val);
        add(rt, 1, n, lo, ro, val);
    }

    // void add(int cur, int s, int t, int lo, int ro, T val) {
    void add(int &cur, int s, int t, int lo, int ro, T val) {
        if (!cur) {
            cur = ++ idx;
        }
        if (lo <= s && t <= ro) {
            seg[cur].val += (t - s + 1) * val;
            seg[cur].tag += val;
            return; 
        }
        // int mid = (s + t) / 2; 
        int mid = s + (t - s) / 2;
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
        if (!cur) {
            return 0;
        }
        if (lo <= s && t <= ro) {
            return seg[cur].val;
        }
        // int mid = (s + t) / 2;
        int mid = s + (t - s) / 2;
        T sum = 0; 
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            sum += query(lc, s, mid, lo, ro);
        }
        if (ro > mid) {
            sum += query(rc, mid + 1, t, lo, ro);
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<i64> a(n + 1);
    
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }
    
    SegmentTree<i64> seg(n, a);
    
    while (m --) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            i64 k;
            cin >> k;
            seg.add(x, y, k);
        }
        if (opt == 2) {
            cout << seg.query(x, y) << '\n';
        }
    }

    return 0;
}