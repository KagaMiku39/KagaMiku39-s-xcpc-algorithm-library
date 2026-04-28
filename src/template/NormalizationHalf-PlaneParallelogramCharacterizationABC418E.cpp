#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> x[i] >> y[i];
    }

    vector<pair<int, int>> slo, mid;
    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            int dx = x[i] - x[j], dy = y[i] - y[j], g = gcd(dx, dy);
            dx /= g;
            dy /= g;
            if (dx < 0 || (!dx && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }
            slo.emplace_back(dx, dy);
            int mx = x[i] + x[j], my = y[i] + y[j];
            mid.emplace_back(mx, my);
        }
    }

    i64 ans = 0;
    auto foo = [&](vector<pair<int, int>> &vec, int sgn) {
        sort(begin(vec), end(vec));
        int cnt = 0;
        for (int i = 1; i < ssize(vec); i ++) {
            if (vec[i] == vec[i - 1]) {
                cnt ++;
                ans += cnt * sgn;
            } else {
                cnt = 0;
            }
        }
    };
    foo(slo, 1);
    foo(mid, -1);
    
    cout << ans << '\n';

    return 0;
}