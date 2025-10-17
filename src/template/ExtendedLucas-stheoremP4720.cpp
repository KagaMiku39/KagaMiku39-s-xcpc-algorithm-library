#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, m;
    cin >> n >> m; 

    int p;
    cin >> p;
    
    int x = 0, y = 0;
    auto exgcd = [&](auto &self, int a, int b, int &x, int &y) {
        if(!b){
            x = 1, y = 0;
            return a;
        }
        int d = self(self, b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    };

    auto inv = [&](int a, int mod) {
        i64 d = exgcd(exgcd, a, mod, x, y);
        if (d == 1) {
            return (x % mod + mod) % mod;
        }
        return 0;
    };

    auto comb = [&](i64 n, i64 m, int p, int k, int mod) -> int {
        if (m < 0 || m > n) {
            return 0;
        }
        auto getcnt = [&](i64 n, int p) {
            i64 cnt = 0;
            while (n) {
                cnt += n / p;
                n /= p;
            }
            return cnt;
        };
        i64 cn = getcnt(n, p), cm = getcnt(m, p), cnm = getcnt(n - m, p), cp = cn - cm - cnm;
        if (cp >= k) {
            return 0;
        }
        auto binpow = [&](int a, int b, int mod) {
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
        auto fac = [&](auto &self, i64 n, int p, int mod) -> int {
            if (n == 0) {
                return 1;
            }
            int res = 1;
            for (int i = 1; i < mod; i ++) {
                if (i % p != 0) {
                    res = 1ll * res * i % mod;
                }
            };
            res = binpow(res, n / mod, mod);
            for (int i = 1; i <= n % mod; i ++) {
                if (i % p != 0) {
                    res = 1ll * res * i % mod;
                }
            }
            return 1ll * res * self(self, n / p, p, mod) % mod;
        };        
        int fn = fac(fac, n, p, mod), fm = fac(fac, m, p, mod), fnm = fac(fac, n - m, p, mod),
            res = 1ll * fn * inv(fm, mod) % mod * inv(fnm, mod) % mod * binpow(p, cp, mod) % mod;
        return res;
    };

    if (m > n) {
        cout << "0\n";
    } else {
        int mod = p;
        vector<int> a, b; 
        for (int i = 2; i * i <= mod; i ++) {
            if (mod % i == 0) {
                i64 pk = 1;
                int k = 0;
                while (mod % i == 0) {
                    pk *= i;
                    k ++;
                    mod /= i;
                }
                int res = comb(n, m, i, k, pk);
                b.emplace_back(res);
                a.emplace_back(pk);
            }
        }
        if (mod > 1) {
            int res = comb(n, m, mod, 1, mod);
            b.emplace_back(res);
            a.emplace_back(mod);
        }
        i64 a1 = a[0], b1 = b[0]; 
        for (int i = 1; i < ssize(a); i ++) {
            i64 a2 = a[i], b2 = b[i], dif = b2 - b1, g = exgcd(exgcd, a1, a2, x, y),
                val = a2 / g, tmp = x * (dif / g % val + val) % val;
            b1 = tmp * a1 % (a1 / g * a2) + b1;
            a1 = a1 / g * a2; 
            b1 = (b1 % a1 + a1) % a1; 
        }
        cout << b1 << '\n';
    }
    
    return 0;
}