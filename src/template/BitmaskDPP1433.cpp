#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<double> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i];
    }

    vector<vector<double>> dis(n + 1, vector<double>(n + 1));
    for (int i = 0; i <= n; i ++) {
        for (int k = i + 1; k <= n; k ++) {
            dis[i][k] = sqrt(pow(x[i] - x[k], 2) + pow(y[i] - y[k], 2));
            dis[k][i] = dis[i][k];
        }
    }

    vector<vector<double>> dp(n + 1, vector<double>(1 << n, DBL_MAX));

    for (int i = 1; i <= n; i ++) {
        dp[i][1 << (i - 1)] = dis[0][i];
    }

    for (int i = 1; i < (1 << n); i ++) {
        for (int j = 0; j < n; j ++) {
            if ((i >> j) & 1) {
                for (int k = 0; k < n; k ++) {
                    if (!((i >> k) & 1)) {
                        cmin(dp[k + 1][i | (1 << k)], dp[j + 1][i] + dis[j + 1][k + 1]);
                    }
                }
            }
        }
    }

    double ans = DBL_MAX;
    for (int i = 1; i <= n; i ++) {
        cmin(ans, dp[i][(1 << n) - 1]);
    }

    cout << fixed << setprecision(2) << ans << '\n';

    return 0;
}