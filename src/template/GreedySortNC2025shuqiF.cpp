#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, c;
    cin >> n >> k >> c;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i ++) {
        a[i] -= 1ll * i * c;
    }

    sort(next(begin(a)), end(a), greater<i64>());

    i64 ans = 0;
    for (int i = 1; i <= k; i ++) {
        ans += a[i];
    }

    ans += (1ll + k) * k / 2 * c;

    cout << ans << '\n';

    return 0;
}