#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, mod;
    cin >> a >> mod;
    
    string b;
    cin >> b;

    auto binpow = [&](i64 a, i64 b) {
        i64 res = 1 % mod;
        a %= mod;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    };

    auto getphi = [&](i64 n) {
        i64 res = n;
        for (i64 i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                res = res / i * (i - 1);
            }
        }
        if (n > 1) res = res / n * (n - 1);
        return res;
    };

    i64 phi = getphi(mod), bb = 0;
    for (char &c : b) {
        bb = (bb * 10 + (c - '0')) % phi;
    }

    i64 g = gcd(a, mod);

    cout << binpow(a, (g == 1 ? bb : bb + phi)) << '\n';

    return 0;
}