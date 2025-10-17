#include <bits/stdc++.h>

using namespace std;

struct PersistentDSU {
    int n, m;

    template<typename T>
    struct PersistentSegmentTree {
        #define lc(x) hjt[x].ch[0]
        #define rc(x) hjt[x].ch[1]

        int n, idx{}; 
        
        vector<int> vec, rt;
        
        struct Node{
            T val; 
            array<int, 2> ch;
        };
        vector<Node> hjt; 
        
        PersistentSegmentTree(int n, int m, const vector<T> &vec) : n(n), hjt(2 * n + 22 * m), vec(vec), rt(m + 1) {
            build(rt[0], 1, n);
        }

        void build(int &cur, int s, int t) {
            cur = ++ idx;
            if (s == t) {
                hjt[cur].val = vec[s];
                return;
            }
            int mid = (s + t) / 2;
            build(lc(cur), s, mid);
            build(rc(cur), mid + 1, t);
        }

        void modify(int id, int ver, int pos, T val) {
            update(rt[id], rt[ver], 1, n, pos, val);
        }
        
        void update(int &now, int last, int s, int t, int pos, T val) {
            now = ++ idx;
            hjt[now] = hjt[last];
            if (s == t) {
                hjt[now].val = val;
                return;
            }
            int mid = (s + t) / 2;
            if (pos > mid) {
                update(rc(now), rc(last), mid + 1, t, pos, val);
            } else {
                update(lc(now), lc(last), s, mid, pos, val);
            }
        }

        T query(int ver, int pos) {
            return query(rt[ver], 1, n, pos);
        }

        T query(int cur, int s, int t, int pos) {
            if (s == t) {
                return hjt[cur].val;
            }
            int mid = (s + t) / 2;
            if (pos > mid) {
                return query(rc(cur), mid + 1, t, pos);
            } else {
                return query(lc(cur), s, mid, pos);
            }
        }
    };
    PersistentSegmentTree<int> p, rk; 

    PersistentDSU(int n, int m) : n(n), m(m), p(n, m, init()), rk(n, m, vector<int>(n + 1)) {}

    vector<int> init() {
        vector<int> vec(n + 1);
        iota(begin(vec), end(vec), 0);
        return vec;
    }

    int find(int ver, int x) {
        int px = p.query(ver, x);
        if (x == px) {
            return x;
        }
        return find(ver, px);
    }

    void merge(int now, int last, int a, int b) {
        int pa = find(last, a), pb = find(last, b);
        if (pa == pb) {
            p.rt[now] = p.rt[last];
            rk.rt[now] = rk.rt[last];
            return;
        }
        int ra = rk.query(last, pa), rb = rk.query(last, pb);
        if (ra > rb) {
            swap(pa, pb);
        }
        p.modify(now, last, pa, pb);
        if (ra == rb) {
            int nrk = rb + 1;
            rk.modify(now, last, pb, nrk);
        } else {
            rk.rt[now] = rk.rt[last];
        }
    }
    
    void rollback(int cur, int ver) {
        p.rt[cur] = p.rt[ver];
        rk.rt[cur] = rk.rt[ver];
    }
    
    bool query(int now, int last, int a, int b) {
        p.rt[now] = p.rt[last];
        rk.rt[now] = rk.rt[last];
        return find(last, a) == find(last, b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    PersistentDSU pdsu(n, m);
    
    for (int i = 1; i <= m; i ++) {
        int opt;
        cin >> opt;
        int last = i - 1;
        if (opt == 1) {
            int a, b;
            cin >> a >> b;
            pdsu.merge(i, last, a, b);
        }
        if (opt == 2) {
            int k;
            cin >> k;
            pdsu.rollback(i, k);
        }
        if (opt == 3) {
            int a, b;
            cin >> a >> b;
            cout << pdsu.query(i, last, a, b) << '\n';
        }
    }

    return 0;
}