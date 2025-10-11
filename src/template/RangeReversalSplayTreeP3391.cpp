#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct SplayTree {
    int rt, idx{};
    
    struct Node {
        T val;

        int p, sz, tag;

        array<int, 2> ch;

        Node() : val{}, p{}, sz{}, tag{}, ch{} {}

        Node(T val, int p) : val(val), p(p), sz(1), tag{}, ch{} {} 
    };
    vector<Node> spl;

    SplayTree() {
        spl.emplace_back();
        insert(numeric_limits<T>::min());
        insert(numeric_limits<T>::max());
    }

    void pushup(int cur) {
        if (cur) {
            spl[cur].sz = spl[spl[cur].ch[0]].sz + spl[spl[cur].ch[1]].sz + 1;
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

    void insert(T val) {
        int u = rt, p = 0;
        while (u && spl[u].val != val) {
            p = u;
            u = spl[u].ch[val > spl[u].val];
        }
        u = ++ idx;
        spl.emplace_back(val, p);
        if (p) {
            spl[p].ch[val > spl[p].val] = u;
        }
        splay(u, 0);
    }

    void pushdown(int cur) {
        if (!spl[cur].tag) {
            return;
        }
        swap(spl[cur].ch[0], spl[cur].ch[1]);
        spl[spl[cur].ch[0]].tag ^= 1;
        spl[spl[cur].ch[1]].tag ^= 1;
        spl[cur].tag = 0;        
    }

    T getval(T rk) {
        int u = rt;
        rk ++; 
        while (true) {
            pushdown(u);
            int lc = spl[u].ch[0];
            if (spl[lc].sz >= rk) {
                u = lc;
            } else if (spl[lc].sz + 1 >= rk) {
                break;
            } else {
                rk -= spl[lc].sz + 1;
                u = spl[u].ch[1];
            }
        }
        return u;
    }

    void flip(int l, int r) {
        int lo = getval(l - 1), ro = getval(r + 1);
        splay(lo, 0);
        splay(ro, lo);
        spl[spl[ro].ch[0]].tag ^= 1;
    }

    void print(int n) {
        auto dfs = [&](auto &self, int cur) -> void {
            if (!cur) {
                return;
            }
            pushdown(cur);
            self(self, spl[cur].ch[0]);
            if (spl[cur].val != numeric_limits<T>::min() && spl[cur].val != numeric_limits<T>::max()) {
                cout << spl[cur].val << " \n"[!-- n];
            }
            self(self, spl[cur].ch[1]);
        };
        dfs(dfs, rt);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;

    SplayTree<int> spl;

    for (int i = 1; i <= n; i ++) {
        spl.insert(i);
    }

    while (m --) {
        int l, r;
        cin >> l >> r;
        spl.flip(l, r);
    }

    spl.print(n);

    return 0;
}