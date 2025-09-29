#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

template<typename T>
struct SegmentTreeWithSplayTree {
    #define lc 2 * cur
    #define rc 2 * cur + 1

    int n;

    vector<int> vec;

    struct Node {
        T val;
        
        int p, cnt, sz;

        array<int, 2> ch;

        Node() : val{}, p{}, cnt{}, sz{}, ch{} {}

        Node(T val, int p) : val(val), p(p), cnt(1), sz(1), ch{} {}
    };
    vector<Node> spl;

    int idx{};
    
    vector<int> seg;

    SegmentTreeWithSplayTree(int n, vector<int> &vec) : n(n), vec(vec), seg(4 * (n + 1)) {
        spl.emplace_back();
        build(1, 1, n);
    }

    void pushup(int u) {
        if (u) {
            spl[u].sz = spl[spl[u].ch[0]].sz + spl[spl[u].ch[1]].sz + spl[u].cnt;
        }
    }

    void rotate(int u) {
        int p = spl[u].p, pp = spl[p].p, dir = (spl[p].ch[1] == u);
        if (pp) {
            spl[pp].ch[spl[pp].ch[1] == p] = u;
        }
        spl[u].p = pp;
        spl[p].ch[dir] = spl[u].ch[dir ^ 1];
        if (spl[u].ch[dir ^ 1]) {
            spl[spl[u].ch[dir ^ 1]].p = p;
        }
        spl[u].ch[dir ^ 1] = p;
        spl[p].p = u;
        pushup(p);
        pushup(u);
    }

    void splay(int &rt, int u, int v) {
        while (spl[u].p != v) {
            int p = spl[u].p, pp = spl[p].p;
            if (pp != v) {
                if ((spl[p].ch[1] == u) == (spl[pp].ch[1] == p)) {
                    rotate(p);
                } else {
                    rotate(u);
                }
            }
            rotate(u);
        }
        if (!v) {
            rt = u;
        }
    }

    void find(int &rt, T val) {
        if (!rt) {
            return;
        }
        int u = rt;
        while (spl[u].val != val && spl[u].ch[val > spl[u].val]) {
            u = spl[u].ch[val > spl[u].val];
        }
        splay(rt, u, 0);
    }

    int getpreidx(int &rt, T val) {
        find(rt, val);
        if (spl[rt].val < val) {
            return rt;
        }
        int u = spl[rt].ch[0];
        while (spl[u].ch[1]) {
            u = spl[u].ch[1];
        }
        splay(rt, u, 0);
        return u;
    }

    int getsucidx(int &rt, T val) {
        find(rt, val);
        if (spl[rt].val > val) {
            return rt;
        }
        int u = spl[rt].ch[1];
        while (spl[u].ch[0]) {
            u = spl[u].ch[0];
        }
        splay(rt, u, 0);
        return u;
    }

    void insert(int &rt, T val) {
        int u = rt, p = 0;
        while (u && spl[u].val != val) {
            p = u;
            u = spl[u].ch[val > spl[p].val];
        }
        if (u) {
            spl[u].cnt ++;
        } else {
            u = ++ idx;
            spl.emplace_back(val, p);
            if (p) {
                spl[p].ch[val > spl[p].val] = u;
            }
        }
        splay(rt, u, 0);
    }

    void erase(int &rt, T val) {
        int pre = getpreidx(rt, val);
        int suc = getsucidx(rt, val);
        splay(rt, pre, 0);
        splay(rt, suc, pre);
        int nd = spl[suc].ch[0];
        if (spl[nd].cnt > 1) {
            spl[nd].cnt --;
            splay(rt, nd, 0);
        } else {
            spl[suc].ch[0] = 0;
            pushup(suc);
            pushup(pre);
        }
    }

    int getrank(int rt, T val) {
        int u = rt, res = 0;
        while (u) {
            if (spl[u].val < val) {
                res += spl[spl[u].ch[0]].sz + spl[u].cnt;
                u = spl[u].ch[1];
            } else {
                u = spl[u].ch[0];
            }
        }
        return res;
    }

