#include <bits/stdc++.h>

#define ssize(x) int(x.size())

using namespace std;

using i64 = long long;

constexpr int maxn = 2000010;

i64 mu[maxn], phi[maxn];

vector<int> pri;

map<i64, i64> mum, phim;

bitset<maxn> inpr;

i64 getsmu(i64 n) {
    if (n < maxn) {
        return mu[n];
    }
    if (mum.count(n)) {
        return mum[n];
    }
    i64 res = 1;
    for (i64 lo = 2, ro; lo <= n; lo = ro + 1) {
        ro = n / (n / lo);
        res -= (ro - lo + 1) * getsmu(n / lo);
    }
    mum[n] = res;
    return res;
}
    
i64 getsphi(i64 n) {
    if (n < maxn) {
        return phi[n];
    }
    if (phim.count(n)) {
        return phim[n];
    }
    i64 res = n * (n + 1) / 2;
    for (i64 lo = 2, ro; lo <= n; lo = ro + 1) {
        ro = n / (n / lo);
        res -= (ro - lo + 1) * getsphi(n / lo);
    }
    phim[n] = res;
    return res;
}

void solve() {
    i64 n;
    cin >> n;

    cout << getsphi(n) << ' ' << getsmu(n) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    inpr[0] = inpr[1] = true;
    mu[1] = phi[1] = 1;

    for (int i = 2; i < maxn; i ++) {
        if (!inpr[i]) {
            pri.emplace_back(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : pri) {
            if (1ll * i * p >= maxn) {
                break;
            }
            inpr[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
                break;
            }
            mu[i * p] = -mu[i];
            phi[i * p] = phi[i] * (p - 1);
        }
    }

    for (int i = 1; i < maxn; i ++) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }

    int t;
    cin >> t;

    while (t --) {
        solve();
    }

    return 0;
}