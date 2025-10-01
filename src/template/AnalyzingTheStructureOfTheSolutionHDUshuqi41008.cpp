#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n, x, y, z;
    cin >> n >> x >> y >> z;

    vector<int> a(n + 1), bu(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        bu[a[i]] ++;
    }

    vector<int> dif(n + 2);
    for (int i = 1; i <= n; i ++) {
        dif[0] ++;
        dif[bu[i]] --;
    }
    for (int i = 1; i <= n; i ++) {
        dif[i] += dif[i - 1];
    }

    i64 ans = 0;
    vector<i64> dp(n + 1);
    for (int i = 1; i <= n; i ++) {
        dp[1] += 1ll * min(bu[i], 1) * x + 1ll * max(bu[i] - 1, 0) * y; 
    }
    cmax(ans, dp[1]);
    for (int i = 2; i <= n; i ++) {
        dp[i] = dp[i - 1] + z - x + 1ll * dif[i - 1] * (x - y); 
        cmax(ans, dp[i]);
    }

    cout << ans << '\n';
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