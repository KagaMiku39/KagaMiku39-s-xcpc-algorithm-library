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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    vector<array<array<int, 2>, 2>> dp(27);
    for (int i = 1; i <= n; i ++) {
        int cnt = 0;
        for (int j = 0; j < 27; j ++) {
            bool k = a[i] >> j & 1;
            dp[j][k][cnt % 2] ++;
            cnt += a[i] >> j & 1; 
        }
    }
    
    i64 ans = 0;
    for (int i = 0; i < 27; i ++) {
        ans += (1ll << i) * (1ll * dp[i][1][0] * dp[i][0][0] + 1ll * dp[i][1][1] * dp[i][0][1]);
    }

    cout << ans << '\n';

    return 0;
}