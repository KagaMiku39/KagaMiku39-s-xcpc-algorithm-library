#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto slowmul = [&](i64 a, i64 b, i64 mod) {
        i64 res = 0;
        a = (a % mod + mod) % mod;
        b = (b % mod + mod) % mod;
        while (b) {
            if (b & 1) {
                res = (res + a) % mod;
            }
            a = (a + a) % mod;
            b /= 2;
        }
        return res;
    };
    
    i64 x, y;
    auto exgcd = [&](auto &self, i64 a, i64 b, i64 &x, i64 &y) -> i64 {
        if (!b) {
            x = 1, y = 0;
            return a;
        }
        i64 d = self(self, b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    };

    i64 a1, b1;
    cin >> a1 >> b1;
    
    for (int i = 1; i < n; i++) {
        i64 a2, b2;
        cin >> a2 >> b2;
        i64 dif = b2 - b1, g = exgcd(exgcd, a1, a2, x, y), inv = a2 / g, tmp = slowmul(x, (dif / g % inv + inv) % inv, inv);
        b1 = slowmul(tmp, a1, a1 / g * a2) + b1;
        a1 = a1 / g * a2;
        b1 = (b1 % a1 + a1) % a1;
    }

    cout << (b1 % a1 + a1) % a1 << "\n";
    
    return 0;
}