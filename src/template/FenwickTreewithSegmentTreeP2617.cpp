#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct FenwickTreeWithSegmentTree {
    int n, mx;
    
    vector<int> vec, mp;

    struct Node {
        int sum{};

        array<int, 2> ch{};
    };
    vector<Node> seg;
    
    int idx{};

    vector<int> rt, rt1, rt2;
    
    FenwickTreeWithSegmentTree(int n, int mx, vector<int>& vec, vector<int>& mp) : n(n), mx(mx), vec(vec), mp(mp), rt(n + 1), seg(400 * n) {}

    int lowbit(int x) {
        return x & -x;
    }

    void update(int &cur, int s, int t, int pos, int k) {
        if (!cur) {
            cur = ++ idx;
        }
        seg[cur].sum += k;
        if (s == t) {
            return;
        }
        int mid = (s + t) / 2;
        if (pos <= mid) {
            update(seg[cur].ch[0], s, mid, pos, k);
        } else {
            update(seg[cur].ch[1], mid + 1, t, pos, k);
        }
    }

    void update(int pos, int k) {
        int tmp = lower_bound(next(begin(mp)), end(mp), vec[pos]) - begin(mp);
        while (pos <= n) {
            update(rt[pos], 1, mx, tmp, k);
            pos += lowbit(pos);
        }
    }

    int getrank(int s, int t, int k) {
        if (s == t) {
            return s;
        }
        int mid = (s + t) / 2, sum = 0;
        for (int cur : rt2) {
            sum += seg[seg[cur].ch[0]].sum;
        }
        for (int cur : rt1) {
            sum -= seg[seg[cur].ch[0]].sum;
        }
        if (sum >= k) {
            for (int &cur : rt1) {
                cur = seg[cur].ch[0];
            }
            for (int &cur : rt2) {
                cur = seg[cur].ch[0];
            }
            return getrank(s, mid, k);
        } else {
            for (int &cur : rt1) {
                cur = seg[cur].ch[1];
            }
            for (int &cur : rt2) {
                cur = seg[cur].ch[1];
            }
            return getrank(mid + 1, t, k - sum);
        }
    }

    int query(int lo, int ro, int k) {
        rt1.clear();
        rt2.clear();
        int x = lo - 1;
        while (x > 0) {
            rt1.push_back(rt[x]);
            x -= lowbit(x);
        }
        int y = ro;
        while (y > 0) {
            rt2.push_back(rt[y]);
            y -= lowbit(y);
        }
        return mp[getrank(1, mx, k)];
    }

    void modify(int pos, int val) {
        update(pos, -1);
        vec[pos] = val;
        update(pos, 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), vec;
    vec.push_back(0);

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        vec.push_back(a[i]);
    }

    vector<tuple<char, int, int, int>> que(m);
    for (int i = 0; i < m; i ++) {
        char type;
        cin >> type;
        if (type == 'Q') {
            int l, r, k;
            cin >> l >> r >> k;
            que[i] = {type, l, r, k};
        } else {
            int pos, val;
            cin >> pos >> val;
            que[i] = {type, pos, val, 0};
            vec.push_back(val);
        }
    }

    sort(next(begin(vec)), end(vec));

    vec.erase(unique(next(begin(vec)), end(vec)), end(vec));

    FenwickTreeWithSegmentTree bitseg(n, ssize(vec) - 1, a, vec);

    for (int i = 1; i <= n; i ++) {
        bitseg.update(i, 1);
    }

    for (auto& [op, a, b, c] : que) {
        if (op == 'Q') {
            cout << bitseg.query(a, b, c) << '\n';
        } else {
            bitseg.modify(a, b);
        }
    }

    return 0;
}