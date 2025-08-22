#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sh, sm, eh, em;
    char ch;
    cin >> sh >> ch >> sm >> eh >> ch >> em;

    int n;
    cin >> n;
    
    int ww = (eh - sh) * 60 + (em - sm);
    
    vector<int> t(n + 1), c(n + 1), p(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> t[i] >> c[i] >> p[i];
    }
    
    vector<int> dp(ww + 1);

    for (int i = 1; i <= n; i ++) {
        if (!p[i]) {
            for (int j = t[i]; j <= ww; j ++) {
                cmax(dp[j], dp[j - t[i]] + c[i]);
            }
        } else {
            // for (int k = 1; p[i] > 0; k <<= 1) {
            //     int cnt = min(k, p[i]);
            //     for (int j = ww; j >= t[i] * cnt; j --) {
            //         cmax(dp[j], dp[j - t[i] * cnt] + c[i] * cnt);
            //     }
            //     p[i] -= cnt;
            // }
            for (int k = 1; k <= p[i]; k ++) {
                for (int j = ww; j >= t[i]; j --) {
                    cmax(dp[j], dp[j - t[i]] + c[i]);
                }
            }
        }
    }
    
    cout << dp[ww] << '\n';

    return 0;
}