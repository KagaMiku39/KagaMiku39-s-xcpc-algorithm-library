#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {   
    int q;
    cin >> q;

    deque<int> a;

    int m = 0, sgn = 1;

    i64 sum = 0, ans = 0;
    
    while (q --) {
        int s;
        cin >> s;
        if (s == 1) {
            if (~sgn) {
                ans += sum - 1ll * m * a.back();
                a.emplace_front(a.back());
                a.pop_back();
            } else {
                ans += sum - 1ll * m * a.front();
                a.emplace_back(a.front());
                a.pop_front();
            }
        }
        if (s == 2) {
            ans = (m + 1ll) * sum - ans;
            sgn *= -1;
        }
        if (s == 3) {
            int k;
            cin >> k;
            if (~sgn) {
                a.emplace_back(k);
            } else {
                a.emplace_front(k);
            }
            m ++;
            sum += k;
            ans += 1ll * m * k;
        }
        cout << ans << '\n';
    }
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