#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmin(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
	return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(2 * n + 1), pre(2 * n + 1);
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(2 * n + 1, vector<int>(2 * n + 1)));
    for (int i = 0; i <= 2 * n; i ++) {
        for (int j = 0; j <= 2 * n; j ++) {
            dp[0][i][j] = INT_MAX;
        }
    }

    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    
    for (int i = 1; i <= 2 * n; i ++) {
        pre[i] = pre[i - 1] + a[i];
    }
    
    for (int i = 1; i <= 2 * n; i ++) {
        dp[0][i][i] = 0;
    }

    for (int len = 2; len <= n; len ++) {
        for (int i = 1; i + len - 1 <= 2 * n; i ++) {
            int j = i + len - 1;
            for (int k = i; k < j; k ++) {
                cmin(dp[0][i][j], dp[0][i][k] + dp[0][k + 1][j] + pre[j] - pre[i - 1]);
                cmax(dp[1][i][j], dp[1][i][k] + dp[1][k + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }

    int ans[2]{INT_MAX, 0};
    for (int i = 1; i <= n; i ++) {
        cmin(ans[0], dp[0][i][i + n - 1]);
        cmax(ans[1], dp[1][i][i + n - 1]);
    }
    
    cout << ans[0] << '\n' << ans[1] << '\n';

    return 0;
}