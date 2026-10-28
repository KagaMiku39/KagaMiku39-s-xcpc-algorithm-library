#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    int sq = sqrt(n) + 1, ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (a[i] >= sq) {
            for (int j = 1; j <= sq; j ++) {
                i64 k = i + 1ll * a[i] * j;
                if (k <= n && a[k] == j) {
                    ans ++;
                }
                k = i - 1ll * a[i] * j;
                if (k >= 1 && a[k] == j) {
                    ans ++;
                }
            }
        } else {
            for (int j = 1; j < sq; j ++) {
                i64 k = i + 1ll * a[i] * j;
                if (k <= n && a[k] == j) {
                    ans ++;
                }
            }
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