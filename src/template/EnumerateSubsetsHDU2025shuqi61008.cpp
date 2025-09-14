#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long; 
using i128 = __int128; 

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> a[i][j];
        }
    } 

    cmin(k, m);
    
    vector<vector<i64>> dp(n + 1, vector<i64>(1 << m));
    for (int i = 0; i < (1 << m); i ++) {
        for (int j = 1; j <= n; j ++) {
            i64 sum = 0;
            for (int l = 0; l < m; l ++) {
                if (i >> l & 1) {
                    sum += a[j][l + 1];     
                }
            }
            cmax(dp[1][i], sum);
        }
    }

    for (int i = 2; i <= k; i ++) {
        for (int j = 0; j < (1 << m); j ++) {
            for (int l = j; l; l = (l - 1) & j) {
                cmax(dp[i][j], dp[i - 1][l] + dp[1][j ^ l]);
            }
        }
    }

    cout << dp[k][(1 << m) - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}