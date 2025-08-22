#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ww;
    cin >> n >> ww;
    
    vector<int> v(n + 1), w(n + 1), m(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> v[i] >> w[i] >> m[i];
    }
    
    vector<int> dp(ww + 1);
    for (int i = 1; i <= n; i ++) {
        for (int k = 1; k <= m[i]; k ++) {
            for (int j = ww; j >= w[i]; j --) {
                cmax(dp[j], dp[j - w[i]] + v[i]);
            }
        }
    }
    
    cout << dp[ww] << '\n';

    return 0;
}