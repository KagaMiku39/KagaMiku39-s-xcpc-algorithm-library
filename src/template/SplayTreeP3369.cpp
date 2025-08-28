#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SplayTree {
    int rt, idx{};
    
    struct Node {
        T val;

        int p, cnt, sz;

        array<int, 2> ch;

        Node() : val{}, p{}, cnt{}, sz{}, ch{} {}

        Node(T val, int p) : val(val), p(p), cnt(1), sz(1), ch{} {} 
    };
    vector<Node> spl;

    SplayTree() {
        spl.emplace_back();
        insert(numeric_limits<T>::min());
        insert(numeric_limits<T>::max());
    }

    void pushup(int cur) {
        if (cur) {
            spl[cur].sz = spl[spl[cur].ch[0]].sz + spl[spl[cur].ch[1]].sz + spl[cur].cnt;
        }
    }

    void rotate(int cur) {
        int p = spl[cur].p, pp = spl[p].p, dir = (spl[p].ch[1] == cur);
        if (pp) {
            spl[pp].ch[spl[pp].ch[1] == p] = cur;
        }
        spl[cur].p = pp;
        spl[p].ch[dir] = spl[cur].ch[dir ^ 1];
        if (spl[cur].ch[dir ^ 1]) {
            spl[spl[cur].ch[dir ^ 1]].p = p;
        }
        spl[cur].ch[dir ^ 1] = p;
        spl[p].p = cur;
        pushup(p);
        pushup(cur);
    }

    void splay(int u, int v) {
        while (spl[u].p != v) {
            int p = spl[u].p, pp = spl[p].p;
            if (pp != v) {
                if ((spl[pp].ch[1] == p) == (spl[p].ch[1] == u)) {
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

    void find(T val) {
        if (!rt) {
            return;
        }
        int u = rt;
        while (spl[u].val != val && spl[u].ch[val > spl[u].val]) {
            u = spl[u].ch[val > spl[u].val];
        }
        splay(u, 0);
    }
    
    T getpre(T val) {
        return spl[getpreidx(val)].val;
    }
    
    int getpreidx(T val) {
        find(val);
        if (spl[rt].val < val) {
            return rt;
        }
        int cur = spl[rt].ch[0];
        while (spl[cur].ch[1]) {
            cur = spl[cur].ch[1];
        }
        splay(cur, 0);
        return cur;
    }

    T getsuc(T val) {
        return spl[getsucidx(val)].val;
    }

    int getsucidx(T val) {
        find(val);
        if (spl[rt].val > val) {
            return rt;
        }
        int cur = spl[rt].ch[1];
        while (spl[cur].ch[0]) {
            cur = spl[cur].ch[0];
        }
        splay(cur, 0);
        return cur;
    }

    void insert(T val) {
        int u = rt, p = 0;
        while (u && spl[u].val != val) {
            p = u;
            u = spl[u].ch[val > spl[u].val];
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
        splay(u, 0);
    }

    void erase(T val) {
        int pre = getpreidx(val), suc = getsucidx(val);
        splay(pre, 0);
        splay(suc, pre);
        int lc = spl[suc].ch[0];
        if (spl[lc].cnt > 1) {
            spl[lc].cnt --;
            splay(lc, 0);
        } else {
            spl[suc].ch[0] = 0;
            splay(suc, 0);
        }
    }

    int getrank(T val) {
        insert(val);
        find(val);
        erase(val);
        return spl[spl[rt].ch[0]].sz;
    }

    T getval(T rk) {
        int u = rt;
        rk ++; 
        while (true) {
            int lc = spl[u].ch[0];
            if (spl[lc].sz >= rk) {
                u = lc;
            } else if (spl[lc].sz + spl[u].cnt >= rk) {
                break;
            } else {
                rk -= spl[lc].sz + spl[u].cnt;
                u = spl[u].ch[1];
            }
        }
        splay(u, 0);
        return spl[rt].val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cin >> n;

    SplayTree<int> spl;

    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            spl.insert(x);
        } 
        if (opt == 2) {
            spl.erase(x);
        } 
        if (opt == 3) {
            cout << spl.getrank(x) << '\n';
        } 
        if (opt == 4) {
            cout << spl.getval(x) << '\n';
        } 
        if (opt == 5) {
            cout << spl.getpre(x) << '\n';
        } 
        if (opt == 6) {
            cout << spl.getsuc(x) << '\n';
        } 
    }

    return 0;
}