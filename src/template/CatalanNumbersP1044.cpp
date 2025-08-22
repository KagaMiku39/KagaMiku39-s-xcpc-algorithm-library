#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<i64> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i ++) {
        dp[i] = dp[i - 1] * (4 * i - 2) / (i + 1);
    }

    cout << dp[n] << '\n';

    return 0;
}