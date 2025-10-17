#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
struct LeftistTree {
    #define lc(x) ltt[x].ch[0]
    #define rc(x) ltt[x].ch[1]
    
    int idx{};
    
    vector<int> root;
    
    struct Node {
        T val;
        
        int dis{}, p;

        array<int, 2> ch{};

        Node(T val, int p) : val(val), p(p) {}
    };
    vector<Node> ltt;

    LeftistTree(int n) : root(n + 1) {
        ltt.emplace_back(0, 0); 
        ltt[0].dis = -1;
    }

    int push(T val) {
        idx ++;
        ltt.emplace_back(val, 0); 
        ltt[idx].dis = 0;
        return idx;
    }
    
    void insert(T val, int id) {
        int ind = push(val);
        root[id] = ind;
    }

    void pushup(int cur) {
        if (!cur) {
            return;
        }
        if (ltt[lc(cur)].dis < ltt[rc(cur)].dis) {
            swap(lc(cur), rc(cur));
        }
        if (ltt[cur].dis != ltt[rc(cur)].dis + 1) {
            ltt[cur].dis = ltt[rc(cur)].dis + 1;
            pushup(ltt[cur].p);
        }
    }

    int merge(int lh, int rh) {
        if (!lh || !rh) {
            return lh | rh; 
        }
        if (ltt[lh].val > ltt[rh].val || (ltt[lh].val == ltt[rh].val && lh > rh)) {
            swap(lh, rh);
        }
        rc(lh) = merge(rc(lh), rh);
        ltt[rc(lh)].p = lh; 
        
        if (ltt[lc(lh)].dis < ltt[rc(lh)].dis) {
            swap(lc(lh), rc(lh));
        }
        ltt[lh].dis = ltt[rc(lh)].dis + 1;
        return lh;
    }

    void mergeheap(int x, int y) {
        if (root[x] != root[y] && root[y] != 0) {
            root[x] = merge(root[x], root[y]);
            root[y] = 0;
        }
    }
    
    T gettop(int id) {
        return ltt[root[id]].val;
    }

    void erase(int cur, int id) { 
        int pa = ltt[cur].p, nrt = merge(lc(cur), rc(cur));
        if (pa != 0) {
            ltt[nrt].p = pa;
            if (lc(pa) == cur) {
                lc(pa) = nrt;
            } else {
                rc(pa) = nrt;
            }
            pushup(pa);
        } else {
            root[id] = nrt;
            ltt[nrt].p = 0;
        }
        ltt[cur].val = numeric_limits<T>::max();
        lc(cur) = 0;
        rc(cur) = 0;
        ltt[cur].p = 0; 
        ltt[cur].dis = 0; 
    }

    void modify(int cur, T new_val, int id) { 
        int pa = ltt[cur].p;
        if (pa) {
            if (lc(pa) == cur) {
                lc(pa) = 0;
            } else {
                rc(pa) = 0;
            }
            pushup(pa); 
        }
        int ns = merge(lc(cur), rc(cur));
        ltt[cur].val = new_val; 
        ltt[cur].p = 0;
        lc(cur) = rc(cur) = 0;
        ltt[cur].dis = 0;
        if (pa) { 
            if (ns) {
                ltt[ns].p = 0;
                root[id] = merge(root[id], ns);
            }
            root[id] = merge(root[id], cur);
        } else {
            if (ns) {
                ltt[ns].p = 0;
                root[id] = ns;
            } else {
                root[id] = 0;
            }
            root[id] = merge(root[id], cur);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    LeftistTree<i64> ltt(n);

    for (int i = 1; i <= n; i ++) {
        i64 a;
        cin >> a; 
        ltt.insert(a, i); 
    }

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            int x, y;
            cin >> x >> y;
            ltt.erase(y, x);
        }
        if (opt == 1) {
            int x;
            cin >> x;
            cout << ltt.gettop(x) << '\n';
        }
        if (opt == 2) {
            int x, y;
            cin >> x >> y;
            ltt.mergeheap(x, y);
        }
        if (opt == 3) {
            int x, y;
            cin >> x >> y;
            i64 z;
            cin >> z;
            ltt.modify(y, z, x);
        }
    }

    return 0;
}