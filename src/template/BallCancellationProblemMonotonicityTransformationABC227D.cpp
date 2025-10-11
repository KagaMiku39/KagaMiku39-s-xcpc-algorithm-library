#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    i64 lo = 1, ro = LLONG_MAX;
    auto pred = [&](i64 x) {
        i64 sum = 0;
        for (int i = 1; i <= n; i ++) {
            sum += min(a[i], x);
        }
        return x <= sum / k;
    };
    while (lo + 1 < ro) {
        i64 mid = lo + (ro - lo) / 2;
        if (pred(mid)) {
            lo = mid;
        } else {
            ro = mid;
        }
    }

    cout << lo << '\n';

    return 0;
}