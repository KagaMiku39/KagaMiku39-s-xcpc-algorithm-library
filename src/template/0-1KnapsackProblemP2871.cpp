#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> w[i] >> v[i];
    }

    vector<int> dp(m + 1);
    for (int i = 1; i <= n; i ++) {
        for (int j = m; j >= w[i]; j --) {
            cmax(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    cout << dp[m] << '\n';

    return 0;
}