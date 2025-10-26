#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

template<typename T>
bool cmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

void solve() {   
    int c;
    cin >> c;
    
    i64 d;
    cin >> d;

    i64 ans = 0, j = 1;
    for (int i = 1; i <= 10; i ++, j *= 10) {
        i64 lo = j - 1 - c, ro = 10 * j - 1 - c;
        cmin(ro, d);
        cmax(lo, 0ll);
        if (ro < lo) {
            continue;
        }
        lo = sqrtl(lo + c + 10 * j * c);
        ro = sqrtl(ro + c + 10 * j * c);
        ans += ro - lo;
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