    T getpre(int rt, T val) {
        int u = rt;
        T res = -numeric_limits<T>::max();
        while (u) {
            if (spl[u].val < val) {
                res = spl[u].val;
                u = spl[u].ch[1];
            } else {
                u = spl[u].ch[0];
            }
        }
        return res;
    }
    
    T getsuc(int rt, T val) {
        int u = rt;
        T res = numeric_limits<T>::max();
        while (u) {
            if (spl[u].val > val) {
                res = spl[u].val;
                u = spl[u].ch[0];
            } else {
                u = spl[u].ch[1];
            }
        }
        return res;
    }

    void build(int cur, int s, int t) {
        insert(seg[cur], -numeric_limits<T>::max());
        insert(seg[cur], numeric_limits<T>::max());
        for (int i = s; i <= t; i ++) {
            insert(seg[cur], vec[i]);
        }
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        build(lc, s, mid);
        build(rc, mid + 1, t);
    }

    
    void update(int pos, T val) {
        update(1, 1, n, pos, val);
        vec[pos] = val;
    }
    
    void update(int cur, int s, int t, int pos, T val) {
        erase(seg[cur], vec[pos]);
        insert(seg[cur], val);
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        if (pos <= mid) {
            update(lc, s, mid, pos, val);
        } else {
            update(rc, mid + 1, t, pos, val);
        }
    }

    int queryrank(int lo, int ro, T val) {
        return queryrank(1, 1, n, lo, ro, val) + 1;
    }
    
    int queryrank(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getrank(seg[cur], val) - 1;
        }
        int mid = (s + t) / 2, res = 0;
        if (lo <= mid) {
            res += queryrank(lc, s, mid, lo, ro, val);
        }
        if (ro > mid) {
            res += queryrank(rc, mid + 1, t, lo, ro, val);
        }
        return res;
    }

    T querypre(int lo, int ro, T val) {
        return querypre(1, 1, n, lo, ro, val);
    }
    
    T querypre(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getpre(seg[cur], val);
        }
        int mid = (s + t) / 2;
        T res = -numeric_limits<T>::max();
        if (lo <= mid) {
            cmax(res, querypre(lc, s, mid, lo, ro, val));
        }
        if (ro > mid) {
            cmax(res, querypre(rc, mid + 1, t, lo, ro, val));
        }
        return res;
    }

    T querysuc(int lo, int ro, T val) {
        return querysuc(1, 1, n, lo, ro, val);
    }
    
    T querysuc(int cur, int s, int t, int lo, int ro, T val) {
        if (lo <= s && t <= ro) {
            return getsuc(seg[cur], val);
        }
        int mid = (s + t) / 2;
        T res = numeric_limits<T>::max();
        if (lo <= mid) {
            cmin(res, querysuc(lc, s, mid, lo, ro, val));
        }
        if (ro > mid) {
            cmin(res, querysuc(rc, mid + 1, t, lo, ro, val));
        }
        return res;
    }

    T queryval(int lo, int ro, int rk) {
        int l = 0, r = 1e8 + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (queryrank(1, 1, n, lo, ro, mid) + 1 <= rk) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> vec(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> vec[i];
    }

    SegmentTreeWithSplayTree<int> splseg(n, vec);

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << splseg.queryrank(x, y, k) << '\n';
        }
        if (opt == 2) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << splseg.queryval(x, y, k) << '\n';
        }
        if (opt == 3) {
            int x, k;
            cin >> x >> k;
            splseg.update(x, k);
        } 
        if (opt == 4) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << splseg.querypre(x, y, k) << '\n';
        }
        if (opt == 5) {
            int x, y, k;
            cin >> x >> y >> k;
            cout << splseg.querysuc(x, y, k) << '\n';
        }
    }

    return 0;
}