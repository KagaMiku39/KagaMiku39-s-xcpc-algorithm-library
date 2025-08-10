#include <bits/stdc++.h>

using namespace std;

struct LeftistTree {
    #define ls(x) ltt[x].ch[0]
    #define rs(x) ltt[x].ch[1]
    
    int idx{};

    struct Node {
        int val, dis, p;

        array<int, 2> ch;

        Node(int val, int p) : val(val), dis{}, p(p), ch{} {}
    };
    vector<Node> ltt;

    LeftistTree() {
        ltt.emplace_back(0, 0);
        ltt[0].dis = -1;
    }

    void push(int val) {
        idx ++;
        ltt.emplace_back(val, idx);
    }

    int find(int x) {
        return ltt[x].p == x ? x : ltt[x].p = find(ltt[x].p);
    }

    int merge(int x, int y) {
        if (!x || !y) {
            return x + y;
        }
        if (ltt[x].val > ltt[y].val || (ltt[x].val == ltt[y].val && x > y)) {
            swap(x, y);
        }
        rs(x) = merge(rs(x), y);
        ltt[rs(x)].p = x;
        if (ltt[ls(x)].dis < ltt[rs(x)].dis) {
            swap(ls(x), rs(x));
        }
        ltt[x].dis = ltt[rs(x)].dis + 1;
        return x;
    }

    void mergeheaps(int x, int y) {
        if (x > idx || y > idx) {
            return;
        }
        if (ltt[x].val == INT_MAX || ltt[y].val == INT_MAX) {
            return;
        }
        int px = find(x), py = find(y);
        if (px != py) {
            ltt[px].p = ltt[py].p = merge(px, py);
        }
    }

    int gettop(int x) {
        if (x > idx || ltt[x].val == INT_MAX) {
            return -1;
        }
        int p = find(x);
        if (ltt[p].val == INT_MAX) {
            return -1;
        }
        int res = ltt[p].val;
        ltt[p].val = INT_MAX;
        ltt[ls(p)].p = ls(p);
        ltt[rs(p)].p = rs(p);
        ltt[p].p = merge(ls(p), rs(p));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    LeftistTree ltt;

    for (int i = 1; i <= n; i ++) {
        int val;
        cin >> val;
        ltt.push(val);
    }

    while (m --) {
        int opt, x, y;
        cin >> opt >> x;
        if (opt == 1) {
            cin >> y;
            ltt.mergeheaps(x, y);
        } 
        if (opt == 2) {
            cout << ltt.gettop(x) << '\n';
        }
    }

    return 0;
}