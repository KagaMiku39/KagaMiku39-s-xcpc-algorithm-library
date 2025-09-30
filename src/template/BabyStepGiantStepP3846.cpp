#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mod, a, b;
    cin >> mod >> a >> b;

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
    
    auto bsgs = [&]() -> i64 {
        b %= mod;
        if (b == 1 && mod > 1) {
            return 0;
        }
        unordered_map<int, int> ump;
        int ste = sqrt(mod) + 1;
        for (int i = 0; i < ste; i ++) {
            int val = 1ll * b * binpow(a, i) % mod;
            if (!ump.count(val)) {
                ump[val] = i;
            }
        }
        int tmp = binpow(a, ste);
        if (!tmp) {
            return b == 0 ? 1 : -1;
        }
        for (int i = 1; i <= ste; i ++) {
            int val = binpow(tmp, i);
            if (ump.count(val)) {
                int j = ump[val];
                if (1ll * i * ste - j >= 0) {
                    return 1ll * i * ste - j;
                }
            }
        }
        return -1;
    };

    i64 ans = bsgs();
    if (ans == -1) {
        cout << "no solution\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}