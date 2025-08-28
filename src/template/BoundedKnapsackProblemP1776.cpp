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

    // for (int i = 1; i <= n; i ++) {
    //     for (int k = 1; k <= m[i]; k ++) {
    //         for (int j = ww; j >= w[i]; j --) {
    //             cmax(dp[j], dp[j - w[i]] + v[i]);
    //         }
    //     }
    // }

    // for (int i = 1; i <= n; i ++) {
    //     for (int k = 1; m[i] > 0; k <<= 1) {
    //         int cnt = min(k, m[i]);
    //         for (int j = ww; j >= w[i] * cnt; j --) {
    //             cmax(dp[j], dp[j - w[i] * cnt] + v[i] * cnt);
    //         }
    //         m[i] -= cnt;
    //     } 
    // }
    
    vector<int> f(ww + 1);
    for (int i = 1; i <= n; i ++) {
        vector<int> g = f; 
        for (int j = 0; j < w[i]; j ++) {
            deque<pair<int, int>> dq;
            for (int k = j; k <= ww; k += w[i]) {
                if (!dq.empty() && dq.front().first < k - m[i] * w[i]) {
                    dq.pop_front();
                }
                
                if (!dq.empty()) {
                    int val = dq.front().second + (k - j) / w[i] * v[i];
                    cmax(f[k], val);
                }
                int val = g[k] - (k - j) / w[i] * v[i];
                while (!dq.empty() && dq.back().second <= val) {
                    dq.pop_back();
                }
                dq.emplace_back(k, val);
            }
        }
    }

    cout << f[ww] << '\n';
    
    // cout << dp[ww] << '\n';

    return 0;
}