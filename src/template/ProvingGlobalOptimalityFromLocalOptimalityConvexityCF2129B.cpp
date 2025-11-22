#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {
    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        int lo = 0, ro = 0;
        for (int j = 1; j < i; j ++) {
            lo += p[j] > p[i];
        }
        for (int j = i + 1; j <= n; j ++) {
            ro += p[j] > p[i];
        }
        ans += min(lo, ro);
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