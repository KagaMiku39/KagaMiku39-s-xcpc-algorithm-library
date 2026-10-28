#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxn = 3e7 + 1, mod = 1e9 + 7;

int fac[maxn];

void solve() {
    int n, m;
    cin >> n >> m;
    
    auto comb = [&](int n, int m) -> int {
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
        if (m < 0 || m > n) {
            return 0;
        }        
        return 1ll * fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
    };
    
    cout << comb(n, m) << '\n';
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