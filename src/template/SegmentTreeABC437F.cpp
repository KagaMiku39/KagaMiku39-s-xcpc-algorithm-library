#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

template<typename T>
struct SegmentTree {
    #define lc 2 * cur
    #define rc 2 * cur + 1
    
    int n;

    T e;

    vector<T> vec; 

    vector<T> seg;
    
    function<T(T, T)> op;
    
    SegmentTree(int n, const T &e, const vector<T> &vec, function<T(T, T)> op) : n(n), e(e), vec(vec), seg(4 * n), op(op) {
        build(1, 1, n);
    }

    void pushup(int cur) {
        seg[cur] = op(seg[lc], seg[rc]); 
    }

    void build(int cur, int s, int t) {  
        if (s == t) {
            seg[cur] = vec[s];
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
        pushup(cur);
    }

    void modify(int pos, T val) {
        modify(1, 1, n, pos, val);
    }
    
    void modify(int cur, int s, int t, int pos, T val) {
        if (s == t) {
            seg[cur] = T(t - s + 1) * val;
            return; 
        }
        int mid = s + (t - s) / 2;
        if (pos <= mid) {
            modify(lc, s, mid, pos, val);
        } else {
            modify(rc, mid + 1, t, pos, val);
        }
        pushup(cur);
    }

    T query(int lo, int ro) {
        return query(1, 1, n, lo, ro);
    }

    T query(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return seg[cur];
        }
        int mid = s + (t - s) / 2;
        T res{e}; 
        if (lo <= mid) {
            res = op(res, query(lc, s, mid, lo, ro));
        }
        if (ro > mid) {
            res = op(res, query(rc, mid + 1, t, lo, ro));
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<i64> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i];
        tie(x[i], y[i]) = make_tuple(x[i] + y[i], x[i] - y[i]);
    }
    
    auto mx = [&](const i64 &a, const i64 &b) {
        return max(a, b);
    };

    auto mi = [&](const i64 &a, const i64 &b) {
        return min(a, b);
    };

    SegmentTree<i64> mxx(n, LLONG_MIN, x, mx), mix(n, LLONG_MAX, x, mi), mxy(n, LLONG_MIN, y, mx), miy(n, LLONG_MAX, y, mi);

    while (q --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int i;
            cin >> i >> x[i] >> y[i];
            tie(x[i], y[i]) = make_tuple(x[i] + y[i], x[i] - y[i]);
            mxx.modify(i, x[i]);
            mix.modify(i, x[i]);
            mxy.modify(i, y[i]);
            miy.modify(i, y[i]);
        }
        if (opt == 2) {
            int l, r;
            cin >> l >> r;
            i64 xx, yy;
            cin >> xx >> yy;
            tie(xx, yy) = make_tuple(xx + yy, xx - yy);
            i64 ans = 0;
            cmax(ans, mxx.query(l, r) - xx);
            cmax(ans, xx - mix.query(l, r));
            cmax(ans, mxy.query(l, r) - yy);
            cmax(ans, yy - miy.query(l, r));
            cout << ans << '\n';
        }
    }

    return 0;
}