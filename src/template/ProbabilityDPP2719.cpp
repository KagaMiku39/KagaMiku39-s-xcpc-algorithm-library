#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    n /= 2;

    if (n == 1) {
        cout << "0.0000\n";
        return 0;
    }

    vector<vector<double>> dp(n + 1, vector<double>(n + 1));
    dp[0][0] = 1;
    for (int i = 0; i <= n; i ++) {
        for (int j = 0; j <= n; j ++) {
            if (j < n) {
                dp[i][j + 1] += (i == n ? 1 : 0.5) * dp[i][j];
            }
            if (i < n) {
                dp[i + 1][j] += (j == n ? 1 : 0.5) * dp[i][j];
            }
        }
    }

    cout << fixed << setprecision(4) << dp[n][n - 2] + dp[n - 2][n] << '\n';

    // double ans = 1;
    // for (int i = 1; i < n; i ++) {
    //     ans *= (i + n - 1.0) / (i << 2);
    // }
    
    // cout << fixed << setprecision(4) << 1 - ans << '\n';

    return 0;
}