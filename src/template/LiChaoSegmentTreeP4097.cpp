#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

struct LiChaoSegmentTree {
    #define lc 2 * cur
    #define rc 2 * cur + 1

    static constexpr double eps = 1e-9;

    int n;

    struct Node {
        int id;
    };
    vector<Node> seg;

    vector<tuple<double, double>> lin;

    LiChaoSegmentTree(int n) : n(n), seg(4 * n) {
        lin.emplace_back(0, -DBL_MAX);
    }

    double gety(int id, int x) {
        if (id == 0) {
            return -DBL_MAX;
        }
        return get<0>(lin[id]) * x + get<1>(lin[id]);
    }

    int cmp(double a, double b) {
        if (a - b > eps) {
            return 1;
        }
        if (b - a > eps) {
            return -1;
        }
        return 0;
    }
    
    void add(int lo, int ro, double k, double b) {
        lin.emplace_back(k, b);
        add(1, 1, n, lo, ro, ssize(lin) - 1);
    }
    
    void add(int cur, int s, int t, int lo, int ro, int id) {
        if (lo <= s && t <= ro) {
            int mid = (s + t) / 2;
            int cm = cmp(gety(id, mid), gety(seg[cur].id, mid));
            if (cm == 1 || (cm == 0 && id < seg[cur].id)) {
                swap(id, seg[cur].id);
            }
            int cl = cmp(gety(id, s), gety(seg[cur].id, s));
            if (cl == 1 || (cl == 0 && id < seg[cur].id)) {
                add(lc, s, mid, lo, ro, id);
            }
            
            int cr = cmp(gety(id, t), gety(seg[cur].id, t));
            if (cr == 1 || (cr == 0 && id < seg[cur].id)) {
                add(rc, mid + 1, t, lo, ro, id);
            }
            return;
        }
        int mid = (s + t) / 2;
        if (lo <= mid) {
            add(lc, s, mid, lo, ro, id);
        }
        if (ro > mid) {
            add(rc, mid + 1, t, lo, ro, id);
        }
    }
    
    bool cmax(pair<double, int> &a, const pair<double, int> &b) {
        int res = cmp(a.first, b.first);
        if (res == 1) {
            return false;
        }
        if (res == -1) {
            a = b;
            return true;
        }
        if (b.second < a.second) {
            a = b;
            return true;
        }
        return false;
    }
    
    auto query(int x) {
        return query(1, 1, n, x);
    }

    pair<double, int> query(int cur, int s, int t, int x) {
        pair<double, int> res = {gety(seg[cur].id, x), seg[cur].id};
        if (s == t) {
            return res;
        }
        int mid = (s + t) / 2;
        if (x <= mid) {
            cmax(res, query(lc, s, mid, x));
        }
        if (x > mid) {
            cmax(res, query(rc, mid + 1, t, x));
        }
        return res;
    }
};

constexpr int m1 = 39989, m2 = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    LiChaoSegmentTree seg(m1);
    
    int last = 0;
    while (n --) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            int x;
            cin >> x;
            x = (x + last - 1) % m1 + 1;
            last = seg.query(x).second;
            cout << last << '\n';
        }
        if (opt == 1) {
            int x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;   
            x0 = (x0 + last - 1) % m1 + 1;
            x1 = (x1 + last - 1) % m1 + 1;
            y0 = (y0 + last - 1) % m2 + 1;
            y1 = (y1 + last - 1) % m2 + 1;
            if (x0 > x1) {
                swap(x0, x1);
                swap(y0, y1);
            }
            double k, b;
            if (x0 == x1) {
                k = 0;
                b = max(y0, y1);
            } else {
                k = 1.0 * (y1 - y0) / (x1 - x0);
                b = y0 - k * x0;
            }
            seg.add(x0, x1, k, b);
        }
    }

    return 0;
}