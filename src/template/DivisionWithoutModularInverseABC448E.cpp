#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m;
    cin >> k >> m;

    vector<i64> c(k + 1), l(k + 2);
    for (int i = 1; i <= k; i ++) {
        cin >> c[i] >> l[i];
    }
    
    vector<i64> suf = l;
    for (int i = k; i; i --) {
        suf[i] += suf[i + 1];
    }

    i64 mod1 = 9ll * m * 10007, mod2 = m * 10007;

    auto binpow = [&](int a, i64 b) {
        i64 res = 1 % mod1;
        a %= mod1;
        while (b) {
            if (b & 1) {
                res = 1ll * res * a % mod1;
            }
            a = 1ll * a * a % mod1;
            b /= 2;
        }
        return res;
    };
    
    i64 ans = 0;
    for (int i = 1; i <= k; i ++) {
        ans = (ans + (binpow(10, l[i]) - 1) * c[i] % mod1 * binpow(10, suf[i + 1]) % mod1) % mod1;
    }
    
    ans = (ans + mod1) % mod1;

    ans /= 9;

    ans %= mod2;

    ans /= m;

    cout << ans << '\n';

    return 0;
}