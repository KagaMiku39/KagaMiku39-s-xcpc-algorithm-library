#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    i64 ans = 0;
    if (m == 1) {
        vector<int> f(n + 1), p(n + 1), d(n + 1);
        for (int i = 1; i < n; i ++) {
            cin >> f[i];
            d[f[i]] ++;
        }
        for (int i = 1, j = 1; i <= n - 2; i ++, j ++) {
            while (d[j]) {
                j ++;
            }
            p[i] = f[j];
            while (i <= n - 2 && !--d[p[i]] && p[i] < j) {
                p[i + 1] = f[p[i]];
                i ++;
            }
        }
        for (int i = 1; i <= n - 2; i ++) {
            ans ^= 1ll * i * p[i];
        }
    } else {
        vector<int> f(n + 1, 0), p(n + 1), d(n + 1, 0);
        for (int i = 1; i <= n - 2; i ++) {
            cin >> p[i];
            d[p[i]] ++;
        }
        p[n - 1] = n;
        for (int i = 1, j = 1; i < n; i ++, j ++) {
            while (d[j]) {
                j ++;
            }
            f[j] = p[i];
            while (i < n && !--d[p[i]] && p[i] < j) {
                f[p[i]] = p[i + 1];
                i ++;
            }
        }
        
        for (int i = 1; i < n; i ++) {
            ans ^= 1ll * i * f[i];
        }
    }

    cout << ans << '\n';

    return 0;
}