#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<int> fact(p);
    fact[0] = 1;
    for (int i = 1; i < p; i ++) {
        fact[i] = (1ll * fact[i - 1] * i % p);
    }

    auto comb = [&](int m, int n) -> int {
        auto binpow = [&](int a, int b) {
            int res = 1;
            a %= p;
            while (b) {
                if (b & 1) {
                    res = 1ll * res * a % p;
                }
                a = 1ll * a * a % p;
                b /= 2;
            }
            return res;
        };
        auto inv = [&](int x) {
            return binpow(x, p - 2);
        };
        if (n < 0 || n > m) {
            return 0;
        }
        return 1ll * fact[m] * inv(fact[n]) % p * inv(fact[m - n]) % p;
    };

    auto lucas = [&](auto &self, int m, int n) -> int {
        if (!n) {
            return 1;
        }
        return 1ll * self(self, m / p, n / p) * comb(m % p, n % p) % p;
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