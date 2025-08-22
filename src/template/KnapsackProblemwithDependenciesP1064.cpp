#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    
    vector<int> w(n + 1), v(n + 1), q(n + 1);
    vector<vector<int>> gr(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> w[i] >> v[i] >> q[i];
        v[i] *= w[i];
        if (q[i]) {
            gr[q[i]].emplace_back(i);
        }
    }
    
    vector<int> dp(m + 1);

    for (int i = 1; i <= n; i ++) {
        if (q[i]) {
            continue;
        }
        for (int j = m; j >= w[i]; j --) {
            cmax(dp[j], dp[j - w[i]] + v[i]);
            if (ssize(gr[i]) >= 1) {
                int a = gr[i][0];
                if (j >= w[i] + w[a]) {
                    cmax(dp[j], dp[j - w[i] - w[a]] + v[i] + v[a]);
                }
            }
            if (ssize(gr[i]) >= 2) {
                int b = gr[i][1];
                if (j >= w[i] + w[b]) {
                    cmax(dp[j], dp[j - w[i] - w[b]] + v[i] + v[b]);
                }
            }
            if (ssize(gr[i]) >= 2) {
                int a = gr[i][0], b = gr[i][1];
                if (j >= w[i] + w[a] + w[b]) {
                    cmax(dp[j], dp[j - w[i] - w[a] - w[b]] + v[i] + v[a] + v[b]);
                }
            }
        }
    }

    cout << dp[m] << '\n';

    return 0;
}