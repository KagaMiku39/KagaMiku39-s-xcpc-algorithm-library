#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
    }

    int sq = sqrt(m), sz = 1.5 * (n + sq - 1) / sq;
    vector<tuple<int, int, int, int>> que;
    for (int i = 1; i <= m; i ++) {
        int l, r;
        cin >> l >> r;
        que.emplace_back(1 + l / sz, r, l, i);
    }

    sort(begin(que), end(que), [&](const auto &a, const auto &b) {
        return get<0>(a) & 1 
            ? tie(get<0>(a), get<1>(a)) < tie(get<0>(b), get<1>(b)) 
            : tie(get<0>(a), get<1>(b)) < tie(get<0>(b), get<1>(a));
    });

    int lo = 1, ro = 0;
    i64 res = 0;
    vector<int> cnt(n + 1);
    vector<string> ans(m + 1);
    auto add = [&](int x) {
        res += 2 * cnt[c[x]];
        cnt[c[x]] ++;
    };
    auto del = [&](int x) {
        cnt[c[x]] --;
        res -= 2 * cnt[c[x]];
    };
    for (auto &[_, r, l, id]: que) {
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
        i64 g = gcd(res, (ro - lo + 1ll) * (ro - lo));
        ans[id] = lo != ro ? to_string(res / g) + '/' + to_string((ro - lo + 1ll) * (ro - lo) / g) : "0/1";
    }

    for (int i = 1; i <= m; i ++) {
        cout << ans[i] << '\n';
    }

    return 0;
}