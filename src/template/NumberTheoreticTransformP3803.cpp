#include <bits/stdc++.h>

using namespace std;

constexpr int g = 3, mod = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int len = 1;
    while (len <= n + m) {
        len <<= 1;
    }

    vector<int> a(len), b(len);
    for (int i = 0; i <= n; i ++) {
        cin >> a[i];
    }
    for (int i = 0; i <= m; i ++) {
        cin >> b[i];
    }
    
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
    
    int gi = binpow(g, mod - 2);
    vector<int> r(len);
    auto ntt = [&](vector<int> &vec, int n, int op) {
        for (int i = 0; i < n; i ++) {
            r[i] = (r[i / 2] / 2) | (i & 1 ? n / 2 : 0);
        }
        for (int i = 0; i < n; i ++) {
            if (i < r[i]) {
                swap(vec[i], vec[r[i]]);
            }
        }
        for (int i = 2; i <= n; i *= 2) {
            int g1 = binpow(op == 1 ? g : gi, (mod - 1) / i);
            for (int j = 0; j < n; j += i) {
                int gk = 1;
                for (int k = j; k < j + i / 2; k ++) {
                    int x = vec[k], y = 1ll * vec[k + i / 2] * gk % mod;
                    vec[k] = (1ll * x + y) % mod;
                    vec[k + i / 2] = (1ll * x - y) % mod;
                    gk = 1ll * gk * g1 % mod;
                }
            }
        }
    };
    ntt(a, len, 1);
    ntt(b, len, 1);

    for (int i = 0; i < len; i ++) {
        a[i] = 1ll * a[i] * b[i] % mod;
    }

    ntt(a, len, -1);

    int li = binpow(len, mod - 2);
    for (int i = 0; i <= n + m; i ++) {
        a[i] = (a[i] * 1ll * li % mod + mod) % mod;
        cout << a[i] << " \n"[i == n + m];
    }

    return 0;
}