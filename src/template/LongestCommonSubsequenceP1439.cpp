#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p1(n + 1), p2(n + 1), id(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p1[i];
    }
    for (int i = 1; i <= n; i ++) {
        cin >> p2[i];
        id[p2[i]] = i;
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (p1[i] == p2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << dp[n][n] << '\n';

    // vector<int> lis;
    // for (int i = 1; i <= n; i ++) {
    //     int val = id[p1[i]];
    //     if (lis.empty() || val > lis.back()) {
    //         lis.emplace_back(val);
    //     } else {
    //         *lower_bound(begin(lis), end(lis), val) = val;
    //     }
    // }

    // cout << ssize(lis) << '\n';

    return 0;
}