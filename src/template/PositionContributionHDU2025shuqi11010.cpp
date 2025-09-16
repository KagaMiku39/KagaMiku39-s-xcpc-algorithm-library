#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> p[i];
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        int pre = 0;
        vector<i64> mp(2 * n + 1);
        mp[pre + n] = 1;
        for (int j = 1; j < i; j ++) {
            pre += p[j] > p[i] ? -1 : 1;
            mp[pre + n] += j + 1;
        }
        for (int j = i; j <= n; j ++) {
            pre += i != j ? p[j] > p[i] ? -1 : 1 : 0;
            ans += mp[pre + n] * p[i] * j; 
        }
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