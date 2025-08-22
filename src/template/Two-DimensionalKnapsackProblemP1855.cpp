#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> w[i] >> v[i];
    }
    
    vector<vector<int>> dp(m + 1, vector<int>(t + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = m; j >= w[i]; j --) {
            for (int k = t; k >= v[i]; k --) {
                cmax(dp[j][k], dp[j - w[i]][k - v[i]] + 1);
            }
        }
    }

    cout << dp[m][t] << '\n';

    return 0;
}