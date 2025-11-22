#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

constexpr int maxsz = 4e5 + 1;

void solve() {   
    int n, y;
    cin >> n >> y;

    int mx = 0;
    vector<int> c(n + 1), mp(maxsz);
    for (int i = 1; i <= n; i ++) {
        cin >> c[i];
        cmax(mx, c[i]);
        mp[c[i]] ++;
    }

    if (mx == 1) {
        cout << n << '\n';
        return;
    }
    
    vector<int> pre = mp;
    for (int i = 1; i < maxsz; i ++) {
        pre[i] += pre[i - 1];
    }
    
    i64 ans = LLONG_MIN;
    for (int i = 2; i <= mx; i ++) {
        i64 res = -1ll * n * y;
        vector<int> vec((mx + i - 1) / i + 1);
        for (int j = 1; j <= (mx + i - 1) / i; j ++) {
            int cnt = pre[j * i] - pre[(j - 1) * i];
            res += 1ll * cnt * j;
            vec[j] += cnt;
        }
        for (int j = 1; j <= (mx + i - 1) / i; j ++) {
            res += 1ll * y * min(vec[j], mp[j]);
        }
        cmax(ans, res);
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