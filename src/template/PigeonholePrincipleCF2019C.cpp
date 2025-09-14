#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n;
    cin >> n;

    i64 k;
    cin >> k;

    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
    }

    i64 sum = 0, mx = 0;
    for (int i = 1; i <= n; i ++) {
        sum += a[i];
        cmax(mx, a[i]);
    }
    
    int ans = 0;
    i64 tot = sum + k;
    for (int i = 1; i <= n; i ++) {
        if (i * mx > tot) {
            break;
        }
        i64 r = tot % i;
        if (r <= k) {
            ans = i;
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