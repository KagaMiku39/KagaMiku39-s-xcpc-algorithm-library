#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

struct Hash {
    static u64 rnd;
    // inline static u64 rnd{mt19937_64(chrono::steady_clock::now().time_since_epoch().count())()};

    size_t operator () (const int &x) const{
        return x ^ rnd;
    }
};

u64 Hash::rnd{mt19937_64(chrono::steady_clock::now().time_since_epoch().count())()};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, mod, b;

    while ((cin >> a >> mod >> b) && (a || mod || b)) {
        auto binpow = [&](int a, int b, int mod) {
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
        auto exbsgs = [=]() mutable -> i64 {
            a %= mod;
            b %= mod;
            if (b == 1 && mod > 1) {
                return 0;
            }
            if (mod == 1) {
                return (b == 0) ? 0 : -1;
            }
            int k = 0;
            i64 c = 1;
            while (true) {
                int d = gcd(a, mod);
                if (d == 1) {
                    break;
                }
                if (b % d != 0) {
                    return -1;
                }
                mod /= d;
                b /= d;
                k ++;
                c = c * (a / d) % mod;
                if (c == b) {
                    return k;
                }
            }
            unordered_map<int, int, Hash> ump;
            int ste = sqrt(mod) + 1;
            for (int j = 0; j < ste; j ++) {
                int val = 1ll * b * binpow(a, j, mod) % mod;
                ump[val] = j;
            }
            int tmp = binpow(a, ste, mod);
            for (int i = 1; i <= ste; i ++) {
                int val = 1ll * c * binpow(tmp, i, mod) % mod;
                if (ump.count(val)) {
                    int j = ump[val];
                    return 1ll * i * ste - j + k;
                }
            }
            return -1;
        };
        
        i64 res = exbsgs();
        
        if (res == -1) {
            cout << "No Solution\n";
        } else {
            cout << res << '\n';
        }
    }
    
    return 0;
}