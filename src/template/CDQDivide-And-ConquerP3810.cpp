#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> bit;

    FenwickTree(int n) : n(n), bit(n + 1) {}

    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, int val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    
    int query(int pos) {
        int res = 0;
        while (pos) {
            res += bit[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
};

struct Element {
    int x, y, z, cnt, res;

    bool operator < (const Element &o) const {
        return tuple{x, y, z} < tuple{o.x, o.y, o.z};
    }

    bool operator == (const Element &o) const {
        return tuple{x, y, z} == tuple{o.x, o.y, o.z};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    
    vector<Element> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        auto &[x, y, z, cnt, res] = a[i];
        cin >> x >> y >> z;
        cnt = 1;
        res = 0;
    }

    sort(next(begin(a)), end(a));
    
    int p = 0;
    vector<Element> b(n + 1);
    if (n > 0) {
        b[++ p] = a[1];
        for (int i = 2; i <= n; i ++) {
            if (a[i] == a[i - 1]) {
                b[p].cnt ++;
            } else {
                b[++ p] = a[i];
            }
        }
    }
    
    FenwickTree bit(k);
    
    auto cdq = [&](auto &self, int lo, int ro) -> void {
        if (lo >= ro) {
            return;
        }
        int mid = (lo + ro) / 2;
        self(self, lo, mid);
        self(self, mid + 1, ro);
        int i = lo, j = mid + 1;
        while (i <= mid && j <= ro) {
            if (b[i].y <= b[j].y) {
                bit.add(b[i].z, b[i].cnt);
                i ++;
            } else {
                b[j].res += bit.query(b[j].z);
                j ++;
            }
        }
        while (i <= mid) {
            bit.add(b[i].z, b[i].cnt);
            i ++;
        }
        while (j <= ro) {
            b[j].res += bit.query(b[j].z);
            j ++;
        }
        for (int l = lo; l <= mid; l ++) {
            bit.add(b[l].z, -b[l].cnt);
        }
        sort(next(begin(b), lo), next(begin(b), ro + 1), [&](const Element &l, const Element &r) {
            return l.y < r.y;
        });
    };

    if (p > 0) {
        cdq(cdq, 1, p);
    }
    
    vector<int> ans(n);
    for (int i = 1; i <= p; i ++) {
        ans[b[i].res + b[i].cnt - 1] += b[i].cnt;
    }
    
    for (int i = 0; i < n; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}