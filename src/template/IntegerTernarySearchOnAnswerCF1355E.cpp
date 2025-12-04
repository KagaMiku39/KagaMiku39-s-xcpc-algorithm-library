#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, r, m;
    cin >> n >> a >> r >> m;

    vector<int> h(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> h[i];
    }

    cmin(m, a + r);

    int lo = 0, ro = 1e9;
    auto pred = [&](int x) -> i64 {
        i64 sum[2]{};
        for (int i = 1; i <= n; i ++) {
            sum[h[i] >= x] += abs(h[i] - x);
        }
        i64 mi = min(sum[0], sum[1]), mx = max(sum[0], sum[1]); 
        return mi * m + (mx - mi) * (sum[0] <= sum[1] ? r : a);
    };
    while (lo + 3 < ro) {
        // int ml = lo + (ro - lo) / 3, mr = ro - (ro - lo) / 3;
        // int ml = (2ll * lo + ro) / 3, mr = (2ll * ro + lo) / 3;
        int ml = lo + (ro - lo + 1) / 3, mr = ro - (ro - lo + 1) / 3;
        if (pred(ml) < pred(mr)) {
            ro = mr;
        } else {
            lo = ml;
        }
    }

    i64 ans = LLONG_MAX;
    for (int i = lo; i <= ro; i ++) {
        cmin(ans, pred(i));
    }

    cout << ans << '\n';

    return 0;
}