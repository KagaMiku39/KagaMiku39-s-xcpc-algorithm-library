#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    i64 ans = 1ll * n * k;
    for (int lo = 1, ro = 0; lo <= n; lo = ro + 1) {
        if (!(k / lo)) {
            break;
        }
        ro = min(k / (k / lo), n);
        ans -= (k / lo) * (ro - lo + 1ll) * (lo + ro) / 2;
    }

    cout << ans << '\n';

    return 0;
}