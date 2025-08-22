#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, m;
    cin >> t >> m;

    vector<int> w(m + 1), v(m + 1);
    for (int i = 1; i <= m; i ++) {
        cin >> w[i] >> v[i];
    }
    
    vector<i64> dp(t + 1);
    for (int i = 1; i <= m; i ++) {
        for (int j = w[i]; j <= t; j ++) {
            cmax(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    cout << dp[t] << '\n';

    return 0;
}