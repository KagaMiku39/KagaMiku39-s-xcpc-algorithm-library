#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {
    int n, m, mod;
    cin >> n >> m >> mod;

    vector<int> fac(mod);
    fac[0] = 1;
    for (int i = 1; i < mod; i ++) {
        fac[i] = (1ll * fac[i - 1] * i % mod);
    }

    auto comb = [&](int m, int n) -> int {
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
        auto inv = [&](int x) {
            return binpow(x, mod - 2);
        };
        if (n < 0 || n > m) {
            return 0;
        }
        return 1ll * fac[m] * inv(fac[n]) % mod * inv(fac[m - n]) % mod;
    };

    auto lucas = [&](auto &self, int m, int n) -> int {
        if (!n) {
            return 1;
        }
        return 1ll * self(self, m / mod, n / mod) * comb(m % mod, n % mod) % mod;
    };
    
    cout << lucas(lucas, n + m, n) << '\n';
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