
#include <bits/stdc++.h>

using namespace std;

void solve() {   
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    sort(next(begin(a)), end(a));

    vector<pair<int, int>> vec{{}};
    for (int i = 1; i <= n; i ++) {
        auto &[val, cnt] = vec.back();
        if (a[i] == val) {
            cnt ++;
        } else {
            vec.emplace_back(a[i], 1);
        }
    }

    vector<int> dp(ssize(vec), INT_MAX);
    dp[0] = 0;
    for (int i = 1; i < ssize(vec); i ++) {
        auto &[_, cnt] = vec[i];
        for (int j = i; j; j --) {
            if (dp[j - 1] != INT_MAX && dp[j - 1] + cnt <= i - j) {
                cmin(dp[j], dp[j - 1] + cnt);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < ssize(vec); i ++) {
        if (dp[i] != INT_MAX) {
            cmax(ans, i);
        }
    }

    ans = ssize(vec) - 1 - ans;
    
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