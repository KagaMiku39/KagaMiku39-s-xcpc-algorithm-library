#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

#include<ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

struct Hash {
    static u64 splitmix64(u64 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator()(int x) const {
        static const i64 rnd{chrono::steady_clock::now().time_since_epoch().count()};
        return splitmix64(x + rnd);
    }
};

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
        gp_hash_table<int, int, Hash> ump;
        int ste = sqrt(mod) + 1;
        for (int i = 0; i < ste; i ++) {
            int val = 1ll * b * binpow(a, i) % mod;
            if (ump.find(val) == ump.end()) {
                ump[val] = i;
            }
        }
        int tmp = binpow(a, ste);
        if (!tmp) {
            return b == 0 ? 1 : -1;
        }
        for (int i = 1; i <= ste; i ++) {
            int val = binpow(tmp, i);
            if (ump.find(val) != ump.end()) {
                int j = ump[val];
                if (1ll * i * ste - j >= 0) {
                    return 1ll * i * ste - j;
                }
            }
        }
        return -1;
    };

    i64 res = bsgs();
    if (res == -1) {
        cout << "no solution\n";
    } else {
        cout << res << '\n';
    }

    return 0;
}