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
    
    vector<int> w(n + 1), v(n + 1), m(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> w[i] >> v[i] >> m[i];
    }
    
    vector<int> dp(ww + 1);

    for (int i = 1; i <= n; i ++) {
        if (!m[i]) {
            for (int j = w[i]; j <= ww; j ++) {
                cmax(dp[j], dp[j - w[i]] + v[i]);
            }
        } else {
            for (int i = 1; i <= n; i ++) {
                for (int k = 1; k <= m[i]; k ++) {
                    for (int j = ww; j >= w[i]; j --) {
                        cmax(dp[j], dp[j - w[i]] + v[i]);
                    }
                }
            }
        }
    }
    
    cout << dp[ww] << '\n';

    return 0;
}