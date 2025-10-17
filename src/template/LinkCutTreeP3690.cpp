#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct LinkCutTree {
    struct Node {
        T val, sum;

        int p;

        bool tag;
        
        array<int, 2> ch;
    };
    vector<Node> lct;

    LinkCutTree(int n, const vector<T> &vec) : lct(n + 1) {
        lct[0].val = lct[0].sum = T();
        for (int i = 1; i <= n; i ++) {
            lct[i].val = vec[i];
            lct[i].sum = vec[i];
        }
    }

    void pushup(int x) {
        lct[x].sum = lct[lct[x].ch[0]].sum ^ lct[lct[x].ch[1]].sum ^ lct[x].val;
    }

    void pushdown(int x) {
        if (lct[x].tag) {
            swap(lct[x].ch[0], lct[x].ch[1]); 
            lct[lct[x].ch[0]].tag ^= 1; 
            lct[lct[x].ch[1]].tag ^= 1; 
            lct[x].tag = false;
        }
    }

    bool isroot(int x) {
        return lct[lct[x].p].ch[0] != x && lct[lct[x].p].ch[1] != x;
    }

    void rotate(int x) {
        int y = lct[x].p, z = lct[y].p;
        int d = (lct[y].ch[1] == x);
        if (!isroot(y)) {
            lct[z].ch[lct[z].ch[1] == y] = x;
        }
        lct[x].p = z;
        lct[y].ch[d] = lct[x].ch[d ^ 1];
        if (lct[x].ch[d ^ 1]) {
            lct[lct[x].ch[d ^ 1]].p = y;
        }
        lct[x].ch[d ^ 1] = y;
        lct[y].p = x;
        pushup(y);
        pushup(x);
    }
    
    void pushall(int x) {
        if (!isroot(x)) {
            pushall(lct[x].p);
        }
        pushdown(x);
    }
    
    void splay(int x) {
        pushall(x);
        while (!isroot(x)) {
            int y = lct[x].p, z = lct[y].p;
            if (!isroot(y)) {
                if ((lct[y].ch[0] == x) ^ (lct[z].ch[0] == y)) {
                    rotate(x);
                } else {
                    rotate(y);
                }
            }
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = lct[x].p) {
            splay(x);
            lct[x].ch[1] = y;
            pushup(x);
        }
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        lct[x].tag ^= 1;
    }

    int findroot(int x) {
        access(x);
        splay(x);
        while (lct[x].ch[0]) {
            pushdown(x);
            x = lct[x].ch[0];
        }
        splay(x);
        return x;
    }

    void split(int u, int v) {
        makeroot(u);
        access(v);
        splay(v);
    }

    T getsum(int u, int v) {
        split(u, v);
        return lct[v].sum;
    }

    void link(int u, int v) {
        makeroot(u);
        if (findroot(v) != u) {
            lct[u].p = v;
        }
    }

    void cut(int u, int v) {
        makeroot(u);
        if (findroot(v) == u && lct[v].p == u && !lct[v].ch[0]) {
            lct[v].p = 0;
            lct[u].ch[1] = 0;
            pushup(u);
        }
    }

    void modify(int u, T val) {
        splay(u);
        lct[u].val = val;
        pushup(u);
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

    LinkCutTree<int> lct(n, vec);
    
    while (m --) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 0) {
            cout << lct.getsum(x, y) << '\n';
        }
        if (opt == 1) {
            lct.link(x, y);
        }
        if (opt == 2) {
            lct.cut(x, y);
        }
        if (opt == 3) {
            lct.modify(x, y);
        }
    }

    return 0;
}