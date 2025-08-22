#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<i64> dp(n + 1);
    if (n >= 1) {
        dp[1] = 0;
    }
    if (n >= 2) {
        dp[2] = 1;
    }
    for (int i = 3; i <= n; i ++) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }

    cout << dp[n] << '\n';

    return 0;
}