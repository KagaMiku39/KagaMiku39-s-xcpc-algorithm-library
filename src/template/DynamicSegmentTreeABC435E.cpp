#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SegmentTree {
    #define lc seg[cur].ch[0]
    #define rc seg[cur].ch[1]
    
    int n;

    int idx{}, rt{};

    struct Node {
        T val, tag;

        array<int, 2> ch;
    };
    vector<Node> seg;

    SegmentTree(int n) : n(n) {
        seg.emplace_back();
    }

    void pushup(int cur) {
        seg[cur].val = seg[lc].val + seg[rc].val; 
    }

    void pushdown(int cur, int s, int t, int mid) {
        if (!seg[cur].tag) {
            return; 
        }
        if (!lc) {
            seg.emplace_back();
            lc = ++ idx;
        }
        if (!rc) {
            seg.emplace_back();
            rc = ++ idx;
        }
        seg[lc].val = T(mid - s + 1) * seg[cur].tag;
        seg[rc].val = T(t - mid) * seg[cur].tag;
        seg[lc].tag = seg[cur].tag;
        seg[rc].tag = seg[cur].tag;
        seg[cur].tag = 0;
    }
    
    void modify(int lo, int ro, T val) {
        rt = modify(rt, 1, n, lo, ro, val);
    }

    int modify(int cur, int s, int t, int lo, int ro, T val) {
        if (!cur) {
            seg.emplace_back();
            cur = ++ idx;
        }
        if (lo <= s && t <= ro) {
            seg[cur].val = T(t - s + 1) * val;
            seg[cur].tag = val;
            return cur; 
        }
        int mid = s + (t - s) / 2;
        pushdown(cur, s, t, mid);
        if (lo <= mid) {
            lc = modify(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            rc = modify(rc, mid + 1, t, lo, ro, val);
        }
        pushup(cur);
        return cur;
    }

    T query(int lo, int ro) {
        return query(rt, 1, n, lo, ro);
    }

    T query(int cur, int s, int t, int lo, int ro) {
        if (!cur) {
            return 0;
        }
        if (lo <= s && t <= ro) {
            return seg[cur].val;
        }
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

    int n;
    cin >> n;

    int q;
    cin >> q;

    SegmentTree<int> seg(1e9);

    while (q --) {
        int l, r;
        cin >> l >> r;
        seg.modify(l, r, 1);
        cout << n - seg.query(1, n) << '\n';
    }

    return 0;
}