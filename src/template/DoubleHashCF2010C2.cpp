#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long; 

constexpr u64 mod1 = 998244353, mod2 = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string t;
    cin >> t;
    
    int n = ssize(t);
    
    t = ' ' + t;
    
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

    const u64 p1 = (rnd() % 1000) + 131, p2 = (rnd() % 1000) + 13331;

    vector<u64> po1(ssize(t)), po2(ssize(t));
    
    auto getpo = [&](string &s) {
        po1[0] = po2[0] = 1;
        for (int i = 1; i < ssize(s); i ++) {
            po1[i] = (po1[i - 1] * p1) % mod1;
            po2[i] = (po2[i - 1] * p2) % mod2;
        }
    };
    getpo(t);
    
    vector<u64> h1(ssize(t)), h2(ssize(t));
    
    auto gethash = [&](string &s) {
        for (int i = 1; i < ssize(s); i ++) {
            h1[i] = (h1[i - 1] * p1 + s[i]) % mod1;
            h2[i] = (h2[i - 1] * p2 + s[i]) % mod2;
        }
    };
    gethash(t);

    auto query = [&](int lo, int ro) {
        u64 res1 = (h1[ro] - h1[lo - 1] * po1[ro - lo + 1] % mod1 + mod1) % mod1,
            res2 = (h2[ro] - h2[lo - 1] * po2[ro - lo + 1] % mod2 + mod2) % mod2;
        return make_pair(res1, res2);
    };
    
    for (int i = n / 2 + 1; i < n; i ++) {
        if (query(1, i) == query(n - i + 1, n)) {
            cout << "YES\n" << t.substr(1, i) << '\n';
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}