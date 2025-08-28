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
            if (b & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    };

    auto getphi = [&](i64 n) {
        i64 phi = 1;
        i64 tmp = n;
        for (i64 i = 2; i * i <= tmp; i++) {
            if (tmp % i == 0) {
                phi *= i - 1;
                tmp /= i;
                while (tmp % i == 0) {
                    phi *= i;
                    tmp /= i;
                }
            }
        }
        if (tmp > 1) {
            phi *= tmp - 1;
        }
        return phi;
    };

    i64 phi = getphi(mod), bb = 0;
    bool tag = false;
    for (char &c : b) {
        bb = bb * 10 + (c - '0');
        if (!tag && bb >= phi) {
            tag = true;
            bb %= phi;
        } else {
            bb %= phi;
        }
    }
    
    if (bb >= phi) {
        tag = true;
        bb %= phi;
    }
    
    if (tag) {
        bb += phi;
    }

    cout << binpow(a, bb) << '\n';

    return 0;
}