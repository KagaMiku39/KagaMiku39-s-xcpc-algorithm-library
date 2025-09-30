#include <bits/stdc++.h>

using namespace std;

constexpr int mod = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    auto binpow = [&](int a, int b) {
        int res = 1;
        a %= mod;
        while (b) {
            if (b & 1) {
                res = 1ll * res * a % mod;
            }
            a = 1ll * a * a % mod;
            b /= 2;
        }
        return res;
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int a = y[i], b = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            a = 1ll * a * (k - x[j]) % mod;
            b = 1ll * b * (x[i] - x[j]) % mod;
        }
        int term = 1ll * a * binpow(b, mod - 2) % mod;
        ans = (ans + term) % mod;
    }

    ans = (1ll * ans + mod) % mod;

    cout << ans << '\n';

    return 0;
}