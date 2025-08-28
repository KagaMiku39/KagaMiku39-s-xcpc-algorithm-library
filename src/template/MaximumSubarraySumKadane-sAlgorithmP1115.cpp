#include <bits/stdc++.h>

using namespace std;

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

    int dp = 0, ans = INT_MIN;
    for (int i = 1; i <= n; i ++) {
        dp += a[i];
        cmax(ans, dp);
        if (dp < 0) {
            dp = 0;
        }
    }

    cout << ans << '\n';

    return 0;
}