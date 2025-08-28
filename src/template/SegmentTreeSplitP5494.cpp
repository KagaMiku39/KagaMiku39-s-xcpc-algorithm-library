#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

struct SegmentTreeSplit {
    #define lc(x) segs[x].ch[0]
    #define rc(x) segs[x].ch[1]

    struct Node {
        array<int, 2> ch;

        i64 val;

        Node() {}
        
        Node(int l, int r, i64 v) : ch{l, r}, val(v) {}
    };
    vector<Node> segs;

    int n, idx, cnt;

    vector<int> root;

    SegmentTreeSplit(int n) : n(n), idx{}, cnt(1), segs((n << 5) + 1), root(n + 1) {}

    void merge(int lt , int rt) {
        root[lt] = mergerec(root[lt], root[rt]);
    }
    
    int mergerec(int lt, int rt) {
        if (!lt || !rt) {
            return lt + rt;
        }
        segs[lt].val += segs[rt].val;
        lc(lt) = mergerec(lc(lt), lc(rt));
        rc(lt) = mergerec(rc(lt), rc(rt));
        return lt;
    }

    void split(int cur, int x, int y) {
        i64 k1 = getsum(root[cur], 1, n, 1, y), k2 = getsum(root[cur], 1, n, x, y);
        int tmp = 0;
        splitrec(root[cur], root[++ cnt], k1 - k2, 1, n);
        splitrec(root[cnt], tmp, k2, 1, n);
        root[cur] = mergerec(root[cur], tmp);
    }
    
    void splitrec(int last, int &now, i64 val, int s, int t) {
        if (segs[last].val == val) {
            return;
        }
        now = ++ idx;
        segs[now] = Node();
        int mid = (s + t) / 2;
        i64 tmp = segs[lc(last)].val;
        if (val <= tmp) {
            splitrec(lc(last), lc(now), val, s, mid);
            swap(rc(last), rc(now));
        } else {
            splitrec(rc(last), rc(now), val - tmp, mid + 1, t);
        }
        segs[now].val = segs[last].val - val;
        segs[last].val = val;
    }

    void modify(int cur, int p, int k) {
        modify(root[cur], 1, n, p, k);
    }
    
    void modify(int &cur, int s, int t, int p, int k) {
        if (!cur) {
            cur = ++ idx;
        }
        segs[cur].val += k;
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        if (p <= mid) {
            modify(lc(cur), s, mid, p, k);
        } else {
            modify(rc(cur), mid + 1, t, p, k);
        }
    }

    i64 getsum(int cur, int x, int y) {
        return getsum(root[cur], 1, n, x, y);
    }    

    i64 getsum(int cur, int s, int t, int x, int y) {
        if (x > t || y < s) {
            return 0;
        }
        if (x <= s && t <= y) {
            return segs[cur].val;
        }
        int mid = (s + t) / 2;
        return getsum(lc(cur), s, mid, x, y) + getsum(rc(cur), mid + 1, t, x, y);
    }

    int getval(int cur, i64 k) {
        if (k <= 0 || k > segs[root[cur]].val) {
            return -1;
        }
        return getval(root[cur], 1, n, k);
    }
    
    int getval(int cur, int s, int t, i64 k) {
        if (s == t) {
            return s;
        }
        int mid = (s + t) / 2;
        if (k <= segs[lc(cur)].val) {
            return getval(lc(cur), s, mid, k);
        } else {
            return getval(rc(cur), mid + 1, t, k - segs[lc(cur)].val);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTreeSplit segs(n);

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        segs.modify(1, i, x);
    }

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            int p, x, y;
            cin >> p >> x >> y;
            segs.split(p, x, y);
        }
        if (opt == 1) {
            int p, t;
            cin >> p >> t;
            segs.merge(p, t);
        }
        if (opt == 2) {
            int p, x, q;
            cin >> p >> x >> q;
            segs.modify(p, q, x);
        }
        if (opt == 3) {
            int p, x, y;
            cin >> p >> x >> y;
            cout << segs.getsum(p, x, y) << '\n';
        }
        if (opt == 4) {
            int p, k;
            cin >> p >> k;
            cout << segs.getval(p, k) << '\n';
        }
    }

    return 0;
}