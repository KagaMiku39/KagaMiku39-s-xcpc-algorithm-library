#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

constexpr int maxn = 1e6 + 1, mod = 1e9 + 7;

bitset<maxn> inpr;

vector<int> pri;

int mu[maxn];

i64 f[maxn], invf[maxn], g[maxn], pre[maxn];

int binpow(int a, int b) {
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
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (n > m) {
        swap(n, m);
    }

    i64 ans = 1;
    for (int lo = 1, ro; lo <= n; lo = ro + 1) {
        ro = min(n / (n / lo), m / (m / lo));
        ans = ans * binpow(pre[ro] * binpow(pre[lo - 1], mod - 2) % mod, 1ll * (n / lo) * (m / lo) % (mod - 1)) % mod;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    inpr[0] = inpr[1] = true;
    mu[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        if (!inpr[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for (int j : pri) {
            if (1ll * i * j >= maxn) break;
            inpr[i * j] = true;
            if (i % j == 0) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = -mu[i];
        }
    }

    f[0] = 0; f[1] = 1;
    invf[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        f[i] = (f[i - 1] + f[i - 2]) % mod;
        invf[i] = binpow(f[i], mod - 2);
    }

    for (int i = 1; i < maxn; i ++) {
        g[i] = 1;
    }
    for (int i = 1; i < maxn; i ++) {
        for (int j = i; j < maxn; j += i) {
            int a = mu[j / i];
            if (a == 1) {
                g[j] = g[j] * f[i] % mod;
            } else if (a == -1) {
                g[j] = g[j] * invf[i] % mod;
            }
        }
    }

    pre[0] = 1;
    for (int i = 1; i < maxn; i ++) {
        pre[i] = pre[i - 1] * g[i] % mod;
    }

    int t;
    cin >> t;
    
    while (t --) {
        solve();
    }

    return 0;
}