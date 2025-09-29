#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxn = 3e6 + 1;

int inv[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, mod;
    cin >> n >> mod;

    inv[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        inv[i] = (-i64(mod / i) * inv[mod % i] % mod + mod) % mod;
    }

    for (int i = 1; i <= n; i ++) {
        cout << inv[i] << '\n';
    }

    return 0;
}