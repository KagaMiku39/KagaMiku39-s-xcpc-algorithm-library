#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct SegmentTree {
    #define lc cur * 2
    #define rc cur * 2 + 1

    int n;

    vector<T> vec;

    struct Node {
        T val, g;
    };
    vector<Node> seg;

    SegmentTree(int n, vector<T> &vec) : n(n), vec(vec), seg(4 * (n + 1)) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        seg[cur].val = seg[lc].val + seg[rc].val;
        seg[cur].g = gcd(seg[lc].g, seg[rc].g);
    }

    void build(int cur, int s, int t) {
        if (s == t) {
            seg[cur].val = vec[s];
            seg[cur].g = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }
    
    void modify(int l, int r, T d) {
        modify(1, 1, n, l, d);
        if (r < n) {
            modify(1, 1, n, r + 1, -d);
        }
    }

    void modify(int cur, int s, int t, int pos, T val) {
        if (s == t) {
            seg[cur].val += val;
            seg[cur].g += val;
            return;
        }
        int mid = (s + t) / 2;
        if (pos <= mid) {
            modify(lc, s, mid, pos, val);
        } else {
            modify(rc, mid + 1, t, pos, val);
        }
        pushup(cur);
    }

    T querygcd(int l, int r) {
        i64 val = queryval(1, 1, n, 1, l);
        if (l < r) {
            return abs(gcd(val, querygcd(1, 1, n, l + 1, r)));
        } else {
            return abs(val);
        }
    }
    
    T querygcd(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return seg[cur].g;
        }
        int mid = (s + t) / 2;
        if (ro <= mid) {
            return querygcd(lc, s, mid, lo, ro);
        }
        if (lo > mid) {
            return querygcd(rc, mid + 1, t, lo, ro);
        }
        return gcd(querygcd(lc, s, mid, lo, ro), querygcd(rc, mid + 1, t, lo, ro));
    }

    T queryval(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return seg[cur].val;
        }
        int mid = (s + t) / 2;
        if (ro <= mid) {
            return queryval(lc, s, mid, lo, ro);
        }
        if (lo > mid) {
            return queryval(rc, mid + 1, t, lo, ro);
        }
        return queryval(lc, s, mid, lo, ro) + queryval(rc, mid + 1, t, lo, ro);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<i64> dif(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> dif[i];
    }
    
    for (int i = n; i >= 1; i --) {
        dif[i] -= dif[i - 1];
    }

    SegmentTree<i64> seg(n, dif);

    while (m --) {
        char opt;
        cin >> opt;
        if (opt == 'C') {
            int l, r;
            i64 d;
            cin >> l >> r >> d;
            seg.modify(l, r, d);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.querygcd(l, r) << '\n';
        }
    }

    return 0;
}