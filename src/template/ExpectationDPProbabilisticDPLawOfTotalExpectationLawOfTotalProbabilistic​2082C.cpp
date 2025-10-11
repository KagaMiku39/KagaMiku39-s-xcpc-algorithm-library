#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

constexpr int mod = 1e9 + 7, inv = 5e8 + 4;

void solve() {   
    int n;
    cin >> n;

    string x;
    cin >> x;

    // int ans = 0;
    // for (int i = n - 1; i; i --) {
    //     if (x[i] == '0') {
    //         ans = 1ll * ans * inv % mod;
    //     } else {
    //         ans = (ans + (1ll - ans) * inv % mod) % mod;
    //     }
    // }

    // ans = (n - 1ll + ans + mod) % mod;

    // cout << ans << '\n';

    x = '0' + x;

    int cnt = 1;
    vector<array<int, 2>> dp(n + 1);
    for (int i = 2; i <= n; i ++) {
        bool j = x[i - 1] - '0';
        if (x[i] == '0') {
            dp[i][0] = (dp[i - 1][j] + 1) % mod;
            dp[i][1] = (1 + inv * i64(dp[i - cnt - 1][1] + cnt) % mod + 1ll * inv * dp[i - 1][j] % mod) % mod;
            cnt = 0;
        } else {
            cnt ++;
            dp[i][1] = (inv * i64(dp[i - cnt][1] + cnt) % mod + inv * (1ll + dp[i - 1][j]) % mod) % mod;
        }
    }

    cout << dp[n][x[n] - '0'] << '\n';
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