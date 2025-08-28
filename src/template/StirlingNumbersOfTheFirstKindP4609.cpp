#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 5e4 + 1, maxsz = 201, mod = 1e9 + 7;

int dp[maxn][maxsz], comb[maxsz][maxsz];

void solve() {
    int n, a, b;
    cin >> n >> a >> b;

    int ans = 1ll * dp[n - 1][a + b - 2] * comb[a + b - 2][a - 1] % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    dp[0][0] = 1;
    for (int i = 1; i < maxn; i ++) {
        for (int j = 1; j < maxsz; j ++) {
            dp[i][j] = (dp[i - 1][j - 1] + 1ll * (i - 1) * dp[i - 1][j]) % mod;
        }
    }
    
    for (int i = 0; i < maxsz; i ++) {
        comb[i][0] = 1;
    }
    for (int i = 1; i < maxsz; i ++) {
        for (int j = 1; j <= i; j ++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
    }

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}