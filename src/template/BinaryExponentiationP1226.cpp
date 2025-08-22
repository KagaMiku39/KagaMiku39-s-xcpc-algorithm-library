#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, mod;
    cin >> a >> b >> mod;

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

    cout << a << '^' << b << " mod " << mod << '=' << binpow(a, b) << '\n';

    return 0;
}