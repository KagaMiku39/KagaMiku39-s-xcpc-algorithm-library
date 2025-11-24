#include <bits/stdc++.h>

using namespace std;

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int n;
    cin >> n;

    int rk, ck, rd, cd;
    cin >> rk >> ck >> rd >> cd;

    int ans = 0;
    if (rd > rk) {
        cmax(ans, rd);
    } else if (rk != rd) {
        cmax(ans, n - rd);
    }

    if (cd > ck) {
        cmax(ans, cd);
    } else if (ck != cd) {
        cmax(ans, n - cd);
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