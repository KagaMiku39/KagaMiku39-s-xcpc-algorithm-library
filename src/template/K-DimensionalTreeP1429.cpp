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

struct KDTree {
    #define lc(x) kdt[x].ch[0]
    #define rc(x) kdt[x].ch[1]

    const int dimension = 2;

    int n;

    double ans = 2e18;

    int rt, cur;

    struct Node {
        array<int, 2> ch;

        double v[2], low[2], up[2];
    };
    vector<Node> kdt;

    int dim;

    KDTree() {
        n = 0;
        rt = 0;
        cur = 0;
        dim = 0;
        kdt.emplace_back();
    }

    void insert(double x, double y) {
        n ++;
        kdt.emplace_back();
        kdt[n].v[0] = x;
        kdt[n].v[1] = y;
    }

    void pushup(int p) {
        for (int i = 0; i < dimension; i ++) {
            kdt[p].low[i] = kdt[p].up[i] = kdt[p].v[i];
            if (lc(p)) {
                cmin(kdt[p].low[i], kdt[lc(p)].low[i]);
                cmax(kdt[p].up[i], kdt[lc(p)].up[i]);
            }
            if (rc(p)) {
                cmin(kdt[p].low[i], kdt[rc(p)].low[i]);
                cmax(kdt[p].up[i], kdt[rc(p)].up[i]);
            }
        }
    }
    
    int build(int lo, int ro, int k) {
        if (lo > ro) {
            return 0;
        }
        int mid = (lo + ro) / 2;
        dim = k;
        nth_element(next(begin(kdt), lo), next(begin(kdt), mid), next(begin(kdt), ro + 1), [&](const Node &a, const Node &b) {
            return a.v[dim] < b.v[dim];
        });
        lc(mid) = build(lo, mid - 1, k ^ 1);
        rc(mid) = build(mid + 1, ro, k ^ 1);
        pushup(mid);
        return mid;
    }

    double getsq(double x) {
        return x * x;
    }

    double getdis(int p) {
        double s = 0;
        for (int i = 0; i < dimension; i ++) {
            s += getsq(kdt[cur].v[i] - kdt[p].v[i]);
        }
        return s;
    }

    double getmindis(int p) {
        if (!p) {
            return 2e18;
        }
        double s = 0;
        for (int i = 0; i < dimension; i ++) {
            s += getsq(max(kdt[cur].v[i] - kdt[p].up[i], (double)0.0)) + getsq(max(kdt[p].low[i] - kdt[cur].v[i], (double)0.0));
        }
        return s;
    }

    void query(int p) {
        if (!p) {
            return;
        }
        if (p != cur) {
            cmin(ans, getdis(p));
        }
        double dl = getmindis(lc(p)), dr = getmindis(rc(p));
        if (dl < dr) {
            if (dl < ans) {
                query(lc(p));
            }
            if (dr < ans) {
                query(rc(p));
            }
        } else {
            if (dr < ans) {
                query(rc(p));
            }
            if (dl < ans) {
                query(lc(p));
            }
        }
    }
    
    double solve() {
        if (n <= 1) {
            return 0.0;
        }
        rt = build(1, n, 0);
        for (int i = 1; i <= n; i ++) {
            cur = i;
            query(rt);
        }
        return sqrt(ans);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    KDTree kdt;

    for (int i = 1; i <= n; i ++) {
        double x, y;
        cin >> x >> y;
        kdt.insert(x, y);
    }

    cout << fixed << setprecision(4) << kdt.solve() << '\n';
    
    return 0;
}