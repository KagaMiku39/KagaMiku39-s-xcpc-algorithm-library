#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

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

    i64 mx = 0, sum = 0, ans = LLONG_MIN;
    for (int i = 1; i <= n; i ++) {
        mx += a[i];
        sum += a[i];
        cmax(ans, mx);
        if (mx < 0) {
            mx = 0;
        }
    }

    i64 mi = 0;
    for (int i = 1; i <= n; i ++) {
        mi += a[i];
        cmax(ans, sum - mi);
        if (mi > 0) {
            mi = 0;
        }
    }

    cout << (ans == LLONG_MIN ? 0 : ans) << '\n';

    return 0;
}