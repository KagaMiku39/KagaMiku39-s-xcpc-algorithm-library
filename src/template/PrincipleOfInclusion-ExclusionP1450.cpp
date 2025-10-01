#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxs = 1e5 + 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 c[5];
    cin >> c[1] >> c[2] >> c[3] >> c[4];

    int n;
    cin >> n;

    vector<i64> dp(maxs);
    dp[0] = 1;
    for (int j = 1; j <= 4; j ++) {
        for (int i = c[j]; i < maxs; i ++) {
            dp[i] += dp[i - c[j]];
        }
    }

    for (int cnt = 1; cnt <= n; cnt ++) {
        i64 d[5];
        cin >> d[1] >> d[2] >> d[3] >> d[4];
        i64 s;
        cin >> s;
        i64 ans = 0;
        for (int i = 1; i < 16; i ++) {
            int cnt = 0;
            i64 m = s;
            for (int j = 1; j <= 4; j ++) {
                if ((i >> (j - 1)) & 1) {
                    m -= (d[j] + 1) * c[j];
                    cnt ++;
                }
            }
            if (m >= 0) {
                if (cnt % 2) {
                    ans += dp[m];
                } else {
                    ans -= dp[m];
                }
            }
        }
        cout << dp[s] - ans << '\n';
    }

    return 0;
}