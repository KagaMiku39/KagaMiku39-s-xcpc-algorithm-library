#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxn = 3e7 + 1, mod = 1e9 + 7;

int fac[maxn];

void solve() {
    int m, n;
    cin >> m >> n;
    
    auto comb = [&](int m, int n) -> int {
        auto binpow = [&](int a, int b) {
            int res = 1 % mod;
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
        auto inv = [&](int x) {
            return binpow(x, mod - 2);
        };
        if (n < 0 || n > m) {
            return 0;
        }
        return 1ll * fac[m] * inv(fac[n]) % mod * inv(fac[m - n]) % mod;
    };
    
    cout << comb(m, n) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fac[0] = 1;
    for (int i = 1; i < maxn; i ++) {
        fac[i] = (1ll * fac[i - 1] * i % mod);
    }

    int t;
    cin >> t;
    
    while (t --) {
        solve();
    }

    cout << '\n';
    
    return 0;
}