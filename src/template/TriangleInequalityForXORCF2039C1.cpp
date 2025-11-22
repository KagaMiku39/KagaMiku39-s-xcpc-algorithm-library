#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

void solve() {   
    int x;
    cin >> x;

    i64 m;
    cin >> m;

    cmin(m, 2ll * x);
    
    int ans = 0;
    for (int i = 1; i <= m; i ++) {
        if (x == i) {
            continue;
        }
        ans += x % (x ^ i) == 0 || i % (x ^ i) == 0; 
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