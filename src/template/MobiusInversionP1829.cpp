#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

constexpr int maxn = 1e7 + 1, mod = 20101009;

bitset<maxn> inpr;

vector<int> pri;

int mu[maxn], pre[maxn];

int getg(int n, int m) {
    return (1ll * n * (n + 1) / 2 % mod) * (1ll * m * (m + 1) / 2 % mod) % mod;
}

int getf(int n, int m) {
    int res = 0;
    for (int lo = 1, ro = 0; lo <= n; lo = ro + 1) {
        ro = min(n / (n / lo), m / (m / lo));
        i64 dif = (pre[ro] - pre[lo - 1] + mod) % mod;
        res = (res + dif * getg(n / lo, m / lo)) % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mu[1] = 1;
    inpr[0] = inpr[1] = true;
    for (int i = 2; i < maxn; i ++) {
        if (!inpr[i]) {
            pri.push_back(i);
            mu[i] = -1;
        }
        for (int j : pri) {
            if (1ll * i * j >= maxn) {
                break;
            }
            inpr[i * j] = true;
            if (i % j == 0) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = -mu[i];
        }
    }

    for (int i = 1; i < maxn; i ++) {
        pre[i] = (pre[i - 1] + (1ll * i * i % mod * mu[i]) % mod + mod) % mod;
    }

    int n, m;
    cin >> n >> m;

    if (n > m) {
        swap(n, m);
    }

    int ans = 0;
    for (int lo = 1, ro = 0; lo <= n; lo = ro + 1) {
        ro = min(n / (n / lo), m / (m / lo));
        i64 sum = 1ll * (ro - lo + 1) * (lo + ro) / 2 % mod;
        ans = (ans + sum * getf(n / lo, m / lo)) % mod;
    }

    cout << ans << '\n';

    return 0;
}