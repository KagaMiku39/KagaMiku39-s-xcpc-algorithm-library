#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int x;
    cin >> x;
    
    i64 m;
    cin >> m;

    i64 ans = 0;
    for (int i = 1; i <= min(1ll * x, m); i ++) {
        ans += (i ^ x) % x == 0 || (i ^ x) % i == 0; 
    }

    if (m > x) {
        i64 k1 = (m - x) / x, k2 = (m + 2 * x - 1) / x;
        ans += max(k1 - 1, 0ll);
        for (i64 i = k1 + 1; i <= k2; i ++) {
            i64 y = i * x ^ x;
            ans += y <= m && y > x;
        }
    }
    
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}