#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct LeftistTree {
    #define lc(x) ltt[x].ch[0]
    #define rc(x) ltt[x].ch[1]
    
    int idx{};

    struct Node {
        T val;

        int dis{}, p;

        array<int, 2> ch{};

        Node(int val, int p) : val(val), p(p) {}
    };
    vector<Node> ltt;

    LeftistTree() {
        ltt.emplace_back(0, 0);
        ltt[0].dis = -1;
    }

    void push(T val) {
        idx ++;
        ltt.emplace_back(val, idx);
    }

    int find(int x) {
        return ltt[x].p == x ? x : ltt[x].p = find(ltt[x].p);
    }

    int merge(int lh, int rh) {
        if (!lh || !rh) {
            return lh + rh;
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
        if (x > idx || y > idx) {
            return;
        }
        if (ltt[x].val == numeric_limits<T>::max() || ltt[y].val == numeric_limits<T>::max()) {
            return;
        }
        int px = find(x), py = find(y);
        if (px != py) {
            ltt[px].p = ltt[py].p = merge(px, py);
        }
    }

    T gettop(int id) {
        if (id > idx || ltt[id].val == numeric_limits<T>::max()) {
            return -1;
        }
        int p = find(id);
        if (ltt[p].val == numeric_limits<T>::max()) {
            return -1;
        }
        int res = ltt[p].val;
        ltt[p].val = numeric_limits<T>::max();
        ltt[lc(p)].p = lc(p);
        ltt[rc(p)].p = rc(p);
        ltt[p].p = merge(lc(p), rc(p));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    LeftistTree<int> ltt;

    for (int i = 1; i <= n; i ++) {
        int val;
        cin >> val;
        ltt.push(val);
    }

    while (m --) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y;
            cin >> x >> y;
            ltt.mergeheap(x, y);
        } 
        if (opt == 2) {
            int x;
            cin >> x;
            cout << ltt.gettop(x) << '\n';
        }
    }

    return 0;
}