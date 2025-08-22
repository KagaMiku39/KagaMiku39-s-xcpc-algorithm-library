#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SegmentTree {
    #define lc cur * 2
    #define rc cur * 2 + 1

    int n;
    
    vector<T> vec, seg;

    SegmentTree(int n, vector<T> &vec) : n(n), vec(vec), seg(4 * (n + 1)) {
        build(1, 1, n);
    }
    
    void pushup(int cur) {
        seg[cur] = T(seg[lc], seg[rc]);
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
    
    void modify(int pos, int val) {
        modify(1, 1, n, pos, val);
    }

    void modify(int cur, int s, int t, int pos, int val) {
        if (s == t) {
            seg[cur] = T(val);
            return;
        }
        int mid = (s + t) / 2;
        if (pos > mid) {
            modify(rc, mid + 1, t, pos, val);
        } else {
            modify(lc, s, mid, pos, val);
        }
        pushup(cur);
    }
    
    int query(int lo, int ro) {
        return query(1, 1, n, lo, ro).ms;
    }
    
    T query(int cur, int s, int t, int lo, int ro) {
        if (lo <= s && t <= ro) {
            return seg[cur];
        }
        int mid = (s + t) / 2;
        if (lo > mid) {
            return query(rc, mid + 1, t, lo, ro);
        }
        if (ro <= mid) {
            return query(lc, s, mid, lo, ro);
        }
        return T(query(lc, s, mid, lo, ro), query(rc, mid + 1, t, lo, ro));
    }
};

struct Node {
    int val, ms, lms, rms;

    Node() : val(), ms(), lms(), rms() {}
    
    Node(int v) : val(v), ms(v), lms(v), rms(v) {}
    
    Node(const Node &lt, const Node &rt) {
        val = lt.val + rt.val;
        ms = max({lt.ms, rt.ms, lt.rms + rt.lms});
        lms = max(lt.lms, lt.val + rt.lms);
        rms = max(rt.rms, rt.val + lt.rms);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<Node> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        a[i] = Node(x);
    }
    
    SegmentTree<Node> seg(n, a);

    while (q --) {
        int k;
        cin >> k;
        if (k == 1) {
            int l, r;
            cin >> l >> r;
            if (l > r) {
                swap(l, r);
            }
            cout << seg.query(l, r) << '\n';
        } else {
            int p, s;
            cin >> p >> s;
            seg.modify(p, s);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}