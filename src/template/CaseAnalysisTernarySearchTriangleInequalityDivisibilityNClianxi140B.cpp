#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<typename T>
bool cmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}

void solve() {   
    i64 n, s;
    cin >> n >> s;

    i64 ans = s - 1;
    cmin(ans, n / s + 1 + s - n / (n / s + 1));
    
    int lo = 1, ro = n / s;
    auto pred = [&](i64 x) -> i64 {
        return x + n / x - s; 
    };
    while (lo + 3 < ro) {
        int l = lo + (ro - lo) / 3, r = ro - (ro - lo) / 3;
        if (pred(l) >= pred(r)) {
            lo = l;
        } else {
            ro = r;
        }
    }

    for (int i = lo; i <= ro; i ++) {
        cmin(ans, pred(i));
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