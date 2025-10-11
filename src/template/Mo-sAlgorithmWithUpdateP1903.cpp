#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }

    int sz = cbrt(1ll * n * n), t = 0, idx = 0;
    vector<pair<int, int>> upd{{}};
    vector<tuple<int, int, int, int, int, int>> que;
    for (int i = 1; i <= m; i ++) {
        char op;
        cin >> op;
        if (op == 'Q') {
            int l, r;
            cin >> l >> r;
            que.emplace_back(1 + l / sz, 1 + r / sz, t, l, r, ++ idx);
        } else {
            int p, col;
            cin >> p >> col;
            t ++;
            upd.emplace_back(p, col);
        }
    }

    sort(begin(que), end(que));

    t = 0;
    int lo = 1, ro = 0, res = 0;
    vector<int> cnt(1e6 + 1), ans(idx + 1);
    auto add = [&](int x) {
        res += !cnt[c[x]];
        cnt[c[x]] ++;
    };
    auto del = [&](int x) {
        cnt[c[x]] --;
        res -= !cnt[c[x]];
    };
    for (auto &[_, __, tt, l, r, id]: que) {
        while (lo > l) {
            lo --;
            add(lo);
        }
        while (ro < r) {
            ro ++;
            add(ro);
        }
        while (lo < l) {
            del(lo);
            lo ++;
        }
        while (ro > r) {
            del(ro);
            ro --;
        }
        while (t < tt) {
            t ++;
            auto &[p, col] = upd[t];
            if (l <= p && p <= r) {
                del(p);
                swap(c[p], col);
                add(p);
            } else {
                swap(c[p], col);
            }
        }
        while (t > tt) {
            auto &[p, col] = upd[t];
            if (l <= p && p <= r) {
                del(p);
                swap(c[p], col);
                add(p);
            } else {
                swap(c[p], col);
            }
            t --;
        }
        ans[id] = res;
    }

    for (int i = 1; i <= idx; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}