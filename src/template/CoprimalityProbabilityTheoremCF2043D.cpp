#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

void solve() {   
    i64 l, r, g;
    cin >> l >> r >> g;

    l = (l + g - 1) / g;
    r /= g;

    if (l > r || (l == r && l != 1)) {
        cout << "-1 -1\n";
        return;
    }

    i64 mx = 0, lo = LLONG_MAX, ro = 0;
    for (int i = 0; i <= 40 && l + i <= r; i ++) {
        for (int j = 0; j <= 40 && r - j >= l + i; j ++) {
            if (gcd(l + i, r - j) == 1) {
                i64 len = r - j - l - i + 1;
                if (len >= mx) {
                    if (len > mx) {
                        mx = len;
                        lo = l + i;
                        ro = r - j;
                    } else if (cmin(lo, l + i)) {
                        mx = len;
                        ro = r - j;
                    }
                }
            }
        }
    }

    lo *= g;
    ro *= g;
    
    cout << lo << ' ' << ro << '\n';
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